// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "AudioTracingWorldSubsystem.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Stats/Stats.h"

#include "Types/AudioRayTypes.h"
#include "Utils/ATUtils.h"
#include "Utils/ATAlgorithm.h"

#include "AudioDevice.h"
#include "AudioTracing.h"
#include "AudioTracingLog.h"
#include "SceneViewExtensions/ATSceneViewExtension.h"
#include "Settings/AudioTracingSettings.h"
#include "Sound/ATAudioSourceDataOverride.h"
#include "Sound/SoundSubmix.h"

#include "SubmixEffects/SubmixEffectTapDelay.h"
#include "SubmixEffects/AudioMixerSubmixEffectReverb.h"
#include "Shaders/AudioHardwareRaytracing.h"

#include "Utils/AudioTracingParamThread.h"

QUICK_SCOPE_CYCLE_COUNTER(STAT_UAudioTracingWorldSubsystem_Tick);

DECLARE_CYCLE_STAT(TEXT("RayTracing"), STAT_ATRayTracing, STATGROUP_AudioTracing);


void UAudioTracingWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UAudioTracingSettings* AudioSettings = GetDefault<UAudioTracingSettings>();
    if ( !AudioSettings )
    {
        UE_LOG(LogAudioTracing, Error, TEXT("UATEngineSubsystem::Initialize(): AudioTracingSettings is null."));
    }

    SetRayCount(AudioSettings->RayCount);

    // Create SceneViewExtension
    ATSceneViewExtension = FSceneViewExtensions::NewExtension<FATSceneViewExtension>();

    OnTracedDataReceived.BindUObject(this, &UAudioTracingWorldSubsystem::SendTracedDataReceived);
}

void UAudioTracingWorldSubsystem::Deinitialize()
{
    OnTracedDataReceived.Unbind();

    if (ATSceneViewExtension.IsValid())
    {
        ATSceneViewExtension.Reset();
        ATSceneViewExtension = nullptr;
    }
    
    CachedAudioSourceDataOverride = nullptr;
    Super::Deinitialize();
}

void UAudioTracingWorldSubsystem::Tick(float DeltaTime) 
{
    if (GetAudioTracingPlugins() == nullptr)
    {
        return;
    }
    
    // Check if RayCount is dirty
    if (bIsRayCountDirty)
    {
        RayDirections = FATUtils::MakeUniformDirections(RayCount);
        
        if (ATSceneViewExtension.IsValid())
        {
            ATSceneViewExtension->UpdateRayDirections_GameThread(RayDirections);
        }

        // Safe to call since GetAudioTracingPlugins() validated the pointer
        CachedAudioSourceDataOverride->SetRayDirections(RayDirections);

        bIsRayCountDirty = false;
    }

    UpdateActiveSound();

    UpdateBypassParam();

    UpdateHardwareRaytracingParam();

    if (bDebugVirtualAudio || AudioTracing::IsVirtualAudioDebugEnabled())
    {
        ProcessDebugVirtualAudio();
    }

    PollRenderThreadResults();
    SendBypassData();
}

TStatId UAudioTracingWorldSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UAudioTracingWorldSubsystem, STATGROUP_Tickables);
}

void UAudioTracingWorldSubsystem::SetDebugVirtualAudioEnabled(bool bIsEnabled)
{
    bDebugVirtualAudio = bIsEnabled;
}

const TArray<FVector>& UAudioTracingWorldSubsystem::GetRayDirections() const
{
    return RayDirections;
}

void UAudioTracingWorldSubsystem::SetRayCount(int32 NewRayCount)
{
    if (NewRayCount < 0 || NewRayCount == RayCount)
    {
        return;
    }

    RayCount = NewRayCount;
    bIsRayCountDirty = true;
}

bool UAudioTracingWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
    return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UAudioTracingWorldSubsystem::UpdateActiveSound()
{
    if (!IsInAudioThread())
    {
        FAudioThread::RunCommandOnAudioThread(
            [this]()
            {
                UpdateActiveSound();
            }
        );
    }
    else
    {
        FVector ListenerLocation = FVector::ZeroVector;
        FVector ListenerFrontDir = FVector::ZeroVector;
        FVector ListenerRightDir = FVector::ZeroVector;
        if ( !GetAudioListenerPosition(ListenerLocation, ListenerFrontDir, ListenerRightDir) )
        {
            return;
        }

        const FAudioDevice* AudioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();
        TArray<FActiveSound*> ActiveSounds = AudioDevice->GetActiveSounds();
        bIsActiveSoundExist = false;

        TArray<FActiveSoundProxy> NewActiveSoundProxy;
        NewActiveSoundProxy.Reserve(ActiveSounds.Num());
        TArray<FActiveSoundProxy> NewBypassActiveSoundProxy;
        NewBypassActiveSoundProxy.Reserve(ActiveSounds.Num());

        for (const FActiveSound* ActiveSound : ActiveSounds)
        {
            if (!ActiveSound->bHasAttenuationSettings)
            {
                continue;
            }
            if (ActiveSound->AttenuationSettings.SpatializationAlgorithm != SPATIALIZATION_HRTF || !ActiveSound->AttenuationSettings.bEnableSourceDataOverride)
            {
                continue;
            }

            // Bypass if Attenuation is not applied
            if (!ActiveSound->AttenuationSettings.bAttenuate)
            {
                FActiveSoundProxy& Proxy = NewBypassActiveSoundProxy.Emplace_GetRef();

                const FVector Location = ActiveSound->Transform.GetLocation();
                Proxy.Location.X = static_cast<float>(Location.X);
                Proxy.Location.Y = static_cast<float>(Location.Y);
                Proxy.Location.Z = static_cast<float>(Location.Z);

                Proxy.AudioID = static_cast<uint32>(ActiveSound->GetPlayOrder());
                
            }
            else
            {
                FActiveSoundProxy& Proxy = NewActiveSoundProxy.Emplace_GetRef();

                const FVector Location = ActiveSound->Transform.GetLocation();
                Proxy.Location.X = static_cast<float>(Location.X);
                Proxy.Location.Y = static_cast<float>(Location.Y);
                Proxy.Location.Z = static_cast<float>(Location.Z);

                Proxy.AudioID = static_cast<uint32>(ActiveSound->GetPlayOrder());

                bIsActiveSoundExist = true;
            }
        }

        // Separate Farest # of ActiveSound to Bypass
        const int32 MaxActiveSoundSources = AudioTracing::GetMaxActiveSoundSources();
        if ( NewActiveSoundProxy.Num() > MaxActiveSoundSources )
        {
            Algo::Sort(NewActiveSoundProxy, [ListenerLocation](const FActiveSoundProxy& LHS, const FActiveSoundProxy& RHS)
            {
                const FVector LHSLocation = FVector(LHS.Location.X, LHS.Location.Y, LHS.Location.Z);
                const FVector RHSLocation = FVector(RHS.Location.X, RHS.Location.Y, RHS.Location.Z);

                return (FVector::DistSquared(LHSLocation, ListenerLocation) < FVector::DistSquared(RHSLocation, ListenerLocation));
            });

            for (int32 ActiveProxyIndex = MaxActiveSoundSources; ActiveProxyIndex < NewActiveSoundProxy.Num(); ++ActiveProxyIndex)
            {
                NewBypassActiveSoundProxy.Add(NewActiveSoundProxy[ActiveProxyIndex]);

                UE_LOG(LogAudioTracing, Log, TEXT("UAudioTracingWorldSubsystem::UpdateActiveSound(): Bypassed Active Sound Play Order: %d"), NewActiveSoundProxy[ActiveProxyIndex].AudioID);
            }

            NewActiveSoundProxy.RemoveAt(MaxActiveSoundSources, NewActiveSoundProxy.Num() - MaxActiveSoundSources);
        }

        {
            FScopeLock Lock(&ActiveSoundProxyMutex);
            ActiveSoundProxy = MoveTemp(NewActiveSoundProxy);
            BypassActiveSoundProxy = MoveTemp(NewBypassActiveSoundProxy);
        }
    }
}

TArray<FActiveSoundProxy> UAudioTracingWorldSubsystem::GetActiveSounds() const
{
    TArray<FActiveSoundProxy> ActiveSoundsCopy;
    {
        FScopeLock Lock(&ActiveSoundProxyMutex);
        ActiveSoundsCopy = ActiveSoundProxy;
    }

    return ActiveSoundsCopy;
}

TArray<FActiveSoundProxy> UAudioTracingWorldSubsystem::GetBypassSounds() const
{
    TArray<FActiveSoundProxy> BypassSoundsCopy;
    {
        FScopeLock Lock(&ActiveSoundProxyMutex);
        BypassSoundsCopy = BypassActiveSoundProxy;
    }

    return BypassSoundsCopy;
}

void UAudioTracingWorldSubsystem::SendTracedDataReceived(FAudioTraceResult& RayTracedResult)
{
    if ( FATAudioSourceDataOverride* AudioSourceDataOverride = GetAudioTracingPlugins() )
    {
        FGameThreadAudioTracePacket Packet;
        Packet.TraceResult = MakeShared<FAudioTraceResult, ESPMode::ThreadSafe>(RayTracedResult);
        Packet.bDebugVirtualAudio = bDebugVirtualAudio || AudioTracing::IsVirtualAudioDebugEnabled();
        
        AudioSourceDataOverride->UpdateTraceData(Packet);
    }
}

void UAudioTracingWorldSubsystem::SendBypassData()
{
    if ( BypassAudioResult.SoundLocations.IsEmpty())
    {
        return;
    }

    if ( FATAudioSourceDataOverride* AudioSourceDataOverride = GetAudioTracingPlugins() )
    {
        FGameThreadAudioTracePacket Packet;
        Packet.TraceResult = MakeShared<FAudioTraceResult, ESPMode::ThreadSafe>(BypassAudioResult);
        Packet.bDebugVirtualAudio = false;

        AudioSourceDataOverride->UpdateBypassData(Packet);
    }
}

void UAudioTracingWorldSubsystem::ProcessDebugVirtualAudio()
{
    if ( !bIsActiveSoundExist || !AudioTracing::UseHardwareRaytracing() )
    {
        CachedDebugData.Reset();
    }
 
    if ( FATAudioSourceDataOverride* AudioSourceDataOverride = GetAudioTracingPlugins() )
    {
        TSharedPtr<FDebugDrawData, ESPMode::ThreadSafe> LatestDebugData;
        AudioSourceDataOverride->GetDebugData(LatestDebugData);
        
        if (!LatestDebugData.IsValid())
        {
            if (!CachedDebugData.IsValid())
            {
                return;
            }
            LatestDebugData = CachedDebugData;
        }
        else
        {
            CachedDebugData = LatestDebugData;
        }
        
        FVector ListenerLocation = LatestDebugData->ListenerLocation;
        for (const auto& DebugInfo : LatestDebugData->SoundDebugInfos)
        {
            for (const FSynthesizeAudioData& Parameter : DebugInfo.Parameters)
            {
                FVector Direction;
                if (Parameter.ReflectionCount == 0)
                {
                    Direction = (DebugInfo.SoundLocation - ListenerLocation).GetSafeNormal();
                }
                else
                {
                    Direction = LatestDebugData->RayDirections[Parameter.DirectionIdx];
                }

                FVector RelativeSoundPosition = Direction * Parameter.Distance;
                FString Message = FString::Printf(TEXT("AudioID:%d\nVol: %.2f\nRT60: %.2f\nReverbGain: %.2f"), Parameter.AudioID, Parameter.Volume, Parameter.RT60, Parameter.ReverbGain);
                float VolumedB = 10 * FMath::LogX(10, Parameter.Volume);
                FColor LineColor = FColor::MakeRedToGreenColorFromScalar(FMath::Clamp((30.f + VolumedB) / 30.f, 0.f, 1.f));
                DrawDebugDirectionalArrow(GetWorld(), ListenerLocation, ListenerLocation + RelativeSoundPosition, 10.f, LineColor);
                DrawDebugString(GetWorld(), ListenerLocation + RelativeSoundPosition, Message, nullptr, FColor::White, 0.f, true);
            }
        }
    }
}

void UAudioTracingWorldSubsystem::UpdateBypassParam()
{
    FVector ListenerLocation = FVector::ZeroVector;
    FVector ListenerFrontDir = FVector::ZeroVector;
    FVector ListenerRightDir = FVector::ZeroVector;
    if ( !GetAudioListenerPosition(ListenerLocation, ListenerFrontDir, ListenerRightDir) )
    {
        return;
    }

    BypassAudioResult.ListenerLocation = ListenerLocation;
    BypassAudioResult.ListenerForward = ListenerFrontDir;
    BypassAudioResult.SoundLocations.Empty();
    BypassAudioResult.TracedAudioData.Empty();

    TArray<FActiveSoundProxy> BypassSoundProxies = GetBypassSounds();
    if (BypassSoundProxies.IsEmpty())
    {
        return;
    }

    for (const FActiveSoundProxy& ActiveSound: BypassSoundProxies)
    {
        const FVector SoundLocation = FVector(ActiveSound.Location.X, ActiveSound.Location.Y, ActiveSound.Location.Z);

        TArray<FTracedAudioData> AudioData;
        AudioData.AddDefaulted();
        AudioData[0].AudioID = ActiveSound.AudioID;
        AudioData[0].DirectionIdx = -1;
        AudioData[0].Distance = FVector::Dist(ListenerLocation, SoundLocation);
        AudioData[0].ReflectionCount = 0;
        AudioData[0].Volume = 1.f;
            

        BypassAudioResult.SoundLocations.Add(ActiveSound.AudioID, SoundLocation);
        BypassAudioResult.TracedAudioData.Add(ActiveSound.AudioID, AudioData);
    }
}

void UAudioTracingWorldSubsystem::UpdateHardwareRaytracingParam()
{
    FVector ListenerLocation = FVector::ZeroVector;
    FVector ListenerFrontDir = FVector::ZeroVector;
    FVector ListenerRightDir = FVector::ZeroVector;
    if (!GetAudioListenerPosition(ListenerLocation, ListenerFrontDir, ListenerRightDir))
    {
        return;
    }
    
    // Get data directly from Override.
    TArray<FActiveSoundProxy> ActiveSoundProxies = GetActiveSounds();

    // Update ray tracing parameters only when data is available.
    if (ATSceneViewExtension.IsValid())
    {
        FAudioTraceParam AudioTraceParam;
        AudioTraceParam.bShouldTrace = (GetAudioTracingPlugins() != nullptr);
        AudioTraceParam.ListenerLocation = ListenerLocation;
        AudioTraceParam.ListenerForward = ListenerFrontDir;
        AudioTraceParam.ActiveSoundProxies = ActiveSoundProxies;
        
        ATSceneViewExtension->UpdateAudioTraceParam_GameThread(AudioTraceParam);
    }
}

void UAudioTracingWorldSubsystem::PollRenderThreadResults() const
{
    if (!ATSceneViewExtension.IsValid())
    {
        return;
    }

    FAudioTraceResult NewData;
    bool bHasNewData = false;

    while (ATSceneViewExtension->AudioTraceResultQueue.Dequeue(NewData))
    {
        bHasNewData = true;
    }

    if (bHasNewData)
    {
        OnTracedDataReceived.ExecuteIfBound(NewData);
    }
}

bool UAudioTracingWorldSubsystem::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->GetAudioListenerPosition(OutLocation, OutFrontDir, OutRightDir);
        return true;
    }
    return false;
}

FATAudioSourceDataOverride* UAudioTracingWorldSubsystem::GetAudioTracingPlugins()
{
    if ( CachedAudioSourceDataOverride == nullptr )
    {
        // Cache AudioSourceOverride if not already done
        if ( const FAudioDeviceHandle AudioDeviceHandle = GetWorld()->GetAudioDevice() )
        {
            if ( const FAudioDevice* AudioDevice = AudioDeviceHandle.GetAudioDevice() )
            {
                if ( IAudioSourceDataOverride* BasePluginPtr = AudioDevice->SourceDataOverridePluginInterface.Get() )
                {
                    CachedAudioSourceDataOverride = static_cast<FATAudioSourceDataOverride*>(BasePluginPtr);
                }
            }
        }
    }

    return CachedAudioSourceDataOverride;
}