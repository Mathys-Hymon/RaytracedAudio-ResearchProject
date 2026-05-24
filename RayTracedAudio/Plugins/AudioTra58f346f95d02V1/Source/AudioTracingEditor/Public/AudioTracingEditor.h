// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMenuBuilder;
class IAssetTypeActions;

class FAudioTracingEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

private:
    void RegisterModuleMenus();
    
    void AddSoundMaterialToSelectedActors();
    void RemoveSoundMaterialFromSelectedActors();

    void RefreshSelectedActors();
    
};
