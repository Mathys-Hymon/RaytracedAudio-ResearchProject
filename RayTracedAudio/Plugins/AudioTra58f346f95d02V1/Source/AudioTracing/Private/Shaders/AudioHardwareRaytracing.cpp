// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "AudioHardwareRaytracing.h"

#include "AudioTracing.h"
#include "ScenePrivate.h"
#include "ShaderCompilerCore.h"
#include "SceneRendering.h"

static TAutoConsoleVariable<int32> CVarAudioTracingHardwareRayTracing(
    TEXT("AudioTracing.HardwareRayTracing"),
    1,
    TEXT("Enables or disables the entire hardware-accelerated audio tracing feature.\n")
    TEXT("0: Disable\n")
    TEXT("1: Enable (default)"),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<int32> CVarAudioTracingMaxReflectionDepth(
    TEXT("AudioTracing.HardwareRayTracing.MaxReflectionDepth"),
    16,
    TEXT("The maximum number of times a ray can reflect off surfaces. Higher values produce more realistic reverberation but increase computational cost.\n")
    TEXT("Default: 16."),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<float> CVarAudioTracingRayTracingNormalBias(
    TEXT("AudioTracing.HardwareRayTracing.RayTracingNormalBias"),
    0.1f,
    TEXT("A small distance in centimeters to offset rays from surfaces to prevent self-intersection artifacts.\n")
    TEXT("Adjust this value if you see incorrect shadowing or artifacts at surface contacts.\n")
    TEXT("Default: 0.1 cm."),
    ECVF_RenderThreadSafe
);

bool AudioTracing::UseHardwareRaytracing()
{
#if RHI_RAYTRACING
    bool bIsEnabled = false;
    if ( IsInRenderingThread() )
    {
        bIsEnabled = CVarAudioTracingHardwareRayTracing.GetValueOnRenderThread() > 0;
    }
    else if ( IsInGameThread() )
    {
        bIsEnabled = CVarAudioTracingHardwareRayTracing.GetValueOnGameThread() > 0;
    }
    else 
    {
        bIsEnabled = CVarAudioTracingHardwareRayTracing.GetValueOnAnyThread() > 0;
    }
    return GRHISupportsInlineRayTracing
        && IsRayTracingEnabled()
        && bIsEnabled;
#else
    return false;
#endif
}
    
uint32 AudioTracing::GetMaxReflectionDepth()
{
    const int32 MaxReflectionDepth = CVarAudioTracingMaxReflectionDepth.GetValueOnRenderThread();
    return static_cast<uint32>(MaxReflectionDepth < 0 ? 16 : MaxReflectionDepth);
}

float AudioTracing::GetRayTracingNormalBias()
{
    const int32 RayTracingNormalBias = CVarAudioTracingRayTracingNormalBias.GetValueOnRenderThread();
    return RayTracingNormalBias;
}

void AudioTracing::SetAudioHardwareRayTracingParams(const FAudioHardwareRayTracingContext& Context,
    FAudioHardwareRayTracingParameters* OutParams)
{
    const FViewInfo& ViewInfo = static_cast<const FViewInfo&>(Context.View);
    FScene* Scene = Context.View.Family->Scene->GetRenderScene();
    FRayTracingScene& RayTracingScene = Scene->RayTracingScene;
    
    OutParams->RayDirections = Context.RayDirections;
    OutParams->ActiveSoundProxies = Context.ActiveSoundProxies;
    OutParams->TracedResult = Context.TracedResult;
    OutParams->ResultCounter = Context.ResultCounter;
    
    OutParams->TranslatedListenerPosition = Context.TranslatedListenerPosition;
    OutParams->ActiveSoundProxyCount = Context.ActiveSoundProxyCount;
    OutParams->RayCount = Context.RayCount;
    OutParams->MaxReflectionDepth = Context.MaxReflectionDepth;
    OutParams->MaxTraceDistance = GetMaxTraceDistance();

    OutParams->AudioTracingNormalBias = GetRayTracingNormalBias();
    OutParams->CustomPrimitiveDataStartSlotIndex = GetCustomPrimitiveDataStartFloat4Index();

    OutParams->TLAS = RayTracingScene.GetLayerView(ERayTracingSceneLayer::Base);
    OutParams->HitGroupData = ViewInfo.LumenHardwareRayTracingHitDataBuffer ? Context.GraphBuilder.CreateSRV(ViewInfo.LumenHardwareRayTracingHitDataBuffer) : nullptr;
    OutParams->RayTracingSceneMetadata = ViewInfo.InlineRayTracingBindingDataBuffer ? Context.GraphBuilder.CreateSRV(ViewInfo.InlineRayTracingBindingDataBuffer) : nullptr;

    OutParams->ViewUniformBuffer = ViewInfo.ViewUniformBuffer;
    OutParams->Scene = ViewInfo.GetSceneUniforms().GetBuffer(Context.GraphBuilder);
}


IMPLEMENT_GLOBAL_SHADER(FAudioHardwareRayTracingDirectCS, "/AudioTracing/Private/AudioRayTracing.usf", "AudioHardwareRayTracingDirectCS", SF_Compute)

bool FAudioHardwareRayTracingDirectCS::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
    return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
}

void FAudioHardwareRayTracingDirectCS::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
    FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

    OutEnvironment.SetDefine(TEXT("LUMEN_HARDWARE_INLINE_RAYTRACING"), 1);
    OutEnvironment.SetDefine(TEXT("AUDIO_HARDWARE_INLINE_RAYTRACING"), 1);
    OutEnvironment.CompilerFlags.Add(CFLAG_InlineRayTracing);
    
    OutEnvironment.SetDefine(TEXT("THREADS_X"), ThreadGroupSizeX);
}


IMPLEMENT_GLOBAL_SHADER(FAudioHardwareRayTracingIndirectCS, "/AudioTracing/Private/AudioRayTracing.usf", "AudioHardwareRayTracingIndirectCS", SF_Compute)

bool FAudioHardwareRayTracingIndirectCS::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
    return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
}

void FAudioHardwareRayTracingIndirectCS::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
    FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

    OutEnvironment.SetDefine(TEXT("LUMEN_HARDWARE_INLINE_RAYTRACING"), 1);
    OutEnvironment.SetDefine(TEXT("AUDIO_HARDWARE_INLINE_RAYTRACING"), 1);
    OutEnvironment.CompilerFlags.Add(CFLAG_InlineRayTracing);
    
    OutEnvironment.SetDefine(TEXT("THREADS_X"), ThreadGroupSizeX);
}
