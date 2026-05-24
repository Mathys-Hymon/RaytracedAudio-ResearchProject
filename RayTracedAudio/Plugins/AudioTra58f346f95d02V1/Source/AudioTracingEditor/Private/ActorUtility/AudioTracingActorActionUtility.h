// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorActionUtility.h"
#include "AudioTracingActorActionUtility.generated.h"

/**
 * 
 */
UCLASS()
class UAudioTracingActorActionUtility : public UActorActionUtility
{
	GENERATED_BODY()
	
public:

	// TODO: Later if need, remove comment and Finish implement this functions 
	UFUNCTION(/* CallInEditor */)
	void AddSoundMaterialToSelectedActors();
	UFUNCTION(/* CallInEditor */)
	void RemoveSoundMaterialFromSelectedActors();
	
};
