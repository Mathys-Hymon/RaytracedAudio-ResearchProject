// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Sound/SoundMaterial.h"

#ifdef AUDIOTRACING_SoundMaterial_generated_h
#error "SoundMaterial.generated.h already included, missing '#pragma once' in SoundMaterial.h"
#endif
#define AUDIOTRACING_SoundMaterial_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class USoundMaterial ***********************************************************
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetAbsorptionCoefficient); \
	DECLARE_FUNCTION(execGetReflectionFactor); \
	DECLARE_FUNCTION(execGetScatteringFactor);


AUDIOTRACING_API UClass* Z_Construct_UClass_USoundMaterial_NoRegister();

#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSoundMaterial(); \
	friend struct Z_Construct_UClass_USoundMaterial_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend AUDIOTRACING_API UClass* Z_Construct_UClass_USoundMaterial_NoRegister(); \
public: \
	DECLARE_CLASS2(USoundMaterial, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AudioTracing"), Z_Construct_UClass_USoundMaterial_NoRegister) \
	DECLARE_SERIALIZER(USoundMaterial)


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	USoundMaterial(USoundMaterial&&) = delete; \
	USoundMaterial(const USoundMaterial&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USoundMaterial); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USoundMaterial); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USoundMaterial) \
	NO_API virtual ~USoundMaterial();


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_16_PROLOG
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_INCLASS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class USoundMaterial;

// ********** End Class USoundMaterial *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
