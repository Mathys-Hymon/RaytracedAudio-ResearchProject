// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAudioExtensionPlugin.h"
#include "Audio.h"
#include "AudioDevice.h"
#include "Types/AudioRayTypes.h"
#include "Utils/ATAlgorithm.h"
#include "Utils/AudioTracingParamThread.h"

class UAudioTracingWorldSubsystem;
class FAudioTracingSpatializer;
class FAudioTracingReverb;

class FATAudioSourceDataOverride : public IAudioSourceDataOverride
{
public:
    using FAudioRenderDataMapPtr = TSharedPtr<TMap<uint32, FAudioRenderData>, ESPMode::ThreadSafe>;
    
    FATAudioSourceDataOverride();
    virtual ~FATAudioSourceDataOverride() override;

    virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;
    
    virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId,
        USourceDataOverridePluginSourceSettingsBase* InSettings) override;
    
    virtual void OnReleaseSource(const uint32 SourceId) override;
    
    virtual void GetSourceDataOverrides(const uint32 SourceId,
        const FTransform& InListenerTransform, FWaveInstance* InOutWaveInstance) override;
    
    virtual void OnAllSourcesProcessed() override;
    
    void SetRayDirections(const TArray<FVector>& InRayDirections);

private:
    FSoundSubmixSendInfo ShortSubmixSend;
    FSoundSubmixSendInfo MediumSubmixSend;
    FSoundSubmixSendInfo LongSubmixSend;

    FAudioTracingSpatializer* CachedSpatializer = nullptr;
    FAudioTracingReverb* CachedReverb = nullptr;

    bool TryCachingSpatializer();

public:
    void UpdateTraceData(const FGameThreadAudioTracePacket& InPacket);

    void UpdateBypassData(const FGameThreadAudioTracePacket& InPacket);

    void GetDebugData(TSharedPtr<FDebugDrawData, ESPMode::ThreadSafe>& OutDebugData);

private:
    TQueue<FGameThreadAudioTracePacket, EQueueMode::Spsc> TracePacketQueue;

    TQueue<FGameThreadAudioTracePacket, EQueueMode::Spsc> BypassPacketQueue;
    
    TQueue<TSharedPtr<FDebugDrawData, ESPMode::ThreadSafe>, EQueueMode::Spsc> DebugDataQueue;

    // Used In Game/Audio Thread
    FAudioRenderDataMapPtr CurrentRenderData;

    // Used In Game/Audio Thread
    TMap<uint32, uint32> SourceIdToPlayOrderMap;
    void RegisterSource(uint32 SourceId, uint32 PlayOrder);
    void UnregisterSource(uint32 SourceId);

    void UpdateSendReverb(FWaveInstance* InOutWaveInstance, const FAudioRenderData& AudioRenderData);
    float CalculateSendReverbInterpolation(const float TargetTime, const float PivotTime, const float OtherTime);
    
    float ReverbGainRatio = 1.f;
    float ReverbTimeMultiplier = 1.f;
    float ShortReverbRT60 = 3.f;
    float MidReverbRT60 = 7.f;
    float LongReverbRT60 = 15.f;
    
    TMap<uint32, float> ShortReverbSendLevelMap;
    TMap<uint32, float> MidReverbSendLevelMap;
    TMap<uint32, float> LongReverbSendLevelMap;

    TMap<uint32, FAudioRenderData> CurrentRenderDataMap;

    bool TryImmediateUpdateParam(int32 PlayOrder);
    
    void ManageParamThread();
    
    void EnqueueTracePacket(const TSharedPtr<FAudioTraceParameterizePacket>& InPacket);

    void ProcessBypassResult();

    TArray<FVector> RayDirections;

    /**
    * @brief A registry of all currently active sounds.
    * 
    * This map serves two core roles:
    * 1. **Data Storage:** It stores the `FSoundAttenuationSettings` for each active sound, using its `PlayOrder` as the key.
    * 2. **Source of Truth:** The presence of a key (`PlayOrder`) in this map acts as the single source of truth to confirm 
    *    that a sound is currently active on the audio thread.
    *    Therefore, a `Contains()` check is used to answer the question: "Is this sound currently active?"
    */
    TMap<uint32, TSharedPtr<const FSoundAttenuationSettings>> ActiveSoundRegistry;
    
    TSet<uint32> PendingPriorityUpdates;
private:

    
    TUniquePtr<FRunnableThread> ParamThread;
    TUniquePtr<FAudioTracingParamThread> ParamThreadRunnable;

    
    TQueue<TSharedPtr<FAudioTraceParameterizePacket>, EQueueMode::Spsc> ParamThreadInputQueue;
    TQueue<FSingleSourceParameterizationResult, EQueueMode::Mpsc> ParamThreadResultQueue;
    FEvent* WakeupEvent = nullptr;

    double LastParamUpdateTime = 0.0;

    float UpdateInterval = 0.05f;

    FGameThreadAudioTracePacket LatestPacket;
};
