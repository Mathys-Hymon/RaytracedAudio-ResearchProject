// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAudioExtensionPlugin.h"
#include "Audio.h"
#include "Types/AudioRayTypes.h"
#include "Sound/AudioTracingSpatialTapDelay.h"
#include "Containers/Map.h"
#include "Containers/Array.h"
#include "Templates/SharedPointer.h"
#include "AudioTracingSpatialTapDelay.h"
#include "Math/MathFwd.h"

class FAudioTracingSpatializer : public IAudioSpatialization
{
public:
    FAudioTracingSpatializer();
    
    // override IAudioSpatialization. Used In AudioMixerRenderThread.

    virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;

    virtual bool IsSpatializationEffectInitialized() const override;

    virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings) override;

    virtual void OnReleaseSource(const uint32 SourceId) override;

    virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData) override;

    // end override IAudioSpatialization

    // Set Parameter on SourceId's Audio
    // Used in Game/Audio Thread (AudioSourceDataOverride)
    void SetTapDelayParameters(const uint32 SourceId, const FTransform& InListenerTransform,
        const FWaveInstance* InWaveInstance, const FAudioRenderData& InAudioRenderData, const TArray<FVector>& InRayDirections);

private:
    uint8 bIsInitialized: 1 = false;

    FAudioTracingSpatialTapDelaySettings TapDelaySettings;

    uint32 MaxNumSources = 0;
    uint32 SampleRate = 0;
    uint32 BufferLength = 0;
    float DirectSoundGainRatio = 1.f;
    float EarlyReflectionGainRatio = 1.f;
    int32 EarlyReflectionMaxCount = 0;
    float MappingNearCosDistThreshold = 0.99f;
    int32 NumChannel = 2;
    
    TMap<uint32, USpatializationPluginSourceSettingsBase*> SettingsMap;

    TMap<uint32, TSharedPtr<FAudioTracingSpatialTapDelay>> TapDelayMap;

    
    // Update Taps Proxy
    void EnqueuePrevTapsProxy(const FAudioTracingSpatialPrevTapDelayProxy& InProxy)
    {
        PrevTapsQueue.Enqueue(InProxy);
    }
    
    void EnqueueNewTapsProxy(const FAudioTracingSpatialNewTapDelayProxy& InProxy)
    {
        check(IsInAudioThread());
        NewTapsQueue.Enqueue(InProxy);
    }
    
    // Used in Game/Audio Thread (AudioSourceDataOverride)
    // Preserve PrevTapsProxyMap
    bool GetOrCreatePrevTapsProxy(const uint32 SourceId, FAudioTracingSpatialPrevTapDelayProxy& OutTapsProxy);

    // Used in AudioMixerRenderThread
    // Doesn't preserve NewTapsProxyMap, only for once use.
    bool GetNewTapsProxy(const uint32 SourceId, FAudioTracingSpatialNewTapDelayProxy& OutTapsProxy);
    
    void UpdatePrevTapsProxy();

    void UpdateNewTapsProxy();
    
    TArray<FAudioTracingSpatialTapDelayData> MappingTaps(const FQuat& ListenerOrientation,
        const TArray<FVector>& SoundLocations, const TArray<float>& SoundVolumes, const FAudioTracingSpatialPrevTapDelayProxy& InPrevProxy);
    
    FCriticalSection NewTapsProxyMapMutex;
    FCriticalSection PrevTapsProxyMapMutex;
    
    TMap<uint32, FAudioTracingSpatialNewTapDelayProxy> NewTapsProxyMap;
    TMap<uint32, FAudioTracingSpatialPrevTapDelayProxy> PrevTapsProxyMap;
    
    TQueue<FAudioTracingSpatialPrevTapDelayProxy> PrevTapsQueue;
    TQueue<FAudioTracingSpatialNewTapDelayProxy> NewTapsQueue;
};
