// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "Components/ATSoundMaterialComponent.h"

#include "AudioTracing.h"
#include "AudioTracingLog.h"
#include "TimerManager.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Sound/SoundMaterial.h"


UATSoundMaterialComponent::UATSoundMaterialComponent()
    : bOverrideSoundMaterial(false)
    , ScatteringFactor(USoundMaterial::DefaultScatteringFactor)
    , ReflectionFactor(USoundMaterial::DefaultReflectionFactor)
    , AbsorptionCoefficient(USoundMaterial::DefaultAbsorptionCoefficient)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UATSoundMaterialComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!bOverrideSoundMaterial && SoundMaterial)
    {
        ScatteringFactor = SoundMaterial->GetScatteringFactor();
        ReflectionFactor = SoundMaterial->GetReflectionFactor();
        AbsorptionCoefficient = SoundMaterial->GetAbsorptionCoefficient();
    }

    SetSoundMaterialCustomPrimitiveData();
}

void UATSoundMaterialComponent::OnAttachmentChanged()
{
    Super::OnAttachmentChanged();

    if (GetAttachParent())
    {
        SetSoundMaterialCustomPrimitiveData();
    }
    else
    {
        ClearSoundMaterialCustomPrimitiveData(CachedParent.Get());
    }

    CachedParent = Cast<UPrimitiveComponent>(GetAttachParent());
    
#if WITH_EDITOR
    ApplySoundMaterialDataDelayed();
#endif
}

void UATSoundMaterialComponent::DestroyComponent(bool bPromoteChildren)
{
    ClearSoundMaterialCustomPrimitiveData();
    
    Super::DestroyComponent(bPromoteChildren);
}

void UATSoundMaterialComponent::PostLoad()
{
    Super::PostLoad();

#if WITH_EDITOR
    if (GetWorld() && GetWorld()->IsEditorWorld())
    {
        SetSoundMaterial(SoundMaterial);
    }
#endif
}

void UATSoundMaterialComponent::OnRegister()
{
    Super::OnRegister();

    SetSoundMaterial(SoundMaterial);

#if WITH_EDITOR
    ApplySoundMaterialDataDelayed();
#endif
}

void UATSoundMaterialComponent::OnUnregister()
{
#if WITH_EDITOR
    UnbindAssetDelegate();
#endif
    
    Super::OnUnregister();
}

#if WITH_EDITOR
void UATSoundMaterialComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.Property)
    {
        if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UATSoundMaterialComponent, SoundMaterial))
        {
            SetSoundMaterial(SoundMaterial);
        }
        else
        {
            const bool bShouldUpdateCustomPrimitiveData = PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UATSoundMaterialComponent, bOverrideSoundMaterial) ||
                PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UATSoundMaterialComponent, ScatteringFactor) ||
                PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UATSoundMaterialComponent, ReflectionFactor) ||
                PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UATSoundMaterialComponent, AbsorptionCoefficient);

            if (bShouldUpdateCustomPrimitiveData)
            {
                SetSoundMaterialCustomPrimitiveData();
            }
        }
    }
}

void UATSoundMaterialComponent::PreEditUndo()
{
    Super::PreEditUndo();

    UnbindAssetDelegate();
}

void UATSoundMaterialComponent::PostEditUndo()
{
    Super::PostEditUndo();

    SetSoundMaterial(SoundMaterial);
}
#endif

float UATSoundMaterialComponent::GetScatteringFactor() const
{
    if (HasBegunPlay())
    {
        return ScatteringFactor;
    }
    
    if (bOverrideSoundMaterial)
    {
        return ScatteringFactor;
    }
    if (SoundMaterial)
    {
        return SoundMaterial->GetScatteringFactor();
    }
    return USoundMaterial::DefaultScatteringFactor;
}

float UATSoundMaterialComponent::GetReflectionFactor() const
{
    if (HasBegunPlay())
    {
        return ReflectionFactor;
    }
    
    if (bOverrideSoundMaterial)
    {
        return ReflectionFactor;
    }
    if (SoundMaterial)
    {
        return SoundMaterial->GetReflectionFactor();
    }
    return USoundMaterial::DefaultReflectionFactor;
}

float UATSoundMaterialComponent::GetAbsorptionCoefficient() const
{
    if (HasBegunPlay())
    {
        return AbsorptionCoefficient;
    }
    
    if (bOverrideSoundMaterial)
    {
        return AbsorptionCoefficient;
    }
    if (SoundMaterial)
    {
        return SoundMaterial->GetAbsorptionCoefficient();
    }
    return USoundMaterial::DefaultAbsorptionCoefficient;
}

void UATSoundMaterialComponent::SetComponentOverrideSoundMaterial(bool bOverride)
{
    bOverrideSoundMaterial = bOverride;
    SetSoundMaterialCustomPrimitiveData();
}

void UATSoundMaterialComponent::SetScatteringFactor(float NewScatteringFactor)
{
    if (HasBegunPlay())
    {
        ScatteringFactor = FMath::Clamp(NewScatteringFactor, 0.f, 1.f);
        SetSoundMaterialCustomPrimitiveData();
    }
}

void UATSoundMaterialComponent::SetReflectionFactor(float NewReflectionFactor)
{
    if (HasBegunPlay())
    {
        ReflectionFactor = FMath::Clamp(NewReflectionFactor, 0.f, 1.f);
        SetSoundMaterialCustomPrimitiveData();
    }
}

void UATSoundMaterialComponent::SetAbsorptionCoefficient(float NewAbsorptionCoefficient)
{
    if (HasBegunPlay())
    {
        AbsorptionCoefficient = FMath::Max(NewAbsorptionCoefficient, 0.f);
        SetSoundMaterialCustomPrimitiveData();
    }
}

void UATSoundMaterialComponent::SetSoundMaterial(USoundMaterial* NewMaterial)
{
    SoundMaterial = NewMaterial;

    if (HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject | RF_MirroredGarbage))
    {
        return;
    }

    if (HasBegunPlay())
    {
        ScatteringFactor = SoundMaterial ? SoundMaterial->GetScatteringFactor() : USoundMaterial::DefaultScatteringFactor;
        ReflectionFactor = SoundMaterial ? SoundMaterial->GetReflectionFactor() : USoundMaterial::DefaultReflectionFactor;
        AbsorptionCoefficient = SoundMaterial ? SoundMaterial->GetAbsorptionCoefficient() : USoundMaterial::DefaultAbsorptionCoefficient;
    }
#if WITH_EDITOR
    else
    {
        if (SoundMaterial)
        {
            BoundSoundMaterial = NewMaterial;
            if (BoundSoundMaterial.IsValid() && !BoundSoundMaterial->OnSoundMaterialPropertyChanged.IsBoundToObject(this))
            {
                BoundSoundMaterial->OnSoundMaterialPropertyChanged.AddUObject(this, &UATSoundMaterialComponent::OnSoundMaterialPropertyChanged);
            }
        }
    }
#endif
    
    SetSoundMaterialCustomPrimitiveData();
}

void UATSoundMaterialComponent::SetSoundMaterialCustomPrimitiveData() const
{
    if (UPrimitiveComponent* ParentPrimitiveComp = Cast<UPrimitiveComponent>(GetAttachParent()))
    {
        const int32 StartFloat4Index = AudioTracing::GetCustomPrimitiveDataStartFloat4Index();
            
        if (0 <= StartFloat4Index && StartFloat4Index < FCustomPrimitiveData::NumCustomPrimitiveDataFloat4s)
        {
            const int32 StartIndex = StartFloat4Index * 4;

            /**
             * Packs the scattering factor by adding 1.0f before writing it to the Custom Primitive Data.
             * This allows the shader to distinguish between a user-set 0.0f and the default 0.0f of an unset slot.
             *
             * The shader will decode this value by checking if it's greater than zero, and if so,
             * subtracting 1.0f to restore the original value.
             */
            const float PackedScatteringFactor = GetScatteringFactor() + 1.0f;
        
            ParentPrimitiveComp->SetCustomPrimitiveDataFloat(StartIndex, PackedScatteringFactor);
            ParentPrimitiveComp->SetCustomPrimitiveDataFloat(StartIndex + 1, GetReflectionFactor());
            ParentPrimitiveComp->SetCustomPrimitiveDataFloat(StartIndex + 2, GetAbsorptionCoefficient());
        }
    }
    else
    {
        UE_LOG(LogAudioTracing, Warning,
            TEXT("UATSoundMaterialComponent::SetSoundMaterialCustomPrimitiveData: Parent component must be a PrimitiveComponent. Owner Actor: [%s]"), 
            *GetNameSafe(GetOwner())
        );
    }
}

void UATSoundMaterialComponent::ClearSoundMaterialCustomPrimitiveData(UPrimitiveComponent* PrimitiveComp) const
{
    if (UPrimitiveComponent* PrimitiveCompToClear = PrimitiveComp ? PrimitiveComp : Cast<UPrimitiveComponent>(GetAttachParent()))
    {
        const int32 StartFloat4Index = AudioTracing::GetCustomPrimitiveDataStartFloat4Index();
            
        if (0 <= StartFloat4Index && StartFloat4Index < FCustomPrimitiveData::NumCustomPrimitiveDataFloat4s)
        {
            const int32 StartIndex = StartFloat4Index * 4;

            PrimitiveCompToClear->SetCustomPrimitiveDataFloat(StartIndex, 0.0f);
            PrimitiveCompToClear->SetCustomPrimitiveDataFloat(StartIndex + 1, 0.0f);
            PrimitiveCompToClear->SetCustomPrimitiveDataFloat(StartIndex + 2, 0.0f);
        }
    }
}

#if WITH_EDITOR
void UATSoundMaterialComponent::OnSoundMaterialPropertyChanged()
{
    SetSoundMaterialCustomPrimitiveData();
}

void UATSoundMaterialComponent::UnbindAssetDelegate()
{
    if (BoundSoundMaterial.IsValid() && BoundSoundMaterial->OnSoundMaterialPropertyChanged.IsBoundToObject(this))
    {
        BoundSoundMaterial->OnSoundMaterialPropertyChanged.RemoveAll(this);
    }
    BoundSoundMaterial = nullptr;
}

void UATSoundMaterialComponent::ApplySoundMaterialDataDelayed()
{
    /**
     * Re-apply the value on the next tick to handle cases where the Actor's Construction Script regenerates
     * the parent component, potentially resetting Custom Primitive Data.
     */
    if (UWorld* World = GetWorld())
    {
        TWeakObjectPtr<UATSoundMaterialComponent> WeakThis(this);
            
        World->GetTimerManager().SetTimerForNextTick(
            [WeakThis]()
            {
                if (WeakThis.IsValid())
                {
                    if (WeakThis->GetAttachParent())
                    {
                        WeakThis->SetSoundMaterialCustomPrimitiveData();
                    }
                    WeakThis->CachedParent = Cast<UPrimitiveComponent>(WeakThis->GetAttachParent());
                }
            }
        );
    }
}
#endif
