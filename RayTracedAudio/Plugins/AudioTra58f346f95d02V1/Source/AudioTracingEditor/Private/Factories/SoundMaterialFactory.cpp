// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "Factories/SoundMaterialFactory.h"

#include "Sound/SoundMaterial.h"


USoundMaterialFactory::USoundMaterialFactory()
{
    SupportedClass = USoundMaterial::StaticClass();
    bCreateNew = true;
    bEditAfterNew = true;
}

UObject* USoundMaterialFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
    UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<USoundMaterial>(InParent, Class, Name, Flags);
}

bool USoundMaterialFactory::ShouldShowInNewMenu() const
{
    return true;
}
