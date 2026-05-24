// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "AudioTracingDebugSubsystem.h"

#include "Editor.h"
#include "SceneViewExtension.h"
#include "Components/ATSoundMaterialComponent.h"
#include "SceneViewExtensions/ATDebugSceneViewExtension.h"


void UAudioTracingDebugSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    ATDebugSceneViewExtension = FSceneViewExtensions::NewExtension<FATDebugSceneViewExtension>();
}

void UAudioTracingDebugSubsystem::Deinitialize()
{
    Super::Deinitialize();

    if (ATDebugSceneViewExtension.IsValid())
    {
        ATDebugSceneViewExtension.Reset();
        ATDebugSceneViewExtension = nullptr;
    }
}
