// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundMaterial.generated.h"

#if WITH_EDITOR
DECLARE_MULTICAST_DELEGATE(FOnSoundMaterialPropertyChanged);
#endif

/**
 * 
 */
UCLASS(BlueprintType)
class AUDIOTRACING_API USoundMaterial : public UObject
{
	GENERATED_BODY()
	
public:
	USoundMaterial();

	static constexpr float DefaultScatteringFactor = 0.1f;
	static constexpr float DefaultReflectionFactor = 0.97f;
	static constexpr float DefaultAbsorptionCoefficient = 0.2f;

	static constexpr uint32 NumProperties = 3;

#if WITH_EDITOR
	FOnSoundMaterialPropertyChanged OnSoundMaterialPropertyChanged;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material")
	FORCEINLINE float GetScatteringFactor() const { return ScatteringFactor; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material")
	FORCEINLINE float GetReflectionFactor() const { return ReflectionFactor; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Audio Tracing|Sound Material")
	FORCEINLINE float GetAbsorptionCoefficient() const { return AbsorptionCoefficient; }

protected:
	/**
	 * Defines how much of the reflected sound energy is scattered diffusely vs. reflected specularly.
	 * A value of 0.0 means perfect mirror-like reflections (specular).
	 * A value of 1.0 means all reflected sound scatters in random directions (fully diffuse).
	 * Range: [0.0, 1.0]
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float ScatteringFactor;

	/**
	 * The fraction of sound energy that is reflected when it hits a surface.
	 * This value determines how much sound "bounces off" the material.
	 * A value of 1.0 means all energy is reflected.
	 * A value of 0.0 means all energy is absorbed.
	 * Range: [0.0, 1.0]
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float ReflectionFactor;

	/**
	 * Defines how much sound energy is lost per centimeter as it travels through the material.
	 * This is used to calculate sound transmission (occlusion) and is unit-dependent.
	 * Higher values mean the material blocks more sound. A value of 0.0 means the material
	 * is acoustically transparent.
	 *
	 * Unit: per centimeter (1/cm)
	 * Range: [0.0, infinity)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing", DisplayName = "Absorption Coefficient (per cm)", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AbsorptionCoefficient;
};
