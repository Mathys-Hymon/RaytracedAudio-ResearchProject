// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Components/ATSoundMaterialComponent.h"

#ifdef AUDIOTRACING_ATSoundMaterialComponent_generated_h
#error "ATSoundMaterialComponent.generated.h already included, missing '#pragma once' in ATSoundMaterialComponent.h"
#endif
#define AUDIOTRACING_ATSoundMaterialComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class USoundMaterial;

// ********** Begin Class UATSoundMaterialComponent ************************************************
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetSoundMaterial); \
	DECLARE_FUNCTION(execGetSoundMaterial); \
	DECLARE_FUNCTION(execSetAbsorptionCoefficient); \
	DECLARE_FUNCTION(execSetReflectionFactor); \
	DECLARE_FUNCTION(execSetScatteringFactor); \
	DECLARE_FUNCTION(execSetComponentOverrideSoundMaterial); \
	DECLARE_FUNCTION(execGetAbsorptionCoefficient); \
	DECLARE_FUNCTION(execGetReflectionFactor); \
	DECLARE_FUNCTION(execGetScatteringFactor); \
	DECLARE_FUNCTION(execIsComponentOverrideSoundMaterial);


#if WITH_EDITOR
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS_EOD \
	DECLARE_FUNCTION(execOnSoundMaterialPropertyChanged);
#else // WITH_EDITOR
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS_EOD
#endif // WITH_EDITOR


AUDIOTRACING_API UClass* Z_Construct_UClass_UATSoundMaterialComponent_NoRegister();

#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUATSoundMaterialComponent(); \
	friend struct Z_Construct_UClass_UATSoundMaterialComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend AUDIOTRACING_API UClass* Z_Construct_UClass_UATSoundMaterialComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UATSoundMaterialComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AudioTracing"), Z_Construct_UClass_UATSoundMaterialComponent_NoRegister) \
	DECLARE_SERIALIZER(UATSoundMaterialComponent)


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UATSoundMaterialComponent(UATSoundMaterialComponent&&) = delete; \
	UATSoundMaterialComponent(const UATSoundMaterialComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UATSoundMaterialComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UATSoundMaterialComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UATSoundMaterialComponent) \
	NO_API virtual ~UATSoundMaterialComponent();


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_12_PROLOG
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS_EOD \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_INCLASS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UATSoundMaterialComponent;

// ********** End Class UATSoundMaterialComponent **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
