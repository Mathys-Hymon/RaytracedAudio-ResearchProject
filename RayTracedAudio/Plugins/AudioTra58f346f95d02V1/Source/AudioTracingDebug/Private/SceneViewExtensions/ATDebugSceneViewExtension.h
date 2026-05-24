// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"

class FATDebugSceneViewExtension : public FSceneViewExtensionBase
{
public:
    FATDebugSceneViewExtension(const FAutoRegister& AutoRegister);
    virtual ~FATDebugSceneViewExtension() override;

    virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;

private:
    bool IsHardwareRayTracingAvailableForView(const FSceneView& View) const;

    void DebugSoundMaterial(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs);
};
