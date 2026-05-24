// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "AudioHardwareRaytracingDebug.h"
#include "ShaderCompilerCore.h"

IMPLEMENT_GLOBAL_SHADER(FAudioHardwareRaytracingDebugMaterialCS, "/AudioTracing/Private/AudioRayTracingDebugMaterial.usf", "AudioHardwareRaytracingDebugMaterialCS", SF_Compute)

bool FAudioHardwareRaytracingDebugMaterialCS::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
    return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
}

void FAudioHardwareRaytracingDebugMaterialCS::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
    FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

    OutEnvironment.SetDefine(TEXT("LUMEN_HARDWARE_INLINE_RAYTRACING"), 1);
    OutEnvironment.SetDefine(TEXT("AUDIO_HARDWARE_INLINE_RAYTRACING"), 1);
    OutEnvironment.CompilerFlags.Add(CFLAG_InlineRayTracing);
    
    OutEnvironment.SetDefine(TEXT("THREADS_X"), ThreadGroupSizeX);
    OutEnvironment.SetDefine(TEXT("THREADS_Y"), ThreadGroupSizeY);
}
