// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ActorUtility/AudioTracingActorActionUtility.h"

#ifdef AUDIOTRACINGEDITOR_AudioTracingActorActionUtility_generated_h
#error "AudioTracingActorActionUtility.generated.h already included, missing '#pragma once' in AudioTracingActorActionUtility.h"
#endif
#define AUDIOTRACINGEDITOR_AudioTracingActorActionUtility_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UAudioTracingActorActionUtility ******************************************
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRemoveSoundMaterialFromSelectedActors); \
	DECLARE_FUNCTION(execAddSoundMaterialToSelectedActors);


AUDIOTRACINGEDITOR_API UClass* Z_Construct_UClass_UAudioTracingActorActionUtility_NoRegister();

#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAudioTracingActorActionUtility(); \
	friend struct Z_Construct_UClass_UAudioTracingActorActionUtility_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend AUDIOTRACINGEDITOR_API UClass* Z_Construct_UClass_UAudioTracingActorActionUtility_NoRegister(); \
public: \
	DECLARE_CLASS2(UAudioTracingActorActionUtility, UActorActionUtility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AudioTracingEditor"), Z_Construct_UClass_UAudioTracingActorActionUtility_NoRegister) \
	DECLARE_SERIALIZER(UAudioTracingActorActionUtility)


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAudioTracingActorActionUtility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAudioTracingActorActionUtility(UAudioTracingActorActionUtility&&) = delete; \
	UAudioTracingActorActionUtility(const UAudioTracingActorActionUtility&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAudioTracingActorActionUtility); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAudioTracingActorActionUtility); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAudioTracingActorActionUtility) \
	NO_API virtual ~UAudioTracingActorActionUtility();


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_12_PROLOG
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_INCLASS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAudioTracingActorActionUtility;

// ********** End Class UAudioTracingActorActionUtility ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
