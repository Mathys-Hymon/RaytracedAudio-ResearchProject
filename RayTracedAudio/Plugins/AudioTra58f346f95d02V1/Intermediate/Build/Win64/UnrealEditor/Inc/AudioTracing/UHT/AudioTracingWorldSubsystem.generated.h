// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AudioTracingWorldSubsystem.h"

#ifdef AUDIOTRACING_AudioTracingWorldSubsystem_generated_h
#error "AudioTracingWorldSubsystem.generated.h already included, missing '#pragma once' in AudioTracingWorldSubsystem.h"
#endif
#define AUDIOTRACING_AudioTracingWorldSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UAudioTracingWorldSubsystem **********************************************
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetDebugVirtualAudioEnabled);


AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingWorldSubsystem_NoRegister();

#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAudioTracingWorldSubsystem(); \
	friend struct Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingWorldSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UAudioTracingWorldSubsystem, UTickableWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AudioTracing"), Z_Construct_UClass_UAudioTracingWorldSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UAudioTracingWorldSubsystem)


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAudioTracingWorldSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAudioTracingWorldSubsystem(UAudioTracingWorldSubsystem&&) = delete; \
	UAudioTracingWorldSubsystem(const UAudioTracingWorldSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAudioTracingWorldSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAudioTracingWorldSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAudioTracingWorldSubsystem) \
	NO_API virtual ~UAudioTracingWorldSubsystem();


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_21_PROLOG
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_INCLASS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAudioTracingWorldSubsystem;

// ********** End Class UAudioTracingWorldSubsystem ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
