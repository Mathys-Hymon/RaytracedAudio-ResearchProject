// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "ATSceneViewExtension.h"

#include "Shaders/AudioHardwareRaytracing.h"
#include "AudioTracing.h"
#include "RHIGPUReadback.h"
#include "ScenePrivate.h"
#include "SceneView.h"

DECLARE_GPU_STAT(AudioHardwareRayTracing);


FVector3f AbsoluteWorldLocationToTranslatedWorldLocation(const FVector3f& AbsoluteWorldLocation, const FVector3f& ViewLocation)
{
    return AbsoluteWorldLocation - ViewLocation;
}

FVector3f TranslatedWorldLocationToAbsoluteWorldLocation(const FVector3f& TranslatedWorldLocation, const FVector3f& ViewLocation)
{
    return TranslatedWorldLocation + ViewLocation;
}


FATSceneViewExtension::FATSceneViewExtension(const FAutoRegister& AutoRegister)
    : FSceneViewExtensionBase(AutoRegister)
    , bShouldTrace(false)
    , ListenerLocation(FVector::ZeroVector)
    , ListenerForward(FVector::ZeroVector)
    , NumActiveSoundProxies(0)
    , RayCount(0)
    , LastProcessedQueryID(0)
    , NextQueryID(1)
{
    AudioTraceQueryContexts.Reserve(NumReadbackBuffers);
    AudioTraceQueryContexts.SetNum(NumReadbackBuffers);

    const int32 MaxActiveSoundSources = AudioTracing::GetMaxActiveSoundSources();

    AudioIdArray.Reset(MaxActiveSoundSources);
    AudioIdToArrayIndexMap.Reset();
    AudioIdToArrayIndexMap.Reserve(MaxActiveSoundSources);
    IdRemappedActiveSoundProxies.Reset(MaxActiveSoundSources);
    TranslatedIdRemappedActiveSoundProxies.Reset(MaxActiveSoundSources);
}

FATSceneViewExtension::~FATSceneViewExtension()
{
    if (RayDirection.IsValid())
    {
        RayDirection.SafeRelease();
    }

    AudioTraceQueryContexts.Empty();
}

void FATSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
    FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

#if RHI_RAYTRACING
    if (IsHardwareRayTracingAvailableForView(View))
    {
        TraceAudio(GraphBuilder, View, Inputs);
    }
#endif
}

void FATSceneViewExtension::UpdateAudioTraceParam_GameThread(const FAudioTraceParam& InAudioTraceData)
{
    ENQUEUE_RENDER_COMMAND(UpdateSourceDataForRender)(
        [this, InAudioTraceData](FRHICommandListImmediate& RHICmdList)
        {
            this->UpdateAudioTraceParam_RenderThread(RHICmdList, InAudioTraceData);
        }
    );
}

void FATSceneViewExtension::UpdateRayDirections_GameThread(const TArray<FVector>& NewRayDirections)
{
    ENQUEUE_RENDER_COMMAND(UpdateRayDirectionsForRender)(
        [this, NewRayDirections](FRHICommandListImmediate& RHICmdList)
        {
            this->UpdateRayDirectionBuffer_RenderThread(RHICmdList, NewRayDirections);
        }
    );
}

bool FATSceneViewExtension::IsHardwareRayTracingAvailableForView(const FSceneView& View) const
{
    if (!AudioTracing::UseHardwareRaytracing() || !View.bAllowRayTracing)
    {
        return false;
    }

    const FViewInfo& ViewInfo = static_cast<const FViewInfo&>(View);
    if (!ViewInfo.InlineRayTracingBindingDataBuffer)
    {
        return false;
    }

    const FScene* Scene = View.Family->Scene->GetRenderScene();
    if (!Scene || !Scene->RayTracingScene.GetRHIRayTracingScene(ERayTracingSceneLayer::Base))
    {
        return false;
    }

    return true;
}

void FATSceneViewExtension::TraceAudio(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
#if RHI_RAYTRACING
    const int32 ValidQueryContextIndex = GetValidQueryContextIndex();
    if (ValidQueryContextIndex < 0)
    {
        return;
    }

    if (!bShouldTrace || NumActiveSoundProxies == 0 || RayCount == 0 || !RayDirection.IsValid())
    {
        return;
    }

    checkSlow(View.bIsViewInfo);

    RDG_EVENT_SCOPE_STAT(GraphBuilder, AudioHardwareRayTracing, "AudioHardwareRayTracing");
    
    const FViewInfo& ViewInfo = static_cast<const FViewInfo&>(View);

    const uint32 MaxReflectionDepth = AudioTracing::GetMaxReflectionDepth();

    const int32 MaxActiveSoundSources = AudioTracing::GetMaxActiveSoundSources();

    // ID Remapped Active Sound Proxies with Translated World Location Data.
    TranslatedIdRemappedActiveSoundProxies.Reset(MaxActiveSoundSources);
    for (const FActiveSoundProxy& SoundProxy : IdRemappedActiveSoundProxies)
    {
        const FVector3f TranslatedWorldLocation = AbsoluteWorldLocationToTranslatedWorldLocation(SoundProxy.Location,FVector3f(View.ViewLocation));
        TranslatedIdRemappedActiveSoundProxies.Emplace(FActiveSoundProxy(TranslatedWorldLocation, SoundProxy.AudioID));
    }

    // Buffers
    FRDGBufferRef RayDirectionBuffer = GraphBuilder.RegisterExternalBuffer(RayDirection);

    FRDGBufferRef ActiveSoundProxiesBuffer = CreateStructuredBuffer(
        GraphBuilder,
        TEXT("AudioTracing.ActiveSoundProxies"),
        sizeof(FActiveSoundProxy),
        MaxActiveSoundSources,
        TranslatedIdRemappedActiveSoundProxies.GetData(),
        sizeof(FActiveSoundProxy) * NumActiveSoundProxies
    );

    const uint64 NumMaxResults = NumActiveSoundProxies * RayCount * (MaxReflectionDepth + 1);
    FRDGBufferRef TracedResultBuffer = CreateStructuredBuffer(
        GraphBuilder,
        TEXT("AudioTracing.TracedResult"),
        sizeof(FTracedAudioData),
        NumMaxResults,
        nullptr,
        0
    );

    TArray<uint32> ResultCounter;
    ResultCounter.Reserve(NumActiveSoundProxies);
    ResultCounter.SetNumZeroed(NumActiveSoundProxies);
    FRDGBufferRef ResultCounterBuffer = CreateStructuredBuffer(
        GraphBuilder,
        TEXT("AudioTracing.ResultCounter"),
        sizeof(uint32),
        NumActiveSoundProxies,
        ResultCounter.GetData(),
        sizeof(uint32) * NumActiveSoundProxies
    );
    
    const FVector TranslatedListenerLocation = ListenerLocation - View.ViewLocation;

    FAudioHardwareRayTracingContext ParamContext(GraphBuilder, View,
        GraphBuilder.CreateSRV(RayDirectionBuffer),
        GraphBuilder.CreateSRV(ActiveSoundProxiesBuffer),
        GraphBuilder.CreateUAV(TracedResultBuffer),
        GraphBuilder.CreateUAV(ResultCounterBuffer),
        FVector3f(TranslatedListenerLocation.X, TranslatedListenerLocation.Y, TranslatedListenerLocation.Z),
        NumActiveSoundProxies,
        RayCount,
        MaxReflectionDepth);

    const bool bAsyncCompute = GSupportsEfficientAsyncCompute && (GNumExplicitGPUsForRendering == 1);
    
    FGlobalShaderMap* ShaderMap = ViewInfo.ShaderMap;

    // Direct Sound
    FAudioHardwareRayTracingDirectCS::FParameters* DirectParameters = GraphBuilder.AllocParameters<FAudioHardwareRayTracingDirectCS::FParameters>();
    AudioTracing::SetAudioHardwareRayTracingParams(ParamContext, DirectParameters);
    
    const TShaderRef<FAudioHardwareRayTracingDirectCS> AudioHardwareRayTracingDirectCS = ShaderMap->GetShader<FAudioHardwareRayTracingDirectCS>();
    const FIntVector GroupCountDirect = FComputeShaderUtils::GetGroupCount(NumActiveSoundProxies, FAudioHardwareRayTracingDirectCS::ThreadGroupSizeX);
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("Audio Hardware Ray Tracing Direct CS"),
        (bAsyncCompute ? ERDGPassFlags::AsyncCompute : ERDGPassFlags::Compute) | ERDGPassFlags::NeverCull,
        AudioHardwareRayTracingDirectCS,
        DirectParameters,
        GroupCountDirect
    );

    // Indirect Sound
    FAudioHardwareRayTracingIndirectCS::FParameters* IndirectParameters = GraphBuilder.AllocParameters<FAudioHardwareRayTracingDirectCS::FParameters>();
    AudioTracing::SetAudioHardwareRayTracingParams(ParamContext, IndirectParameters);
    
    const TShaderRef<FAudioHardwareRayTracingIndirectCS> AudioHardwareRayTracingIndirectCS = ShaderMap->GetShader<FAudioHardwareRayTracingIndirectCS>();
    const FIntVector GroupCountIndirect = FComputeShaderUtils::GetGroupCount(RayDirection->Desc.NumElements, FAudioHardwareRayTracingIndirectCS::ThreadGroupSizeX);
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("Audio Hardware Ray Tracing Indirect CS"),
        (bAsyncCompute ? ERDGPassFlags::AsyncCompute : ERDGPassFlags::Compute) | ERDGPassFlags::NeverCull,
        AudioHardwareRayTracingIndirectCS,
        IndirectParameters,
        GroupCountIndirect
    );

    // Capture the current information. Store the necessary information to process the tracing results received from the GPU.
    FAudioTraceQueryContext& QueryContext = AudioTraceQueryContexts[ValidQueryContextIndex];
    QueryContext.AudioIdArrayCaptured = AudioIdArray;
    QueryContext.ListenerLocationCaptured = ListenerLocation;
    QueryContext.ListenerForwardCaptured = ListenerForward;
    QueryContext.MaxReflectionDepthCaptured = MaxReflectionDepth;
    QueryContext.bIsPending = true;
    QueryContext.QueryID = NextQueryID++;
    QueryContext.SoundLocationsCaptured.Reserve(NumActiveSoundProxies);
    for (int32 i = 0; i < NumActiveSoundProxies; ++i)
    {
        QueryContext.SoundLocationsCaptured.Emplace(AudioIdArray[i], IdRemappedActiveSoundProxies[i].Location);
    }

    AddEnqueueCopyPass(GraphBuilder, QueryContext.DataReadback.Get(), TracedResultBuffer, 0);
    AddEnqueueCopyPass(GraphBuilder, QueryContext.CounterReadback.Get(), ResultCounterBuffer, 0);
#endif
}

void FATSceneViewExtension::UpdateAudioTraceParam_RenderThread(FRHICommandListImmediate& RHICmdList, const FAudioTraceParam& InAudioTraceData)
{
    bShouldTrace = InAudioTraceData.bShouldTrace;
    ListenerLocation = InAudioTraceData.ListenerLocation;
    ListenerForward = InAudioTraceData.ListenerForward;

    const int32 MaxActiveSoundSources = AudioTracing::GetMaxActiveSoundSources();

    AudioIdArray.Reset(MaxActiveSoundSources);
    AudioIdToArrayIndexMap.Reset();
    AudioIdToArrayIndexMap.Reserve(MaxActiveSoundSources);
    IdRemappedActiveSoundProxies.Reset(MaxActiveSoundSources);
    
    NumActiveSoundProxies = InAudioTraceData.ActiveSoundProxies.Num();
    
    if (bShouldTrace && NumActiveSoundProxies > 0)
    {
        // Build Remap Data
        for (const FActiveSoundProxy& Proxy : InAudioTraceData.ActiveSoundProxies)
        {
            const uint32 AudioComponentID = Proxy.AudioID;
            const int32 ArrayIndex = AudioIdArray.Num();

            AudioIdArray.Emplace(AudioComponentID);
            AudioIdToArrayIndexMap.Emplace(AudioComponentID, ArrayIndex);
        }

        // ID Remap
        for (const FActiveSoundProxy& Proxy : InAudioTraceData.ActiveSoundProxies)
        {
            FActiveSoundProxy RemappedProxy;
            RemappedProxy.Location = Proxy.Location; // Absolute world location
            RemappedProxy.AudioID = AudioIdToArrayIndexMap.FindChecked(Proxy.AudioID);

            IdRemappedActiveSoundProxies.Emplace(RemappedProxy);
        }
    }
}

void FATSceneViewExtension::UpdateRayDirectionBuffer_RenderThread(FRHICommandListImmediate& RHICmdList, const TArray<FVector>& NewRayDirections)
{
    // Since the subsystem has already checked the conditions for changing the Directions array, we will follow that decision here and apply it directly without additional checks.
    RayCount = NewRayDirections.Num();
    
    // Release the buffer for reallocation
    if (RayDirection.IsValid())
    {
        RayDirection.SafeRelease();
    }

    FRDGBufferDesc RayDirectionDesc = FRDGBufferDesc::CreateStructuredDesc(sizeof(FVector3f), RayCount);
    AllocatePooledBuffer(RayDirectionDesc, RayDirection, TEXT("AudioTracing.RayDirectionBuffer"));
    
    if (RayDirection.IsValid() && RayCount > 0)
    {
        // Write data to the buffer
        FVector3f* BufferData = static_cast<FVector3f*>(RHICmdList.LockBuffer(RayDirection->GetRHI(), 0, RayCount * sizeof(FVector3f), RLM_WriteOnly));

        for (uint32 i = 0; i < RayCount; ++i)
        {
            BufferData[i] = static_cast<FVector3f>(NewRayDirections[i]);
        }
        
        RHICmdList.UnlockBuffer(RayDirection->GetRHI());
    }

    // Invalidate the payload being copied. This is because the QueryContext depends on the RayDirections at the time the copy was initiated.
    for (FAudioTraceQueryContext& QueryContext : AudioTraceQueryContexts)
    {
        if (QueryContext.bIsPending)
        {
            QueryContext.bIsValid = false;
        }
    }
}

int32 FATSceneViewExtension::GetValidQueryContextIndex()
{
    // Collect the indices of QueryContexts that are not currently performing a copy operation
    TArray<int8> ReadyQueryContextIndices;
    for (int8 i = 0; i < NumReadbackBuffers; ++i)
    {
        const FAudioTraceQueryContext& Context = AudioTraceQueryContexts[i];
        if (!Context.bIsPending || (Context.DataReadback->IsReady() && Context.DataReadback->IsReady()))
        {
            ReadyQueryContextIndices.Add(i);
        }
    }

    int8 LatestValidQueryContextIndex = -1;
    
    if (!ReadyQueryContextIndices.IsEmpty())
    {
        // Find the single payload with the most recent information among the completed queries
        uint64 MaxValidQueryID = LastProcessedQueryID;
        
        for (const int32 PayloadIndex : ReadyQueryContextIndices)
        {
            const FAudioTraceQueryContext& Payload = AudioTraceQueryContexts[PayloadIndex];
            if (Payload.bIsValid && Payload.QueryID > MaxValidQueryID)
            {
                MaxValidQueryID = Payload.QueryID;
                LatestValidQueryContextIndex = PayloadIndex;
            }
        }

        if (LatestValidQueryContextIndex != -1)
        {
            // Process the information from the payload that copied the most recent data
            ProcessReceivedData(LatestValidQueryContextIndex);
        }

        // Reset all available buffers
        for (const int32 PayloadIndex : ReadyQueryContextIndices)
        {
            AudioTraceQueryContexts[PayloadIndex].Reset();
        }

        // If all available buffers have not copied any data (e.g., at the start of the game), use the first index
        if (LatestValidQueryContextIndex == -1)
        {
            LatestValidQueryContextIndex = ReadyQueryContextIndices[0];
        }
    }

    return LatestValidQueryContextIndex;
}

void FATSceneViewExtension::ProcessReceivedData(uint32 QueryContextIndex)
{
    FAudioTraceQueryContext& Payload = AudioTraceQueryContexts[QueryContextIndex];

    const uint32 NumActiveSoundProxiesCaptured = Payload.AudioIdArrayCaptured.Num();

    TArray<uint32> Counter;
    {
        const uint32 CounterNumOfBytes = NumActiveSoundProxiesCaptured * sizeof(uint32);
        uint32* CounterBuffer = static_cast<uint32*>(Payload.CounterReadback->Lock(CounterNumOfBytes));

        Counter.Reserve(NumActiveSoundProxiesCaptured);
        for (uint32 i = 0; i < NumActiveSoundProxiesCaptured; ++i)
        {
            Counter.Emplace(CounterBuffer[i]);
        }
        
        Payload.CounterReadback->Unlock();
    }

    FAudioTraceResult TraceResult;
    TraceResult.TracedAudioData.Reserve(NumActiveSoundProxiesCaptured);
    {
        const uint32 MaxResultsPerSound = RayCount * (Payload.MaxReflectionDepthCaptured + 1);
        const uint32 NumElements = NumActiveSoundProxiesCaptured * MaxResultsPerSound;
        const uint32 DataNumOfBytes = NumElements * sizeof(FTracedAudioData);
        FTracedAudioData* DataBuffer = static_cast<FTracedAudioData*>(Payload.DataReadback->Lock(DataNumOfBytes));

        for (uint32 ActiveSoundIndex = 0; ActiveSoundIndex < NumActiveSoundProxiesCaptured; ++ActiveSoundIndex)
        {
            const uint32 NumTracedData = Counter[ActiveSoundIndex];
            if (NumTracedData == 0)
            {
                continue;
            }
            
            const uint32 AudioID = Payload.AudioIdArrayCaptured[ActiveSoundIndex];

            TArray<FTracedAudioData>& TargetDataArray = TraceResult.TracedAudioData.Emplace(AudioID);
            TargetDataArray.Reserve(NumTracedData);
            
            const uint32 OffsetStart = MaxResultsPerSound * ActiveSoundIndex;
            for (uint32 DataIndex = 0; DataIndex < NumTracedData; ++DataIndex)
            {
                FTracedAudioData& TracedAudioData = TargetDataArray.Emplace_GetRef(DataBuffer[OffsetStart + DataIndex]);
                TracedAudioData.AudioID = AudioID;
            }
        }
        
        Payload.DataReadback->Unlock();
    }

    TraceResult.ListenerLocation = Payload.ListenerLocationCaptured;
    TraceResult.ListenerForward = Payload.ListenerForwardCaptured;
    TraceResult.SoundLocations = MoveTemp(Payload.SoundLocationsCaptured);

    AudioTraceResultQueue.Enqueue(TraceResult);

    LastProcessedQueryID = Payload.QueryID;
}
