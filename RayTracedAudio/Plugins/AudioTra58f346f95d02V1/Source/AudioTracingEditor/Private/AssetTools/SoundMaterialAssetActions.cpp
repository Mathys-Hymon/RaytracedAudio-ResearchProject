// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "AssetTools/SoundMaterialAssetActions.h"

#include "Sound/SoundMaterial.h"


FText FSoundMaterialAssetActions::GetName() const
{
    return FText::FromString("Sound Material");
}

FColor FSoundMaterialAssetActions::GetTypeColor() const
{
    return FColor(89, 146, 179);
}

UClass* FSoundMaterialAssetActions::GetSupportedClass() const
{
    return USoundMaterial::StaticClass();
}

uint32 FSoundMaterialAssetActions::GetCategories()
{
    return EAssetTypeCategories::Sounds;
}
