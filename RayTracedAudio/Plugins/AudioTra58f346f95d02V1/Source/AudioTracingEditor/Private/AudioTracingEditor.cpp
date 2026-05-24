// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "AudioTracingEditor.h"


#include "PropertyEditorModule.h"
#include "ScopedTransaction.h"
#include "AssetTools/SoundMaterialAssetActions.h"
#include "Components/PrimitiveComponent.h"

#include "Selection.h"
#include "ToolMenus.h"
#include "Components/ATSoundMaterialComponent.h"

#define LOCTEXT_NAMESPACE "FAudioTracingEditorModule"

void FAudioTracingEditorModule::StartupModule()
{
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

    const TSharedPtr<FSoundMaterialAssetActions> Actions = MakeShareable(new FSoundMaterialAssetActions());
    AssetTools.RegisterAssetTypeActions(Actions.ToSharedRef());

    CreatedAssetTypeActions.Add(Actions);

    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAudioTracingEditorModule::RegisterModuleMenus));
}

void FAudioTracingEditorModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
    {
        IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
        for (auto Action : CreatedAssetTypeActions)
        {
            AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
        }
    }
    CreatedAssetTypeActions.Empty();
}

void FAudioTracingEditorModule::RegisterModuleMenus()
{
    UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.ActorContextMenu");

    FToolMenuSection& Section = Menu->AddSection("AudioTracing", FText::FromString("AudioTracing"), FToolMenuInsert("ActorOptions", EToolMenuInsertType::Before));
    
    Section.AddMenuEntry(
        "AddSoundMaterial",
        FText::FromString("Add Audio Tracing Sound Material Components"),
        FText::FromString("Add ATSoundMaterialComponents to selected actors. Components will be attached to the all primitive components of the actors."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FAudioTracingEditorModule::AddSoundMaterialToSelectedActors))
    );

    Section.AddMenuEntry(
        "RemoveSoundMaterial",
        FText::FromString("Remove Audio Tracing Sound Material Components"),
        FText::FromString("Remove ATSoundMaterialComponents from selected actors. All Sound Material Components will be removed from the actors."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FAudioTracingEditorModule::RemoveSoundMaterialFromSelectedActors))
    );
}

void FAudioTracingEditorModule::AddSoundMaterialToSelectedActors()
{
    const FScopedTransaction ScopedTransaction(FText::FromString("Add Sound Material Components"));
    USelection* SelectedActors = GEditor->GetSelectedActors();

    if (SelectedActors->Num() <= 0)
    {
        return;
    }

    for (FSelectionIterator It(*SelectedActors); It; ++It)
    {
        AActor* Actor = Cast<AActor>(*It);

        if (!Actor)
        {
            continue;
        }

        Actor->Modify();

        TArray<TObjectPtr<UPrimitiveComponent>> PrimitiveComponents;
        Actor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);

        for (UPrimitiveComponent* Comp : PrimitiveComponents)
        {
            if (!Comp)
            {
                continue;
            }
            
            bool bAlreadyHasComp = false;
            for (USceneComponent* Child : Comp->GetAttachChildren())
            {
                if (Child && Child->IsA<UATSoundMaterialComponent>())
                {
                    bAlreadyHasComp = true;
                    break;
                }
            }
            if (bAlreadyHasComp)
            {
                continue;
            }
            
            UATSoundMaterialComponent* NewATSMComponent = NewObject<UATSoundMaterialComponent>(Actor, UATSoundMaterialComponent::StaticClass(), NAME_None, RF_Transactional);
            NewATSMComponent->OnComponentCreated();
            NewATSMComponent->Modify();
            NewATSMComponent->AttachToComponent(Comp, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
            Actor->AddInstanceComponent(NewATSMComponent);
            NewATSMComponent->RegisterComponent();
        }
    }
    RefreshSelectedActors();
}

void FAudioTracingEditorModule::RemoveSoundMaterialFromSelectedActors()
{
    const FScopedTransaction ScopedTransaction(FText::FromString("Remove Sound Material Components"));
    USelection* SelectedActors = GEditor->GetSelectedActors();

    if (SelectedActors->Num() <= 0)
    {
        return;
    }

    for (FSelectionIterator It(*SelectedActors); It; ++It)
    {
        AActor* Actor = Cast<AActor>(*It);

        if (!Actor)
        {
            continue;
        }

        Actor->Modify();

        TArray<TObjectPtr<UATSoundMaterialComponent>> OwnedSoundMaterialComponents;
        Actor->GetComponents<UATSoundMaterialComponent>(OwnedSoundMaterialComponents);

        TArray<UATSoundMaterialComponent*> ComponentsToRemove;

        for (UATSoundMaterialComponent* Comp : OwnedSoundMaterialComponents)
        {
            if (!Comp)
            {
                continue;
            }
            ComponentsToRemove.Add(Comp);
        }

        for (UATSoundMaterialComponent* ATSMComponent : ComponentsToRemove)
        {
            if (ATSMComponent)
            {
                ATSMComponent->Modify();
                Actor->RemoveInstanceComponent(ATSMComponent);
                ATSMComponent->DestroyComponent(false);
            }
        }
    }
    RefreshSelectedActors();
}

void FAudioTracingEditorModule::RefreshSelectedActors()
{
    if (!GEditor) return;

    TArray<AActor*> SelectedActors;
    for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
    {
        if (AActor* Actor = Cast<AActor>(*It))
        {
            SelectedActors.Add(Actor);
        }
    }

    GEditor->SelectNone(false, true);

    for (AActor* Actor : SelectedActors)
    {
        GEditor->SelectActor(Actor, true, true);
    }

    GEditor->RedrawLevelEditingViewports();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAudioTracingEditorModule, AudioTracingEditor)
