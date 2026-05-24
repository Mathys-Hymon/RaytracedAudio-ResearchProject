// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "ATDebugSceneViewExtension.h"

#include "Shaders/AudioHardwareRaytracingDebug.h"
#include "AudioTracing.h"
#include "ScenePrivate.h"
#include "SceneView.h"
#include "PostProcess/PostProcessInputs.h"

static TAutoConsoleVariable<int32> CVarAudioTracingDebugSoundMaterial(
    TEXT("AudioTracing.HardwareRayTracing.DebugSoundMaterial"),
    0,
    TEXT("Enables a debug visualization mode for the Audio Tracing hardware ray tracing pass, overriding the material output.\n")
    TEXT("Note: This only works during active gameplay, not in the editor viewport.\n"),
    ECVF_RenderThreadSafe
);


FATDebugSceneViewExtension::FATDebugSceneViewExtension(const FAutoRegister& AutoRegister)
    : FSceneViewExtensionBase(AutoRegister)
{
}

FATDebugSceneViewExtension::~FATDebugSceneViewExtension()
{
}

void FATDebugSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
    FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

#if RHI_RAYTRACING
    if (IsHardwareRayTracingAvailableForView(View))
    {
        if (CVarAudioTracingDebugSoundMaterial.GetValueOnRenderThread() > 0)
        {
            DebugSoundMaterial(GraphBuilder, View, Inputs);
        }
    }
#endif
}

bool FATDebugSceneViewExtension::IsHardwareRayTracingAvailableForView(const FSceneView& View) const
{
    if (!View.bAllowRayTracing)
    {
        return false;
    }
    
    const FViewInfo& ViewInfo = static_cast<const FViewInfo&>(View);
    if (!ViewInfo.InlineRayTracingBindingDataBuffer)
    {
        return false;
    }

    FScene* Scene = View.Family->Scene->GetRenderScene();
    if (!Scene || !Scene->RayTracingScene.GetRHIRayTracingScene(ERayTracingSceneLayer::Base))
    {
        return false;
    }

    return true;
}

void FATDebugSceneViewExtension::DebugSoundMaterial(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
#if RHI_RAYTRACING
    checkSlow(View.bIsViewInfo);

    const FViewInfo& ViewInfo = static_cast<const FViewInfo&>(View);
    const FScene* Scene = View.Family->Scene->GetRenderScene();
    
    TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures = Inputs.SceneTextures;

    const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
    const EPixelFormat OutputFormat = SceneTextures->GetContents()->SceneColorTexture->Desc.Format;

    const FRDGTextureDesc TextureDesc = FRDGTextureDesc::Create2D(Viewport.Size(), OutputFormat, FClearValueBinding::Black, TexCreate_ShaderResource | TexCreate_UAV);
    const FRDGTextureRef MaterialDebugResult = GraphBuilder.CreateTexture(TextureDesc, TEXT("AudioTracing.DebugSoundMaterial.MaterialDebugResult"));
    
    const FRayTracingScene& RayTracingScene = Scene->RayTracingScene;

    FAudioHardwareRaytracingDebugMaterialCS::FParameters* Parameters = GraphBuilder.AllocParameters<FAudioHardwareRaytracingDebugMaterialCS::FParameters>();
    Parameters->OutTexture = GraphBuilder.CreateUAV(MaterialDebugResult);
    Parameters->CustomPrimitiveDataStartSlotIndex = AudioTracing::GetCustomPrimitiveDataStartFloat4Index();

    Parameters->TLAS = RayTracingScene.GetLayerView(ERayTracingSceneLayer::Base);
    Parameters->HitGroupData = ViewInfo.LumenHardwareRayTracingHitDataBuffer ? GraphBuilder.CreateSRV(ViewInfo.LumenHardwareRayTracingHitDataBuffer) : nullptr;
    Parameters->RayTracingSceneMetadata = ViewInfo.InlineRayTracingBindingDataBuffer ? GraphBuilder.CreateSRV(ViewInfo.InlineRayTracingBindingDataBuffer) : nullptr;

    Parameters->ViewUniformBuffer = ViewInfo.ViewUniformBuffer;
    Parameters->Scene = ViewInfo.GetSceneUniforms().GetBuffer(GraphBuilder);

    FGlobalShaderMap* ShaderMap = ViewInfo.ShaderMap;
    const TShaderRef<FAudioHardwareRaytracingDebugMaterialCS> AudioHardwareRaytracingDebugMaterialCS = ShaderMap->GetShader<FAudioHardwareRaytracingDebugMaterialCS>();

    const bool bAsyncCompute = GSupportsEfficientAsyncCompute && (GNumExplicitGPUsForRendering == 1);

    const FIntPoint ThreadCount = Viewport.Size();
    const FIntVector GroupCount = FComputeShaderUtils::GetGroupCount(ThreadCount,
        FIntPoint(FAudioHardwareRaytracingDebugMaterialCS::ThreadGroupSizeX, FAudioHardwareRaytracingDebugMaterialCS::ThreadGroupSizeY)
    );
    
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("Audio Hardware Raytracing Debug Material CS"),
        (bAsyncCompute ? ERDGPassFlags::AsyncCompute : ERDGPassFlags::Compute) | ERDGPassFlags::NeverCull,
        AudioHardwareRaytracingDebugMaterialCS,
        Parameters,
        GroupCount
    );

    AddCopyTexturePass(GraphBuilder, MaterialDebugResult, SceneTextures->GetContents()->SceneColorTexture);
#endif
}
