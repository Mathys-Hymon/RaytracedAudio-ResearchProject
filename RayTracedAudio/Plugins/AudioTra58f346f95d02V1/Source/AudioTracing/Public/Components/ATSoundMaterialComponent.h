// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ATSoundMaterialComponent.generated.h"


class USoundMaterial;

UCLASS( ClassGroup=(AudioTracing), meta=(BlueprintSpawnableComponent, DisplayName = "Audio Tracing Sound Material") )
class AUDIOTRACING_API UATSoundMaterialComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UATSoundMaterialComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void OnAttachmentChanged() override;

    virtual void DestroyComponent(bool bPromoteChildren = false) override;

    virtual void PostLoad() override;

    virtual void OnRegister() override;

    virtual void OnUnregister() override;
    
#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

    virtual void PreEditUndo() override;
    
    virtual void PostEditUndo() override;
#endif

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material Component")
    bool IsComponentOverrideSoundMaterial() const { return bOverrideSoundMaterial; }
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material Component")
    float GetScatteringFactor() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material Component")
    float GetReflectionFactor() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material Component")
    float GetAbsorptionCoefficient() const;

    UFUNCTION(BlueprintCallable, Category = "Audio Tracing|Sound Material Component")
    void SetComponentOverrideSoundMaterial(bool bOverride);

    UFUNCTION(BlueprintCallable, Category = "Audio Tracing|Sound Material Component")
    void SetScatteringFactor(float NewScatteringFactor);
    
    UFUNCTION(BlueprintCallable, Category = "Audio Tracing|Sound Material Component")
    void SetReflectionFactor(float NewReflectionFactor);

    UFUNCTION(BlueprintCallable, Category = "Audio Tracing|Sound Material Component")
    void SetAbsorptionCoefficient(float NewAbsorptionCoefficient);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material Component")
    USoundMaterial* GetSoundMaterial() const { return SoundMaterial; }

    UFUNCTION(BlueprintCallable, Category = "Audio Tracing|Sound Material Component")
    void SetSoundMaterial(USoundMaterial* NewMaterial);

    void SetSoundMaterialCustomPrimitiveData() const;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing")
    TObjectPtr<USoundMaterial> SoundMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing|Override")
    bool bOverrideSoundMaterial;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing|Override", meta = (
        EditCondition = "bOverrideSoundMaterial", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
    float ScatteringFactor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing|Override", meta = (
        EditCondition = "bOverrideSoundMaterial", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
    float ReflectionFactor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing|Override", DisplayName = "Absorption Coefficient (per cm)", meta = (
        EditCondition = "bOverrideSoundMaterial", ClampMin = "0.0", UIMin = "0.0"))
    float AbsorptionCoefficient;

    void ClearSoundMaterialCustomPrimitiveData(UPrimitiveComponent* PrimitiveComp = nullptr) const;

private:
    TWeakObjectPtr<UPrimitiveComponent> CachedParent;

#if WITH_EDITOR
    TWeakObjectPtr<USoundMaterial> BoundSoundMaterial;

    UFUNCTION()
    void OnSoundMaterialPropertyChanged();

    void UnbindAssetDelegate();
    
    /**
     * Re-applies sound material data to the parent component.
     * Intended to be called on the next tick to handle initialization race conditions (e.g., Construction Script).
     */
    void ApplySoundMaterialDataDelayed();
#endif
};
