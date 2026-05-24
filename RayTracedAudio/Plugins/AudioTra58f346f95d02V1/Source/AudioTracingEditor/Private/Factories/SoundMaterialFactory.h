// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SoundMaterialFactory.generated.h"

/**
 * 
 */
UCLASS()
class USoundMaterialFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	USoundMaterialFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	virtual bool ShouldShowInNewMenu() const override;
};
