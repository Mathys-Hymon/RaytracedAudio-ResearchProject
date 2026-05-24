// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "Sound/AudioTracingSpatializer.h"

#include "AudioDevice.h"
#include "AudioTracing.h"
#include "AudioTracingLog.h"
#include "Settings/AudioTracingSettings.h"
#include "Types/AudioRayTypes.h"
#include "Utils/ATUtils.h"
#include "Stats/Stats.h"
#include "Shaders/AudioHardwareRaytracing.h"

DECLARE_CYCLE_STAT(TEXT("TapDelay Mapping"), STAT_TapDelayMapping, STATGROUP_AudioTracing);

FAudioTracingSpatializer::FAudioTracingSpatializer()
    : TapDelaySettings()
{
}

void FAudioTracingSpatializer::Initialize(const FAudioPluginInitializationParams InitializationParams)
{
    const UAudioTracingSettings* ATSettings = GetDefault<UAudioTracingSettings>();

    DirectSoundGainRatio = 1.f;
    EarlyReflectionGainRatio = 1.f;
    EarlyReflectionMaxCount = 0;
    MappingNearCosDistThreshold = 0.99f;

    if ( ATSettings != nullptr )
    {
        DirectSoundGainRatio = FATUtils::DecibelToRatio(ATSettings->DirectSoundGain);
        EarlyReflectionGainRatio = FATUtils::DecibelToRatio(ATSettings->EarlyReflectionGain);
        EarlyReflectionMaxCount = ATSettings->EarlyReflectionMaxCount;
        
        const float Radian = FMath::DegreesToRadians(FMath::Max(AudioTracing::GetMinUpdateInterval(), InitializationParams.BufferLength / InitializationParams.SampleRate) * 500.f);
        MappingNearCosDistThreshold = FMath::Cos( Radian );
    }
    else
    {
        UE_LOG(LogAudioTracing, Warning, TEXT("Failed to find AudioTracingSettings. FAudioTracingSpatializer will use Default Value."));
    }

    MaxNumSources = InitializationParams.NumSources;
    SampleRate = InitializationParams.SampleRate;
    BufferLength = InitializationParams.BufferLength;

    bIsInitialized = true;
}

bool FAudioTracingSpatializer::IsSpatializationEffectInitialized() const
{
    return bIsInitialized;
}

void FAudioTracingSpatializer::OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings)
{
    const UAudioTracingSettings* ATSettings = GetDefault<UAudioTracingSettings>();
    
    TapDelaySettings.BlockSample = BufferLength;
    TapDelaySettings.SampleRate = SampleRate;
    TapDelaySettings.NearestDistanceThreshold = 100.f;
    TapDelaySettings.InterpolationTimeSecond = 0.2f;
    TapDelaySettings.MaxDelayLengthSecond = 5.f;
    TapDelaySettings.SoundSpeed = 34300;
    TapDelaySettings.HeadWidth = 30;
    TapDelaySettings.NumChannel = NumChannel;
    TapDelaySettings.MaxNumTaps = 10;
    TapDelaySettings.NearestDistanceThresholdSquared = TapDelaySettings.NearestDistanceThreshold * TapDelaySettings.NearestDistanceThreshold;
    if (ATSettings != nullptr)
    {
        TapDelaySettings.SoundSpeed = ATSettings->SoundSpeed;
        TapDelaySettings.HeadWidth = ATSettings->HeadWidth;
    }

    TSharedPtr<FAudioTracingSpatialTapDelay> TapDelay = MakeShared< FAudioTracingSpatialTapDelay>();
    TapDelay->Init(TapDelaySettings);
    TapDelayMap.Add(SourceId, TapDelay);
}

void FAudioTracingSpatializer::OnReleaseSource(const uint32 SourceId)
{
    {
        FScopeLock Lock(&PrevTapsProxyMapMutex);
        
        TapDelayMap.Remove(SourceId);
        PrevTapsProxyMap.Remove(SourceId);
    }
    {
        FScopeLock Lock(&NewTapsProxyMapMutex);
        
        NewTapsProxyMap.Remove(SourceId);
    }
}

void FAudioTracingSpatializer::ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)
{
    const bool bIsAudioTracingEnabled = AudioTracing::UseHardwareRaytracing();
    const uint32 SourceId = InputData.SourceId;

    FAudioRenderData RenderData;

    FAudioTracingSpatialNewTapDelayProxy NewTapsProxy;
    if (GetNewTapsProxy(SourceId, NewTapsProxy))
    {
        FAudioTracingSpatialPrevTapDelayProxy PrevTapsProxy = TapDelayMap[SourceId]->UpdateTaps(NewTapsProxy);
        PrevTapsProxy.SourceId = SourceId;
        EnqueuePrevTapsProxy(PrevTapsProxy);
    }
    TapDelayMap[SourceId]->bIsBypass = !bIsAudioTracingEnabled;
    TapDelayMap[SourceId]->ProcessAudio(InputData, OutputData);
}

void FAudioTracingSpatializer::SetTapDelayParameters(const uint32 SourceId, const FTransform& InListenerTransform,
    const FWaveInstance* InWaveInstance, const FAudioRenderData& InAudioRenderData, const TArray<FVector>& InRayDirections)
{
    check(IsInAudioThread());

    TArray<FAudioTracingSpatialTapDelayData> NewTaps;

    TArray<FVector> VirtualSoundRelativeLocations;
    TArray<float> VirtualSoundVolumes;
    for (const FSynthesizeAudioData& AudioData : InAudioRenderData.RenderData)
    {
        if (AudioData.ReflectionCount == 0)
        {
            VirtualSoundRelativeLocations.Add(InAudioRenderData.SoundLocation - InAudioRenderData.ListenerLocation);
            VirtualSoundVolumes.Add(AudioData.Volume * DirectSoundGainRatio);
        }
        else
        {
            VirtualSoundRelativeLocations.Add(InRayDirections[AudioData.DirectionIdx] * AudioData.Distance);
            VirtualSoundVolumes.Add(AudioData.Volume * EarlyReflectionGainRatio);
        }
    }

    FAudioTracingSpatialPrevTapDelayProxy PrevTapsProxy;
    GetOrCreatePrevTapsProxy(SourceId, PrevTapsProxy);

    FAudioTracingSpatialNewTapDelayProxy NewTapsProxy;
    NewTapsProxy.SourceId = SourceId;
    NewTapsProxy.NewTapProxy = MappingTaps(InListenerTransform.GetRotation(), VirtualSoundRelativeLocations, VirtualSoundVolumes, PrevTapsProxy);

    EnqueueNewTapsProxy(NewTapsProxy);
}

void FAudioTracingSpatializer::UpdatePrevTapsProxy()
{
    FAudioTracingSpatialPrevTapDelayProxy Data;
    FScopeLock Lock(&PrevTapsProxyMapMutex);
    while (PrevTapsQueue.Dequeue(Data))
    {
        PrevTapsProxyMap.Add(Data.SourceId, MoveTemp(Data));
    }
}

void FAudioTracingSpatializer::UpdateNewTapsProxy()
{
    FAudioTracingSpatialNewTapDelayProxy Data;
    FScopeLock Lock(&NewTapsProxyMapMutex);
    while (NewTapsQueue.Dequeue(Data))
    {
        NewTapsProxyMap.Add(Data.SourceId, MoveTemp(Data));
    }
}

bool FAudioTracingSpatializer::GetOrCreatePrevTapsProxy(const uint32 SourceId, FAudioTracingSpatialPrevTapDelayProxy& OutTapsProxy)
{
    check(IsInAudioThread());
    
    UpdatePrevTapsProxy();

    {
        FScopeLock Lock(&PrevTapsProxyMapMutex);
        
        if (FAudioTracingSpatialPrevTapDelayProxy* FoundProxy = PrevTapsProxyMap.Find(SourceId))
        {
            // Preserve PrevTapsProxy
            // if remove PrevTapsProxy, it will create new tap while mapping taps,
            // then sometimes volume are boosted by thread speed difference
            OutTapsProxy = *FoundProxy;
            return true;
        }
    }
    
    OutTapsProxy.SourceId = SourceId;
    OutTapsProxy.PrevTapProxy.AddDefaulted(NumChannel);
    return false;
}

bool FAudioTracingSpatializer::GetNewTapsProxy(const uint32 SourceId, FAudioTracingSpatialNewTapDelayProxy& OutTapsProxy)
{
    UpdateNewTapsProxy();

    {
        FScopeLock Lock(&NewTapsProxyMapMutex);
        
        if (NewTapsProxyMap.Contains(SourceId))
        {
            NewTapsProxyMap.RemoveAndCopyValue(SourceId, OutTapsProxy);
            return true;
        }
    }
    
    OutTapsProxy.SourceId = SourceId;
    return false;
}

TArray<FAudioTracingSpatialTapDelayData> FAudioTracingSpatializer::MappingTaps(const FQuat& ListenerOrientation,
    const TArray<FVector>& SoundLocations, const TArray<float>& SoundVolumes, const FAudioTracingSpatialPrevTapDelayProxy& InPrevProxy)
{
    check(IsInAudioThread());
    
    static uint32 NewTapIdCounter = 1;

    if ( SoundLocations.Num() != SoundVolumes.Num() )
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FAudioTracingSpatialTapDelay::MappingTaps(): Size of SoundLocations and SoundVolumes not equal."));
        return {};
    }

    SCOPE_CYCLE_COUNTER(STAT_TapDelayMapping);

    TArray<FVector> FilteredSoundLocation;
    TArray<float> FilteredSoundVolumes;

    // Filter with MaxNumTaps
    if ( SoundLocations.Num() > TapDelaySettings.MaxNumTaps)
    {
        TArray<TPair<FVector, float>> Sorted;
        for ( int32 i = 0; i < SoundLocations.Num(); ++i )
        {
            Sorted.Add({ SoundLocations[i], SoundVolumes[i] });
        }
        Algo::Sort(Sorted, [](TPair<FVector, float> LHS, TPair<FVector, float> RHS)
        {
            return LHS.Value > RHS.Value;
        });
        Sorted.RemoveAt(TapDelaySettings.MaxNumTaps, SoundLocations.Num() - TapDelaySettings.MaxNumTaps);

        for (int32 i = 0; i < TapDelaySettings.MaxNumTaps; ++i)
        {
            FilteredSoundLocation.Add(Sorted[i].Key);
            FilteredSoundVolumes.Add(Sorted[i].Value);
        }
    }
    else
    {
        FilteredSoundLocation = SoundLocations;
        FilteredSoundVolumes = SoundVolumes;
    }
    

    TArray<FAudioTracingSpatialTapDelayData> NewTaps;
    const int32 NumSounds = FilteredSoundLocation.Num();
    const float FindNearVolumedBThreshold = -20.f;

    for (int32 ChannelIdx = 0; ChannelIdx < NumChannel; ++ChannelIdx )
    {
        FAudioTracingSpatialTapDelayData PrevTapsByChannel = InPrevProxy.PrevTapProxy[ChannelIdx];
        FAudioTracingSpatialTapDelayData NewTapsByChannel;

        const FVector ChannelDirection = ListenerOrientation.RotateVector(TapDelaySettings.ChannelDirections[ChannelIdx]);
        NewTapsByChannel.ChannelLocation = ChannelDirection * (TapDelaySettings.HeadWidth / 2.f);

        TArray<uint32> TapIndices;
        PrevTapsByChannel.TapsLocations.GetKeys(TapIndices);

        for ( int32 SoundIndex = 0; SoundIndex < NumSounds; ++SoundIndex )
        {
            const FVector SoundLocation = FilteredSoundLocation[SoundIndex];
            const float SoundVolume = FilteredSoundVolumes[SoundIndex];

            // Find Nearest Tap Position
            int32 NearestTapIndexPos = -1;
            uint32 NearestTapIndex = 0;

            // adjust cos dist & volume diff threshold
            float NearestCosDist = -1.f;
            const float NearVolumeDiffdBThreshold = 3.f;
            const float NearCosDistThreshold = MappingNearCosDistThreshold;

            for ( int32 TapIndexPos = 0; TapIndexPos < TapIndices.Num(); ++TapIndexPos )
            {
                const uint32 TapIndex = TapIndices[TapIndexPos];
                if ( TapIndex == 0 )
                {
                    continue;
                }

                const FVector PrevTapLocation = PrevTapsByChannel.TapsLocations[TapIndex];
                const float PrevTapVolume = PrevTapsByChannel.TapsVolumes[TapIndex];
                const float DistPow = FVector::DistSquared(PrevTapLocation, SoundLocation);
                const float CosDist = FVector::DotProduct(PrevTapLocation.GetSafeNormal(), SoundLocation.GetSafeNormal());
                const float VolumeDiffdB = FMath::Abs(FATUtils::RatioToDecibel(PrevTapVolume / SoundVolume));

                if ( CosDist > NearCosDistThreshold && CosDist > NearestCosDist && VolumeDiffdB < NearVolumeDiffdBThreshold )
                {
                    NearestTapIndexPos = TapIndexPos;
                    NearestTapIndex = TapIndex;
                    NearestCosDist = CosDist;
                }
            }

            // if param position can't find near tap position, add tap
            if ( NearestTapIndexPos == -1 )
            {
                const int32 NewTapId = NewTapIdCounter++;
                NewTapsByChannel.TapsLocations.Add(NewTapId, SoundLocation);
                NewTapsByChannel.TapsVolumes.Add(NewTapId, SoundVolume);
            }
            // if param position found nearest tap position, update tap
            else
            {
                NewTapsByChannel.TapsLocations.Add(NearestTapIndex, SoundLocation);
                NewTapsByChannel.TapsVolumes.Add(NearestTapIndex, SoundVolume);
            }

            // remove from finding range
            if ( NearestTapIndexPos >= 0 )
            {
                TapIndices[NearestTapIndexPos] = 0;
            }
        }

        NewTaps.Add(NewTapsByChannel);
    }

    return NewTaps;
}