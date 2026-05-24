// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Settings/AudioTracingSettings.h"

#ifdef AUDIOTRACING_AudioTracingSettings_generated_h
#error "AudioTracingSettings.generated.h already included, missing '#pragma once' in AudioTracingSettings.h"
#endif
#define AUDIOTRACING_AudioTracingSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UAudioTracingSettings ****************************************************
AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingSettings_NoRegister();

#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAudioTracingSettings(); \
	friend struct Z_Construct_UClass_UAudioTracingSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UAudioTracingSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/AudioTracing"), Z_Construct_UClass_UAudioTracingSettings_NoRegister) \
	DECLARE_SERIALIZER(UAudioTracingSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("AudioTracing");} \



#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAudioTracingSettings(UAudioTracingSettings&&) = delete; \
	UAudioTracingSettings(const UAudioTracingSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAudioTracingSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAudioTracingSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAudioTracingSettings) \
	NO_API virtual ~UAudioTracingSettings();


#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h_10_PROLOG
#define FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h_13_INCLASS_NO_PURE_DECLS \
	FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAudioTracingSettings;

// ********** End Class UAudioTracingSettings ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
