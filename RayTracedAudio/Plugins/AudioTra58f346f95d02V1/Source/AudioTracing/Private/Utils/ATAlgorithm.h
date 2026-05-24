// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ATUtils.h"
#include "Types/AudioRayTypes.h"
#include "Async/AsyncWork.h"
#include "Async/ParallelFor.h"
#include "Sound/SoundAttenuation.h"

struct FATAlgorithmSettings
{
    float SoundSpeed = 34300.f;
    float MaxTraceTime = 2.f;
    int32 RayCount = 256;
    int32 MaxEarlyReflectionCount = 20;
};

class FAudioTracingAlgorithm
{
public:
    static TArray<FSynthesizeAudioData> Parameterize(const TArray<FTracedAudioData>& TracedDataArray, const FATAlgorithmSettings& InSettings);

    static void DistanceAttenuateRayTracedData(TArray<FTracedAudioData>& TargetData, const FTransform& SoundTransform, const FVector& ListenerLocation, TSharedPtr<const FSoundAttenuationSettings> AttenuationSetting);

    static float DefaultDistanceAttenuate(float Distance);


private:
    struct FClusterInfo
    {
        int32 FirstRayDirectionIdx = INDEX_NONE;
        float FirstRayDelay = 0.f;
        TArray<float> EarlyReflectionVolumes;
        TArray<float> EarlyReflectionDelays;
    };

    struct FEarlyReflectionInfo
    {
        int32 DirIdx;
        float Delay;
        float Volume;
    };
};

// Structure to contain calculation results for a single source
struct FSingleSourceParameterizationResult
{
    uint32 AudioID = 0;
    FAudioRenderData RenderData;
    
    bool bHasDebugData = false;
    FVector SoundLocation;
    TArray<FSynthesizeAudioData> DebugParameters;
};

struct FSingleSourceParameterizeData
{
    uint32 PlayOrder = 0;
    TArray<FTracedAudioData> TracedAudioData;
    FVector SoundLocation = FVector::ZeroVector;
    TSharedPtr<const FSoundAttenuationSettings> AttenuationSetting;
};

struct FAudioTraceParameterizePacket 
{
    FVector ListenerLocation = FVector::ZeroVector;
    FVector ListenerForward = FVector::ZeroVector;

    TArray<FSingleSourceParameterizeData> SoundProcessData;

    FATAlgorithmSettings AlgorithmSettings;
    bool bDebugVirtualAudio = false;
    
};



/**
 * This is an asynchronous task class that processes audio ray tracing results in parallel and
 * streams the calculation results of each source individually into a queue.
 */
class FStreamingParameterizeTask : public FNonAbandonableTask
{
public:
    TQueue<FSingleSourceParameterizationResult, EQueueMode::Mpsc>* ResultQueuePtr;

    FStreamingParameterizeTask(
        TSharedPtr<FAudioTraceResult, ESPMode::ThreadSafe> InTraceResult,
        TSharedPtr<TMap<uint32, TSharedPtr<const FSoundAttenuationSettings>>, ESPMode::ThreadSafe> InAttenuationSettingsMap,
        const FATAlgorithmSettings& InSettings,
        bool bInDebugVirtualAudio,
        TQueue<FSingleSourceParameterizationResult, EQueueMode::Mpsc>* InResultQueuePtr)
        : ResultQueuePtr(InResultQueuePtr)
        , TraceResult(InTraceResult)
        , AttenuationSettingsMap(InAttenuationSettingsMap)
        , bDebugVirtualAudio(bInDebugVirtualAudio)
        , AlgorithmSettings(InSettings)
    {
    }

    void DoWork()
    {
        check(ResultQueuePtr);
        
        TArray<TTuple<uint32, TArray<FTracedAudioData>>> TraceDataArray;
        TraceDataArray.Reserve(TraceResult->TracedAudioData.Num());
        for (auto& Pair : TraceResult->TracedAudioData)
        {
            TraceDataArray.Emplace(Pair.Key, MoveTemp(Pair.Value));
        }

        ParallelFor(TraceDataArray.Num(), [&](int32 Index)
        {
            const uint32 AudioId = TraceDataArray[Index].Get<0>();
            TArray<FTracedAudioData> TraceAudioDataArr = TraceDataArray[Index].Get<1>(); 

            if (TraceAudioDataArr.IsEmpty() || !TraceResult->SoundLocations.Contains(AudioId))
            {
                return;
            }

            const FVector SoundLocation = TraceResult->SoundLocations[AudioId];
            
            if (AttenuationSettingsMap->Contains(AudioId))
            {
                FAudioTracingAlgorithm::DistanceAttenuateRayTracedData(TraceAudioDataArr, FTransform(SoundLocation), TraceResult->ListenerLocation, (*AttenuationSettingsMap)[AudioId]);
            }
            
            TArray<FSynthesizeAudioData> Parameters = FAudioTracingAlgorithm::Parameterize(TraceAudioDataArr, AlgorithmSettings);

            FSingleSourceParameterizationResult SingleResult;
            SingleResult.AudioID = AudioId;
            SingleResult.RenderData.AudioID = AudioId;
            SingleResult.RenderData.SoundLocation = SoundLocation;
            SingleResult.RenderData.ListenerForward = TraceResult->ListenerForward;
            SingleResult.RenderData.ListenerLocation = TraceResult->ListenerLocation;
            
            if (bDebugVirtualAudio)
            {
                SingleResult.bHasDebugData = true;
                SingleResult.SoundLocation = SoundLocation;
                SingleResult.DebugParameters = Parameters; 
            }
            
            SingleResult.RenderData.RenderData = MoveTemp(Parameters); 

            ResultQueuePtr->Enqueue(SingleResult);
        });
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FStreamingParameterizeTask, STATGROUP_ThreadPoolAsyncTasks);
    }

private:
    TSharedPtr<FAudioTraceResult, ESPMode::ThreadSafe> TraceResult;
    TSharedPtr<TMap<uint32, TSharedPtr<const FSoundAttenuationSettings>>, ESPMode::ThreadSafe> AttenuationSettingsMap;
    bool bDebugVirtualAudio;
    FATAlgorithmSettings AlgorithmSettings;
};
