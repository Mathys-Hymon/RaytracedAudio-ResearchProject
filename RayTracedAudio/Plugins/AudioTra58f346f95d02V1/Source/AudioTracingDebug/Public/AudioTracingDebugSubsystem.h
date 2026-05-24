// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "AudioTracingDebugSubsystem.generated.h"

class FATDebugSceneViewExtension;

/**
 * 
 */
UCLASS()
class AUDIOTRACINGDEBUG_API UAudioTracingDebugSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

private:
	TSharedPtr<FATDebugSceneViewExtension, ESPMode::ThreadSafe> ATDebugSceneViewExtension;
};
