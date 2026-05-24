// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "ActorUtility/AudioTracingActorActionUtility.h"

#include "Editor.h"
#include "Selection.h"

void UAudioTracingActorActionUtility::AddSoundMaterialToSelectedActors()
{
	USelection* SelectedActors = GEditor->GetSelectedActors();

	UE_LOG(LogTemp, Warning, TEXT("Selected Actors : %d"), SelectedActors->Num());
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (Actor)
		{
			// Add Sound Material to the Actor
			// This is a placeholder for actual implementation
			UE_LOG(LogTemp, Warning, TEXT("Adding Sound Material to Actor: %s"), *Actor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Selected object is not an Actor."));
		}
	}
}

void UAudioTracingActorActionUtility::RemoveSoundMaterialFromSelectedActors()
{
	
}
