// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "Sound/ATAudioSourceDataOverride.h"

#include "Engine/Engine.h"
#include "ActiveSound.h"
#include "AudioDevice.h"
#include "AudioTracing.h"
#include "AudioTracingLog.h"
#include "Sound/AudioTracingSpatializer.h"
#include "Utils/ATUtils.h"
#include "Sound/SoundSubmix.h"
#include "SubmixEffects/AudioMixerSubmixEffectReverb.h"
#include "Settings/AudioTracingSettings.h"
#include "Shaders/AudioHardwareRaytracing.h"


FATAudioSourceDataOverride::FATAudioSourceDataOverride()
{
    // Create initial data map
}

FATAudioSourceDataOverride::~FATAudioSourceDataOverride()
{

    if (ParamThread.IsValid())
    {
        ParamThread->Kill(true);
    }
    
    if (WakeupEvent)
    {
        FPlatformProcess::ReturnSynchEventToPool(WakeupEvent);
        WakeupEvent = nullptr;
    }
}

void FATAudioSourceDataOverride::Initialize(const FAudioPluginInitializationParams InitializationParams)
{
    const UAudioTracingSettings* ATSettings = GetDefault<UAudioTracingSettings>();

    WakeupEvent = FPlatformProcess::GetSynchEventFromPool(false);
    
    UpdateInterval = 0.05f;
    ReverbGainRatio = 1.f;
    ReverbTimeMultiplier = 1.f;

    if (ATSettings != nullptr)
    {
        UpdateInterval = AudioTracing::GetMinUpdateInterval();
        ReverbGainRatio = FATUtils::DecibelToRatio(ATSettings->ReverbGain);
        ReverbTimeMultiplier = ATSettings->ReverbTimeMultiplier;
    }
    else
    {
        UE_LOG(LogAudioTracing, Warning, TEXT("Failed to find AudioTracingSettings. FATAudioSourceDataOverride will use Default Value."));
    }
    
    ParamThreadRunnable = MakeUnique<FAudioTracingParamThread>(
        &ParamThreadInputQueue,
        &ParamThreadResultQueue,
        WakeupEvent
    );
    
    FString ThreadName = FString::Printf(TEXT("AudioTracingParamThread_%d"), FPlatformTLS::GetCurrentThreadId());
    ParamThread = TUniquePtr<FRunnableThread>(FRunnableThread::Create(ParamThreadRunnable.Get(), *ThreadName, 0, TPri_Normal));

    if (!ParamThread.IsValid())
    {
        UE_LOG(LogAudioTracing, Error, TEXT("Failed to create AudioTracingParamThread."));
    }
    
    TObjectPtr<USoundSubmix> ShortReverbSubmix = Cast<USoundSubmix>(ATSettings->ShortReverbSubmixPath.TryLoad());
    TObjectPtr<USoundSubmix> MediumReverbSubmix = Cast<USoundSubmix>(ATSettings->MediumReverbSubmixPath.TryLoad());
    TObjectPtr<USoundSubmix> LongReverbSubmix = Cast<USoundSubmix>(ATSettings->LongReverbSubmixPath.TryLoad());

    if ( !IsValid(ShortReverbSubmix) || !IsValid(MediumReverbSubmix) || !IsValid(LongReverbSubmix) )
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATAudioSourceDataOverride::Initialize(): Invalid reverb submixes specified in settings."));
    }
    else
    {
        bool bIsShortReverbEffector = false;
        if ( ShortReverbSubmix->SubmixEffectChain.Num() > 0 )
        {
            if ( USubmixEffectReverbPreset* Reverb = Cast<USubmixEffectReverbPreset>(ShortReverbSubmix->SubmixEffectChain[0]) )
            {
                ShortReverbRT60 = Reverb->Settings.DecayTime;
                bIsShortReverbEffector = true;
            }
        }

        if (!bIsShortReverbEffector)
        {
            UE_LOG(LogAudioTracing, Error, TEXT("FATAudioSourceDataOverride::Initialize(): Can not find Reverb Effector in Short Reverb"));
        }

        bool bIsMidReverbEffector = false;
        if ( MediumReverbSubmix->SubmixEffectChain.Num() > 0 )
        {
            if ( USubmixEffectReverbPreset* Reverb = Cast<USubmixEffectReverbPreset>(MediumReverbSubmix->SubmixEffectChain[0]) )
            {
                MidReverbRT60 = Reverb->Settings.DecayTime;
                bIsMidReverbEffector = true;
            }
            
        } 
        
        if (!bIsMidReverbEffector)
        {
            UE_LOG(LogAudioTracing, Error, TEXT("FATAudioSourceDataOverride::Initialize(): Can not find Reverb Effector in Medium Reverb"));
        }

        bool bIsLongReverbEffector = false;
        if ( LongReverbSubmix->SubmixEffectChain.Num() > 0 )
        {
            if ( USubmixEffectReverbPreset* Reverb = Cast<USubmixEffectReverbPreset>(LongReverbSubmix->SubmixEffectChain[0]) )
            {
                LongReverbRT60 = Reverb->Settings.DecayTime;
                bIsLongReverbEffector = true;
            }
        } 

        if (!bIsLongReverbEffector)
        {
            UE_LOG(LogAudioTracing, Error, TEXT("FATAudioSourceDataOverride::Initialize(): Can not find Reverb Effector in Long Reverb"));
        }
    }
    
    ShortSubmixSend.SoundSubmix = ShortReverbSubmix;
    MediumSubmixSend.SoundSubmix = MediumReverbSubmix;
    LongSubmixSend.SoundSubmix = LongReverbSubmix;

    auto SendLevelControlMethod = ESendLevelControlMethod::Manual;
    ShortSubmixSend.SendLevelControlMethod = SendLevelControlMethod;
    MediumSubmixSend.SendLevelControlMethod = SendLevelControlMethod;
    LongSubmixSend.SendLevelControlMethod = SendLevelControlMethod;

    auto sendStage = ESubmixSendStage::PostDistanceAttenuation;
    ShortSubmixSend.SendStage = sendStage;
    MediumSubmixSend.SendStage = sendStage;
    LongSubmixSend.SendStage = sendStage;

    LastParamUpdateTime = -1.0; 
}

void FATAudioSourceDataOverride::OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId,
    USourceDataOverridePluginSourceSettingsBase* InSettings)
{
}

void FATAudioSourceDataOverride::OnReleaseSource(const uint32 SourceId)
{
    if (SourceIdToPlayOrderMap.Contains(SourceId))
    {
        uint32 PlayOrder = SourceIdToPlayOrderMap[SourceId];
        ActiveSoundRegistry.Remove(PlayOrder);
        CurrentRenderDataMap.Remove(PlayOrder);
        ShortReverbSendLevelMap.Remove(PlayOrder);
        MidReverbSendLevelMap.Remove(PlayOrder);
        LongReverbSendLevelMap.Remove(PlayOrder);
    }
    UnregisterSource(SourceId);
}

void FATAudioSourceDataOverride::GetSourceDataOverrides(const uint32 SourceId, const FTransform& InListenerTransform, FWaveInstance* InOutWaveInstance)
{
    /*
    * Register and Enqueue playing wave instance
    */
    uint32 PlayOrder = InOutWaveInstance->ActiveSound->GetPlayOrder();
    
    if (!ActiveSoundRegistry.Contains(PlayOrder))
    {
        PendingPriorityUpdates.Add(PlayOrder);
    }
    
    ActiveSoundRegistry.Add(PlayOrder, MakeShared<FSoundAttenuationSettings>(InOutWaveInstance->ActiveSound->AttenuationSettings));
    RegisterSource(SourceId, PlayOrder);

    if (PendingPriorityUpdates.Contains(PlayOrder))
    {
        if (TryImmediateUpdateParam(PlayOrder))
        {
            PendingPriorityUpdates.Remove(PlayOrder);
        }
    }

    ManageParamThread();
    ProcessBypassResult();

    if (CurrentRenderDataMap.Contains(PlayOrder))
    {
        //const FAudioRenderData& AudioRenderData = CurrentRenderDataMap[PlayOrder];
        
        FAudioRenderData AudioRenderData;
        CurrentRenderDataMap.RemoveAndCopyValue(PlayOrder, AudioRenderData);
        
        // Spatializer
        if (TryCachingSpatializer())
        {
            CachedSpatializer->SetTapDelayParameters(SourceId, InListenerTransform, InOutWaveInstance, AudioRenderData, RayDirections);
        }
        
        // Reverb
        UpdateSendReverb(InOutWaveInstance, AudioRenderData);
        if (InOutWaveInstance->SoundSubmixSends.Num() >= 3)
        {
            ShortReverbSendLevelMap.Add(PlayOrder, InOutWaveInstance->SoundSubmixSends[0].SendLevel);
            MidReverbSendLevelMap.Add(PlayOrder, InOutWaveInstance->SoundSubmixSends[1].SendLevel);
            LongReverbSendLevelMap.Add(PlayOrder, InOutWaveInstance->SoundSubmixSends[2].SendLevel);
        }
        
    }
    else
    {
        // Reverb without RenderDataMap
        // to reduct clikcing reverb noise
        ShortSubmixSend.SendLevel = 0.f;
        MediumSubmixSend.SendLevel = 0.f;
        LongSubmixSend.SendLevel = 0.f;
        if (ShortReverbSendLevelMap.Contains(PlayOrder))
        {
            ShortSubmixSend.SendLevel = ShortReverbSendLevelMap[PlayOrder];
        }
        if ( MidReverbSendLevelMap.Contains(PlayOrder) )
        {
            MediumSubmixSend.SendLevel = MidReverbSendLevelMap[PlayOrder];
        }
        if ( LongReverbSendLevelMap.Contains(PlayOrder) )
        {
            LongSubmixSend.SendLevel = LongReverbSendLevelMap[PlayOrder];
        }

        InOutWaveInstance->SoundSubmixSends.Add(ShortSubmixSend);
        InOutWaveInstance->SoundSubmixSends.Add(MediumSubmixSend);
        InOutWaveInstance->SoundSubmixSends.Add(LongSubmixSend);
    }
}

// Not the audio thread, but the audio mixer render thread
void FATAudioSourceDataOverride::OnAllSourcesProcessed()
{
}

void FATAudioSourceDataOverride::SetRayDirections(const TArray<FVector>& InRayDirections)
{
    if (!IsInAudioThread())
    {
        TArray<FVector> RayDirectionsCopy = InRayDirections;

        FAudioThread::RunCommandOnAudioThread(
            [this, RayDirectionsCopy]() 
            {
                SetRayDirections(RayDirectionsCopy);
            }
        );
    }
    else
    {
        RayDirections = InRayDirections;
    }
}

bool FATAudioSourceDataOverride::TryCachingSpatializer()
{
    if ( CachedSpatializer != nullptr )
    {
        return true;
    }

    if ( FAudioDevice* AudioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice() )
    {
        if ( IAudioSpatialization* BasePluginPtr = AudioDevice->GetSpatializationPluginInterface().Get() )
        {
            CachedSpatializer = static_cast<FAudioTracingSpatializer*>(BasePluginPtr);
        }
    }

    if ( CachedSpatializer == nullptr )
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATAudioSourceDataOverride::TryCachingSpatializer(): Failed to caching FAudioTracingSpatializer."));
        return false;
    }
    return true;
}

void FATAudioSourceDataOverride::UpdateTraceData(const FGameThreadAudioTracePacket& InPacket)
{
    check(IsInGameThread());
    TracePacketQueue.Enqueue(InPacket);
}

void FATAudioSourceDataOverride::UpdateBypassData(const FGameThreadAudioTracePacket& InPacket)
{
    check(IsInGameThread());
    BypassPacketQueue.Enqueue(InPacket);
}

void FATAudioSourceDataOverride::GetDebugData(TSharedPtr<FDebugDrawData, ESPMode::ThreadSafe>& OutDebugData)
{
    check(IsInGameThread());

    TSharedPtr<FDebugDrawData, ESPMode::ThreadSafe> TempData;

    while ( DebugDataQueue.Dequeue(TempData) )
    {
        if (!OutDebugData.IsValid() || TempData->SoundDebugInfos.IsEmpty())
        {
            OutDebugData = TempData;
        }
        else
        {
            for (FDebugDrawData::FDebugInfo& DebugInfo: TempData->SoundDebugInfos)
            {
                OutDebugData->SoundDebugInfos.Add(DebugInfo);
            }
        }
    }
}

void FATAudioSourceDataOverride::RegisterSource(uint32 SourceId, uint32 PlayOrder)
{
    check(IsInAudioThread());
    const uint32* FoundPlayOrder = SourceIdToPlayOrderMap.Find(SourceId);
    if ( FoundPlayOrder && *FoundPlayOrder == PlayOrder )
    {
        return;
    }
    SourceIdToPlayOrderMap.Add(SourceId, PlayOrder);
}

void FATAudioSourceDataOverride::UnregisterSource(uint32 SourceId)
{
    check(IsInAudioThread());
    SourceIdToPlayOrderMap.Remove(SourceId);
}

void FATAudioSourceDataOverride::UpdateSendReverb(FWaveInstance* InOutWaveInstance, const FAudioRenderData& AudioRenderData)
{
    if (AudioRenderData.RenderData.IsEmpty())
    {
        return;
    }

    float ReverbGainAvgdB = 0.f;
    float RT60Avg = 0.f;
    for (const FSynthesizeAudioData& RenderData : AudioRenderData.RenderData)
    {
        ReverbGainAvgdB += RenderData.ReverbGain;
        RT60Avg += RenderData.RT60;
    }
    ReverbGainAvgdB /= AudioRenderData.RenderData.Num();
    RT60Avg /= AudioRenderData.RenderData.Num();
    RT60Avg *= ReverbTimeMultiplier;

    float ReverbGainAvg = FATUtils::DecibelToRatio(ReverbGainAvgdB);

    ShortSubmixSend.SendLevel = 0.f;
    MediumSubmixSend.SendLevel = 0.f;
    LongSubmixSend.SendLevel = 0.f;

    if ( !AudioTracing::UseHardwareRaytracing() )
    {
        ShortSubmixSend.SendLevel = 0.f;
        MediumSubmixSend.SendLevel = 0.f;
        LongSubmixSend.SendLevel = 0.f;
    }
    else if (RT60Avg < ShortReverbRT60)
    {
        ShortSubmixSend.SendLevel = ReverbGainAvg * (RT60Avg / ShortReverbRT60);
    }
    else if ( ShortReverbRT60 < RT60Avg && RT60Avg < MidReverbRT60 )
    {
        float Weight = CalculateSendReverbInterpolation(RT60Avg, ShortReverbRT60, MidReverbRT60);
        ShortSubmixSend.SendLevel = ReverbGainAvg * Weight;
        MediumSubmixSend.SendLevel = ReverbGainAvg * (1 - Weight);
    }
    else if ( MidReverbRT60 < RT60Avg && RT60Avg < LongReverbRT60 )
    {
        float Weight = CalculateSendReverbInterpolation(RT60Avg, MidReverbRT60, LongReverbRT60);
        MediumSubmixSend.SendLevel = ReverbGainAvg * Weight;
        LongSubmixSend.SendLevel = ReverbGainAvg * (1 - Weight);
    }
    else if ( LongReverbRT60 < RT60Avg )
    {
        LongSubmixSend.SendLevel = ReverbGainAvg;
    }

    ShortSubmixSend.SendLevel *= ReverbGainRatio;
    MediumSubmixSend.SendLevel *= ReverbGainRatio;
    LongSubmixSend.SendLevel *= ReverbGainRatio;

    InOutWaveInstance->SoundSubmixSends.Add(ShortSubmixSend);
    InOutWaveInstance->SoundSubmixSends.Add(MediumSubmixSend);
    InOutWaveInstance->SoundSubmixSends.Add(LongSubmixSend);
}

float FATAudioSourceDataOverride::CalculateSendReverbInterpolation(const float TargetTime, const float PivotTime, const float OtherTime)
{
    auto DecayOnTargetTime = [TargetTime](const float RT60)
    {
        return FMath::Pow(10, -6 * TargetTime / RT60);
    };
    return (DecayOnTargetTime(TargetTime) - DecayOnTargetTime(OtherTime)) / (DecayOnTargetTime(PivotTime) - DecayOnTargetTime(OtherTime));
}

bool FATAudioSourceDataOverride::TryImmediateUpdateParam(int32 PlayOrder)
{
    FGameThreadAudioTracePacket TempPacket;
    while (TracePacketQueue.Dequeue(TempPacket))
    {
        LatestPacket = TempPacket;
    }

    if (LatestPacket.TraceResult.IsValid() && LatestPacket.TraceResult->TracedAudioData.Contains(PlayOrder))
    {
        TSharedPtr<const FAudioTraceResult, ESPMode::ThreadSafe> LatestTraceResult = LatestPacket.TraceResult;
        const bool bIsDebugEnabled = LatestPacket.bDebugVirtualAudio;

        auto AttenuationSettingsMap = MakeShared<
            TMap<uint32, TSharedPtr<const FSoundAttenuationSettings>>, ESPMode::ThreadSafe>();


        auto AudioTraceParameterizePacket = MakeShared<FAudioTraceParameterizePacket>();
        AudioTraceParameterizePacket->ListenerLocation = LatestTraceResult->ListenerLocation;
        AudioTraceParameterizePacket->ListenerForward = LatestTraceResult->ListenerForward;
        AudioTraceParameterizePacket->bDebugVirtualAudio = bIsDebugEnabled;

        if (ActiveSoundRegistry.Contains(PlayOrder))
        {
            FSingleSourceParameterizeData SoundData;
            SoundData.PlayOrder = PlayOrder;
            SoundData.TracedAudioData = LatestPacket.TraceResult->TracedAudioData[PlayOrder];
            SoundData.SoundLocation = LatestPacket.TraceResult->SoundLocations[PlayOrder];
            SoundData.AttenuationSetting = ActiveSoundRegistry[PlayOrder];
            AudioTraceParameterizePacket->SoundProcessData.Add(MoveTemp(SoundData));
        }


        if (!AudioTraceParameterizePacket->SoundProcessData.IsEmpty())
        {
            const UAudioTracingSettings* SettingsCDO = GetDefault<UAudioTracingSettings>();
            FATAlgorithmSettings AlgorithmSettings;
            if (SettingsCDO)
            {
                AlgorithmSettings.RayCount = SettingsCDO->RayCount;
                AlgorithmSettings.MaxTraceTime = SettingsCDO->MaxTraceTime;
                AlgorithmSettings.SoundSpeed = SettingsCDO->SoundSpeed;
                AlgorithmSettings.MaxEarlyReflectionCount = SettingsCDO->EarlyReflectionMaxCount;
            }
            AudioTraceParameterizePacket->AlgorithmSettings = AlgorithmSettings;

            FSingleSourceParameterizationResult SingleResult = FAudioTracingParamThread::CalculateSingleSourceParameterization(AudioTraceParameterizePacket, 0);

            if ( ActiveSoundRegistry.Contains(SingleResult.AudioID) )
            {
                CurrentRenderDataMap.Add(SingleResult.AudioID, SingleResult.RenderData);

                if ( SingleResult.bHasDebugData )
                {
                    TSharedPtr<FDebugDrawData> DebugData = MakeShared<FDebugDrawData, ESPMode::ThreadSafe>();
                    DebugData->ListenerLocation = SingleResult.RenderData.ListenerLocation;
                    DebugData->RayDirections = RayDirections;

                    FDebugDrawData::FDebugInfo DebugInfo;
                    DebugInfo.AudioID = SingleResult.AudioID;
                    DebugInfo.SoundLocation = SingleResult.SoundLocation;
                    DebugInfo.Parameters = MoveTemp(SingleResult.DebugParameters);
                    DebugData->SoundDebugInfos.Add(MoveTemp(DebugInfo));
                    DebugDataQueue.Enqueue(DebugData);
                }
            }
        }
        return true;
    }

    return false;
}

void FATAudioSourceDataOverride::ManageParamThread()
{
    TRACE_CPUPROFILER_EVENT_SCOPE(AudioTracing.ManageParamThread);
    check(IsInAudioThread());
    
    FSingleSourceParameterizationResult SingleResult;
    while ( ParamThreadResultQueue.Dequeue(SingleResult) )
    {
        if ( ActiveSoundRegistry.Contains(SingleResult.AudioID) )
        {
            CurrentRenderDataMap.Add(SingleResult.AudioID, SingleResult.RenderData);

            if ( SingleResult.bHasDebugData )
            {
                TSharedPtr<FDebugDrawData> DebugData = MakeShared<FDebugDrawData, ESPMode::ThreadSafe>();
                DebugData->ListenerLocation = SingleResult.RenderData.ListenerLocation;
                DebugData->RayDirections = RayDirections;

                FDebugDrawData::FDebugInfo DebugInfo;
                DebugInfo.AudioID = SingleResult.AudioID;
                DebugInfo.SoundLocation = SingleResult.SoundLocation;
                DebugInfo.Parameters = MoveTemp(SingleResult.DebugParameters);
                DebugData->SoundDebugInfos.Add(MoveTemp(DebugInfo));
                DebugDataQueue.Enqueue(DebugData);
            }
        }
    }

    const double CurrentTime = FPlatformTime::Seconds();
    if (CurrentTime - LastParamUpdateTime < UpdateInterval)
    {
        return;
    }

    FGameThreadAudioTracePacket TempPacket;
    while (TracePacketQueue.Dequeue(TempPacket))
    {
        LatestPacket = TempPacket;
    }
    
    if (LatestPacket.TraceResult.IsValid())
    {
        TSharedPtr<const FAudioTraceResult, ESPMode::ThreadSafe> LatestTraceResult = LatestPacket.TraceResult;
        const bool bIsDebugEnabled = LatestPacket.bDebugVirtualAudio;

        auto AttenuationSettingsMap = MakeShared<
            TMap<uint32, TSharedPtr<const FSoundAttenuationSettings>>, ESPMode::ThreadSafe>();

        
        auto AudioTraceParameterizePacket = MakeShared<FAudioTraceParameterizePacket>();
        AudioTraceParameterizePacket->ListenerLocation = LatestTraceResult->ListenerLocation;
        AudioTraceParameterizePacket->ListenerForward = LatestTraceResult->ListenerForward;
        AudioTraceParameterizePacket->bDebugVirtualAudio = bIsDebugEnabled;
        

        // Filters the PlayOrder of the currently active sounds in the active sound registry.
        for (const auto& Pair : LatestPacket.TraceResult->TracedAudioData)
        {
            const uint32 PlayOrder = Pair.Key;
            
            if (ActiveSoundRegistry.Contains(PlayOrder))
            {
                FSingleSourceParameterizeData SoundData;
                SoundData.PlayOrder = PlayOrder;
                SoundData.TracedAudioData = Pair.Value;
                SoundData.SoundLocation = LatestPacket.TraceResult->SoundLocations[PlayOrder];
                SoundData.AttenuationSetting = ActiveSoundRegistry[PlayOrder];

                AudioTraceParameterizePacket->SoundProcessData.Add(MoveTemp(SoundData));
            }
        }

        if (!AudioTraceParameterizePacket->SoundProcessData.IsEmpty())
        {
            LastParamUpdateTime = CurrentTime;
            
            const UAudioTracingSettings* SettingsCDO = GetDefault<UAudioTracingSettings>();
            FATAlgorithmSettings AlgorithmSettings;
            if (SettingsCDO)
            {
                AlgorithmSettings.RayCount = SettingsCDO->RayCount;
                AlgorithmSettings.MaxTraceTime = SettingsCDO->MaxTraceTime;
                AlgorithmSettings.SoundSpeed = SettingsCDO->SoundSpeed;
                AlgorithmSettings.MaxEarlyReflectionCount = SettingsCDO->EarlyReflectionMaxCount;
            }
            AudioTraceParameterizePacket->AlgorithmSettings = AlgorithmSettings;

            EnqueueTracePacket(AudioTraceParameterizePacket);
        }

        LatestPacket.TraceResult = nullptr;
        LatestPacket.bDebugVirtualAudio = false;
    }
    
}

void FATAudioSourceDataOverride::EnqueueTracePacket(const TSharedPtr<FAudioTraceParameterizePacket>& InPacket)
{
    ParamThreadInputQueue.Enqueue(InPacket);

    if (WakeupEvent)
    {
        WakeupEvent->Trigger();
    }
}

void FATAudioSourceDataOverride::ProcessBypassResult()
{
    check(IsInAudioThread());

    bool bNewData = false;
    FGameThreadAudioTracePacket TraceResult;
    while ( BypassPacketQueue.Dequeue(TraceResult) )
    {
        bNewData = true;
    }

    if (bNewData)
    {
        TArray<uint32> AudioIDs;
        TraceResult.TraceResult->SoundLocations.GetKeys(AudioIDs);
        for (const uint32 AudioID: AudioIDs)
        {
            if ( ActiveSoundRegistry.Contains(AudioID) )
            {
                FAudioRenderData RenderData;
                RenderData.AudioID = AudioID;
                RenderData.ListenerForward = TraceResult.TraceResult->ListenerForward;
                RenderData.ListenerLocation = TraceResult.TraceResult->ListenerLocation;
                RenderData.SoundLocation = TraceResult.TraceResult->SoundLocations[AudioID];

                FSynthesizeAudioData BypassRenderData;
                BypassRenderData.AudioID = AudioID;
                BypassRenderData.DirectionIdx = -1;
                BypassRenderData.Distance = FVector::Dist(RenderData.ListenerLocation, RenderData.SoundLocation);
                BypassRenderData.ReflectionCount = 0;
                BypassRenderData.ReverbGain = 0.f;
                BypassRenderData.RT60 = 0.f;
                BypassRenderData.TraceType = ETracedRayType::ETT_DirectSound;
                BypassRenderData.Volume = 1.f;
                RenderData.RenderData.Add(BypassRenderData);

                CurrentRenderDataMap.Add(AudioID, RenderData);
            }
        }
        
    }
}