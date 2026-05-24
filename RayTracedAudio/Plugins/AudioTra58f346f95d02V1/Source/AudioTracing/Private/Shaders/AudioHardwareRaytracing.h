// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "SceneUniformBuffer.h"
#include "SceneView.h"

struct FAudioHardwareRayTracingContext;

namespace AudioTracing
{
    bool UseHardwareRaytracing();
    uint32 GetMaxReflectionDepth();
    float GetRayTracingNormalBias();

    BEGIN_SHADER_PARAMETER_STRUCT(FAudioHardwareRayTracingParameters, )
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<FVector3f>, RayDirections)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<FActiveSoundProxy>, ActiveSoundProxies)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FTracedAudioData>, TracedResult)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<uint32>, ResultCounter)

        SHADER_PARAMETER(FVector3f, TranslatedListenerPosition)
        SHADER_PARAMETER(uint32, ActiveSoundProxyCount)
        SHADER_PARAMETER(uint32, RayCount)
        SHADER_PARAMETER(uint32, MaxReflectionDepth)
        SHADER_PARAMETER(float, MaxTraceDistance)

        SHADER_PARAMETER(float, AudioTracingNormalBias)
        SHADER_PARAMETER(uint32, CustomPrimitiveDataStartSlotIndex)

        SHADER_PARAMETER_RDG_BUFFER_SRV(RaytracingAccelerationStructure, TLAS)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<Lumen::FHitGroupRootConstants>, HitGroupData)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer, RayTracingSceneMetadata)

        SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, ViewUniformBuffer)
        SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FSceneUniformParameters, Scene)
    END_SHADER_PARAMETER_STRUCT()

    void SetAudioHardwareRayTracingParams(const FAudioHardwareRayTracingContext& Context, FAudioHardwareRayTracingParameters* OutParams);
}


struct FAudioHardwareRayTracingContext
{
    FRDGBuilder& GraphBuilder;
    const FSceneView& View;
    
    FRDGBufferSRVRef RayDirections;
    FRDGBufferSRVRef ActiveSoundProxies;
    FRDGBufferUAVRef TracedResult;
    FRDGBufferUAVRef ResultCounter;

    const FVector3f TranslatedListenerPosition;
    uint32 ActiveSoundProxyCount;
    uint32 RayCount;
    uint32 MaxReflectionDepth;

    FAudioHardwareRayTracingContext(FRDGBuilder& InGraphBuilder,
        const FSceneView& InView,
        FRDGBufferSRVRef InRayDirections,
        FRDGBufferSRVRef InActiveSoundProxies,
        FRDGBufferUAVRef InTracedResult,
        FRDGBufferUAVRef InResultCounter,
        const FVector3f& InTranslatedListenerPosition,
        uint32 InActiveSoundProxyCount,
        uint32 InRayCount,
        uint32 InMaxReflectionDepth)
        : GraphBuilder(InGraphBuilder)
        , View(InView)
        , RayDirections(InRayDirections)
        , ActiveSoundProxies(InActiveSoundProxies)
        , TracedResult(InTracedResult)
        , ResultCounter(InResultCounter)
        , TranslatedListenerPosition(InTranslatedListenerPosition)
        , ActiveSoundProxyCount(InActiveSoundProxyCount)
        , RayCount(InRayCount)
        , MaxReflectionDepth(InMaxReflectionDepth)
    {}
};


class FAudioHardwareRayTracingDirectCS : public FGlobalShader
{
public:
    DECLARE_GLOBAL_SHADER(FAudioHardwareRayTracingDirectCS)
    SHADER_USE_PARAMETER_STRUCT(FAudioHardwareRayTracingDirectCS, FGlobalShader)

    using FParameters = AudioTracing::FAudioHardwareRayTracingParameters;

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);

    static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);

    static constexpr uint8 ThreadGroupSizeX = 64;
};


class FAudioHardwareRayTracingIndirectCS : public FGlobalShader
{
public:
    DECLARE_GLOBAL_SHADER(FAudioHardwareRayTracingIndirectCS)
    SHADER_USE_PARAMETER_STRUCT(FAudioHardwareRayTracingIndirectCS, FGlobalShader)

    using FParameters = AudioTracing::FAudioHardwareRayTracingParameters;
    
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);

    static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);

    static constexpr uint8 ThreadGroupSizeX = 64;
};

