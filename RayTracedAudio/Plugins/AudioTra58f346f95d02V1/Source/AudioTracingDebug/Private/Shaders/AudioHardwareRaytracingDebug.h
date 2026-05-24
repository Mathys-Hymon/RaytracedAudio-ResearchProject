// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "SceneUniformBuffer.h"
#include "SceneView.h"

class FAudioHardwareRaytracingDebugMaterialCS : public FGlobalShader
{
public:
    DECLARE_GLOBAL_SHADER(FAudioHardwareRaytracingDebugMaterialCS)
    SHADER_USE_PARAMETER_STRUCT(FAudioHardwareRaytracingDebugMaterialCS, FGlobalShader)

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, OutTexture)
    
        SHADER_PARAMETER(uint32, CustomPrimitiveDataStartSlotIndex)

        SHADER_PARAMETER_RDG_BUFFER_SRV(RaytracingAccelerationStructure, TLAS)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<uint32>, HitGroupData)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer, RayTracingSceneMetadata)

        SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, ViewUniformBuffer)
        SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FSceneUniformParameters, Scene)
    END_SHADER_PARAMETER_STRUCT()
    
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);

    static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);

    static constexpr uint8 ThreadGroupSizeX = 16;
    static constexpr uint8 ThreadGroupSizeY = 16;
};
