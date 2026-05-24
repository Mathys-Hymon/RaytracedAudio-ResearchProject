// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RHIGPUReadback.h"
#include "SceneViewExtension.h"
#include "Types/AudioRayTypes.h"

struct FAudioTraceParam
{
    bool bShouldTrace = false;
    FVector ListenerLocation = FVector::ZeroVector;
    FVector ListenerForward = FVector::ZeroVector;
    TArray<FActiveSoundProxy> ActiveSoundProxies;
};

class FATSceneViewExtension : public FSceneViewExtensionBase
{
public:
    FATSceneViewExtension(const FAutoRegister& AutoRegister);
    virtual ~FATSceneViewExtension() override;

    virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
    virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
    virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};

    virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;

    void UpdateAudioTraceParam_GameThread(const FAudioTraceParam& InAudioTraceData);

    void UpdateRayDirections_GameThread(const TArray<FVector>& NewRayDirections);

    // Spsc: Single-producers, single-consumer
    TQueue<FAudioTraceResult, EQueueMode::Spsc> AudioTraceResultQueue;
    
private:
    bool bShouldTrace;

    FVector ListenerLocation;

    FVector ListenerForward;
    
    TArray<FActiveSoundProxy> IdRemappedActiveSoundProxies;

    int32 NumActiveSoundProxies;

    // For Buffer Data.
    TArray<FActiveSoundProxy> TranslatedIdRemappedActiveSoundProxies;

    TArray<uint32> AudioIdArray;

    TMap<uint32, uint32> AudioIdToArrayIndexMap;

    TRefCountPtr<FRDGPooledBuffer> RayDirection;

    uint32 RayCount;

    bool IsHardwareRayTracingAvailableForView(const FSceneView& View) const;

    void TraceAudio(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs);

    void UpdateAudioTraceParam_RenderThread(FRHICommandListImmediate& RHICmdList, const FAudioTraceParam& InAudioTraceData);
    
    void UpdateRayDirectionBuffer_RenderThread(FRHICommandListImmediate& RHICmdList, const TArray<FVector>& NewRayDirections);

    
    struct FAudioTraceQueryContext
    {
        TUniquePtr<FRHIGPUBufferReadback> DataReadback;
        TUniquePtr<FRHIGPUBufferReadback> CounterReadback;

        TArray<uint32> AudioIdArrayCaptured; // To preserve the audio sequence in the GPU buffer.

        TMap<uint32, FVector> SoundLocationsCaptured;

        FVector ListenerLocationCaptured;

        FVector ListenerForwardCaptured;

        uint32 MaxReflectionDepthCaptured;
        
        bool bIsPending;

        bool bIsValid;

        uint64 QueryID;

        FAudioTraceQueryContext()
            : DataReadback(MakeUnique<FRHIGPUBufferReadback>("Traced Audio Data Readback"))
            , CounterReadback(MakeUnique<FRHIGPUBufferReadback>("Traced Audio Counter Readback"))
            , ListenerLocationCaptured(FVector::ZeroVector)
            , ListenerForwardCaptured(FVector::ZeroVector)
            , MaxReflectionDepthCaptured(0)
            , bIsPending(false)
            , bIsValid(true)
            , QueryID(0)
        {
        }

        ~FAudioTraceQueryContext()
        {
            Reset();
            
            if (DataReadback.IsValid())
            {
                DataReadback.Reset();
            }
            if (CounterReadback.IsValid())
            {
                CounterReadback.Reset();
            }
        }

        void Reset()
        {
            bIsPending = false;
            bIsValid = true;
            QueryID = 0;

            AudioIdArrayCaptured.Empty();
        }
    };
    
    static constexpr uint8 NumReadbackBuffers = 3;
    
    TArray<FAudioTraceQueryContext> AudioTraceQueryContexts;
    
    uint64 LastProcessedQueryID;

    uint64 NextQueryID;

    int32 GetValidQueryContextIndex();

    void ProcessReceivedData(uint32 QueryContextIndex);
};
