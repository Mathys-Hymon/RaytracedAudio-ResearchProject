// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Settings/AudioTracingSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAudioTracingSettings() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingSettings();
AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingSettings_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSoftObjectPath();
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
UPackage* Z_Construct_UPackage__Script_AudioTracing();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAudioTracingSettings ****************************************************
void UAudioTracingSettings::StaticRegisterNativesUAudioTracingSettings()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAudioTracingSettings;
UClass* UAudioTracingSettings::GetPrivateStaticClass()
{
	using TClass = UAudioTracingSettings;
	if (!Z_Registration_Info_UClass_UAudioTracingSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AudioTracingSettings"),
			Z_Registration_Info_UClass_UAudioTracingSettings.InnerSingleton,
			StaticRegisterNativesUAudioTracingSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UAudioTracingSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UAudioTracingSettings_NoRegister()
{
	return UAudioTracingSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAudioTracingSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Settings for the Audio Tracing\n" },
#endif
		{ "DisplayName", "Audio Tracing" },
		{ "IncludePath", "Settings/AudioTracingSettings.h" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Settings for the Audio Tracing" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableHardwareRaytracing_MetaData[] = {
		{ "Category", "Audio Tracing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * Enables or disables the entire hardware-accelerated audio tracing feature.\n     * Requires a project restart to take full effect.\n     */" },
#endif
		{ "ConfigRestartRequired", "TRUE" },
		{ "ConsoleVariable", "AudioTracing.HardwareRayTracing" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enables or disables the entire hardware-accelerated audio tracing feature.\nRequires a project restart to take full effect." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinUpdateInterval_MetaData[] = {
		{ "Category", "Performance" },
		{ "ClampMax", "0.25" },
		{ "ClampMin", "0.016" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The minimum time interval in seconds between audio tracing calculations.\n     * Increasing this value reduces CPU usage but lowers the responsiveness of environmental audio changes.\n     * Recommended values are between 0.0333 (33ms) and 0.15 (150ms).\n     */" },
#endif
		{ "ConsoleVariable", "AudioTracing.MinUpdateInterval" },
		{ "DisplayName", "Minimum Update Interval (s)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The minimum time interval in seconds between audio tracing calculations.\nIncreasing this value reduces CPU usage but lowers the responsiveness of environmental audio changes.\nRecommended values are between 0.0333 (33ms) and 0.15 (150ms)." },
#endif
		{ "UIMax", "0.25" },
		{ "UIMin", "0.016" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxReflection_MetaData[] = {
		{ "Category", "Hardware Raytracing" },
		{ "ClampMax", "32" },
		{ "ClampMin", "8" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The maximum number of times a ray can reflect off surfaces.\n     * Higher values produce more realistic reverberation but increase computational cost.\n     */" },
#endif
		{ "ConsoleVariable", "AudioTracing.HardwareRayTracing.MaxReflectionDepth" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The maximum number of times a ray can reflect off surfaces.\nHigher values produce more realistic reverberation but increase computational cost." },
#endif
		{ "UIMax", "32" },
		{ "UIMin", "8" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RayCount_MetaData[] = {
		{ "Category", "Hardware Raytracing" },
		{ "ClampMax", "2048" },
		{ "ClampMin", "512" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The number of rays to cast from the listener for calculating reflections and occlusion.\n     * More rays result in a more accurate and stable simulation, at a higher performance cost.\n     * This setting cannot be changed during gameplay.\n     */" },
#endif
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The number of rays to cast from the listener for calculating reflections and occlusion.\nMore rays result in a more accurate and stable simulation, at a higher performance cost.\nThis setting cannot be changed during gameplay." },
#endif
		{ "UIMax", "2048" },
		{ "UIMin", "512" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundSpeed_MetaData[] = {
		{ "Category", "General" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The speed of sound in centimeters per second.\n     * Used for time-of-flight calculations to determine delay and distance.\n     * Default: 34,300 cm/s\n     */" },
#endif
		{ "ConsoleVariable", "AudioTracing.SoundSpeed" },
		{ "DisplayName", "Speed of Sound (cm/s)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The speed of sound in centimeters per second.\nUsed for time-of-flight calculations to determine delay and distance.\nDefault: 34,300 cm/s" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeadWidth_MetaData[] = {
		{ "Category", "General" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The simulated width of the listener's head in centimeters.\n     * Used for binaural audio calculations such as Interaural Time Difference (ITD).\n     */" },
#endif
		{ "ConsoleVariable", "AudioTracing.HeadWidth" },
		{ "DisplayName", "Listener Head Width (cm)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The simulated width of the listener's head in centimeters.\nUsed for binaural audio calculations such as Interaural Time Difference (ITD)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTraceTime_MetaData[] = {
		{ "Category", "Hardware Raytracing" },
		{ "ClampMax", "45.0" },
		{ "ClampMin", "15.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The maximum time in seconds a sound ray can travel, determining its maximum distance.\n     * Max Trace Distance = Speed of Sound * Max Trace Time.\n     */" },
#endif
		{ "ConsoleVariable", "AudioTracing.HardwareRayTracing.MaxTraceTime" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The maximum time in seconds a sound ray can travel, determining its maximum distance.\nMax Trace Distance = Speed of Sound * Max Trace Time." },
#endif
		{ "UIMax", "45.0" },
		{ "UIMin", "15.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxActiveSoundSources_MetaData[] = {
		{ "Category", "Hardware Raytracing" },
		{ "ClampMax", "32" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The maximum number of concurrently active sound sources to trace against per frame.\n     * Limiting this helps control performance in scenes with many sounds.\n     * When this limit is exceeded, the plugin will only process the sources closest to the listener.\n     * Any sounds beyond this count will fall back to standard audio playback without tracing effects.\n     */" },
#endif
		{ "ConsoleVariable", "AudioTracing.HardwareRayTracing.MaxActiveSoundSources" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The maximum number of concurrently active sound sources to trace against per frame.\nLimiting this helps control performance in scenes with many sounds.\nWhen this limit is exceeded, the plugin will only process the sources closest to the listener.\nAny sounds beyond this count will fall back to standard audio playback without tracing effects." },
#endif
		{ "UIMax", "32" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomPrimitiveDataStartFloat4Index_MetaData[] = {
		{ "Category", "Hardware Raytracing" },
		{ "ClampMin", "-1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * The starting float4 index in the Custom Primitive Data to read sound material properties from.\n     * This index is counted in float4 units (groups of 4 floats).\n     * \n     * Example:\n     * - Index 0 corresponds to CustomPrimitiveData[0..3]\n     * - Index 1 corresponds to CustomPrimitiveData[4..7]\n     * \n     * Ensure this does not overlap with other systems using Custom Primitive Data.\n     * \n     * Set to a value outside the valid range [0, 8] (e.g., 9 or higher) to disable reading custom data.\n     * Disabling this will cause all objects to use default sound material properties.\n     */" },
#endif
		{ "DisplayName", "Custom Primitive Data Start Index (float4)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The starting float4 index in the Custom Primitive Data to read sound material properties from.\nThis index is counted in float4 units (groups of 4 floats).\n\nExample:\n- Index 0 corresponds to CustomPrimitiveData[0..3]\n- Index 1 corresponds to CustomPrimitiveData[4..7]\n\nEnsure this does not overlap with other systems using Custom Primitive Data.\n\nSet to a value outside the valid range [0, 8] (e.g., 9 or higher) to disable reading custom data.\nDisabling this will cause all objects to use default sound material properties." },
#endif
		{ "UIMax", "9" },
		{ "UIMin", "-1" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShortReverbSubmixPath_MetaData[] = {
		{ "AllowedClasses", "/Script/Engine.SoundSubmix" },
		{ "Category", "Reverb|Submix" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Path of submix has short reverb effector.\n    */" },
#endif
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path of submix has short reverb effector." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MediumReverbSubmixPath_MetaData[] = {
		{ "AllowedClasses", "/Script/Engine.SoundSubmix" },
		{ "Category", "Reverb|Submix" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Path of submix has medium reverb effector.\n    */" },
#endif
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path of submix has medium reverb effector." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LongReverbSubmixPath_MetaData[] = {
		{ "AllowedClasses", "/Script/Engine.SoundSubmix" },
		{ "Category", "Reverb|Submix" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Path of submix has long reverb effector.\n    */" },
#endif
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path of submix has long reverb effector." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectSoundGain_MetaData[] = {
		{ "Category", "General|Advanced" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "-60.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Gain of Direct Sound. \n    */" },
#endif
		{ "DisplayName", "Direct Sound Gain (dB)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gain of Direct Sound." },
#endif
		{ "UIMax", "10.0" },
		{ "UIMin", "-60.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EarlyReflectionGain_MetaData[] = {
		{ "Category", "General|Advanced" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "-60.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Gain of Early Reflection Sound.\n    */" },
#endif
		{ "DisplayName", "Early Reflection Gain (dB)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gain of Early Reflection Sound." },
#endif
		{ "UIMax", "10.0" },
		{ "UIMin", "-60.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReverbGain_MetaData[] = {
		{ "Category", "General|Advanced" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "-60.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Gain of Reverb Sound.\n    */" },
#endif
		{ "DisplayName", "Reverb Gain (dB)" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gain of Reverb Sound." },
#endif
		{ "UIMax", "10.0" },
		{ "UIMin", "-60.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EarlyReflectionMaxCount_MetaData[] = {
		{ "Category", "General|Advanced" },
		{ "ClampMax", "20" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * Maximum number of Early Reflections to be played.\n    */" },
#endif
		{ "DisplayName", "Early Reflection Max Count" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of Early Reflections to be played." },
#endif
		{ "UIMax", "20" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReverbTimeMultiplier_MetaData[] = {
		{ "Category", "General|Advanced" },
		{ "ClampMax", "4" },
		{ "ClampMin", "0.25" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n    * A Multiplier will be applied to reverberation time.\n    * This helps compensate when the number of Max Reflection is reduced for performance reasons.\n    */" },
#endif
		{ "DisplayName", "Reverb Time Multiplier" },
		{ "ModuleRelativePath", "Public/Settings/AudioTracingSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A Multiplier will be applied to reverberation time.\nThis helps compensate when the number of Max Reflection is reduced for performance reasons." },
#endif
		{ "UIMax", "4" },
		{ "UIMin", "0.25" },
	};
#endif // WITH_METADATA
	static void NewProp_bEnableHardwareRaytracing_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableHardwareRaytracing;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinUpdateInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxReflection;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RayCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SoundSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HeadWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxTraceTime;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxActiveSoundSources;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CustomPrimitiveDataStartFloat4Index;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ShortReverbSubmixPath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MediumReverbSubmixPath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LongReverbSubmixPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DirectSoundGain;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EarlyReflectionGain;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReverbGain;
	static const UECodeGen_Private::FIntPropertyParams NewProp_EarlyReflectionMaxCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReverbTimeMultiplier;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAudioTracingSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_bEnableHardwareRaytracing_SetBit(void* Obj)
{
	((UAudioTracingSettings*)Obj)->bEnableHardwareRaytracing = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_bEnableHardwareRaytracing = { "bEnableHardwareRaytracing", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAudioTracingSettings), &Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_bEnableHardwareRaytracing_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableHardwareRaytracing_MetaData), NewProp_bEnableHardwareRaytracing_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MinUpdateInterval = { "MinUpdateInterval", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, MinUpdateInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinUpdateInterval_MetaData), NewProp_MinUpdateInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MaxReflection = { "MaxReflection", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, MaxReflection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxReflection_MetaData), NewProp_MaxReflection_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_RayCount = { "RayCount", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, RayCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RayCount_MetaData), NewProp_RayCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_SoundSpeed = { "SoundSpeed", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, SoundSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundSpeed_MetaData), NewProp_SoundSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_HeadWidth = { "HeadWidth", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, HeadWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeadWidth_MetaData), NewProp_HeadWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MaxTraceTime = { "MaxTraceTime", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, MaxTraceTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTraceTime_MetaData), NewProp_MaxTraceTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MaxActiveSoundSources = { "MaxActiveSoundSources", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, MaxActiveSoundSources), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxActiveSoundSources_MetaData), NewProp_MaxActiveSoundSources_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_CustomPrimitiveDataStartFloat4Index = { "CustomPrimitiveDataStartFloat4Index", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, CustomPrimitiveDataStartFloat4Index), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomPrimitiveDataStartFloat4Index_MetaData), NewProp_CustomPrimitiveDataStartFloat4Index_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_ShortReverbSubmixPath = { "ShortReverbSubmixPath", nullptr, (EPropertyFlags)0x0010000000044005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, ShortReverbSubmixPath), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShortReverbSubmixPath_MetaData), NewProp_ShortReverbSubmixPath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MediumReverbSubmixPath = { "MediumReverbSubmixPath", nullptr, (EPropertyFlags)0x0010000000044005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, MediumReverbSubmixPath), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MediumReverbSubmixPath_MetaData), NewProp_MediumReverbSubmixPath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_LongReverbSubmixPath = { "LongReverbSubmixPath", nullptr, (EPropertyFlags)0x0010000000044005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, LongReverbSubmixPath), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LongReverbSubmixPath_MetaData), NewProp_LongReverbSubmixPath_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_DirectSoundGain = { "DirectSoundGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, DirectSoundGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectSoundGain_MetaData), NewProp_DirectSoundGain_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_EarlyReflectionGain = { "EarlyReflectionGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, EarlyReflectionGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EarlyReflectionGain_MetaData), NewProp_EarlyReflectionGain_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_ReverbGain = { "ReverbGain", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, ReverbGain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReverbGain_MetaData), NewProp_ReverbGain_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_EarlyReflectionMaxCount = { "EarlyReflectionMaxCount", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, EarlyReflectionMaxCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EarlyReflectionMaxCount_MetaData), NewProp_EarlyReflectionMaxCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_ReverbTimeMultiplier = { "ReverbTimeMultiplier", nullptr, (EPropertyFlags)0x0010000000004015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudioTracingSettings, ReverbTimeMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReverbTimeMultiplier_MetaData), NewProp_ReverbTimeMultiplier_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAudioTracingSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_bEnableHardwareRaytracing,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MinUpdateInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MaxReflection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_RayCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_SoundSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_HeadWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MaxTraceTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MaxActiveSoundSources,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_CustomPrimitiveDataStartFloat4Index,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_ShortReverbSubmixPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_MediumReverbSubmixPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_LongReverbSubmixPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_DirectSoundGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_EarlyReflectionGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_ReverbGain,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_EarlyReflectionMaxCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudioTracingSettings_Statics::NewProp_ReverbTimeMultiplier,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAudioTracingSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracing,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAudioTracingSettings_Statics::ClassParams = {
	&UAudioTracingSettings::StaticClass,
	"AudioTracing",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAudioTracingSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingSettings_Statics::PropPointers),
	0,
	0x000000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UAudioTracingSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAudioTracingSettings()
{
	if (!Z_Registration_Info_UClass_UAudioTracingSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAudioTracingSettings.OuterSingleton, Z_Construct_UClass_UAudioTracingSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAudioTracingSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAudioTracingSettings);
UAudioTracingSettings::~UAudioTracingSettings() {}
// ********** End Class UAudioTracingSettings ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h__Script_AudioTracing_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAudioTracingSettings, UAudioTracingSettings::StaticClass, TEXT("UAudioTracingSettings"), &Z_Registration_Info_UClass_UAudioTracingSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAudioTracingSettings), 3174021367U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h__Script_AudioTracing_1896537020(TEXT("/Script/AudioTracing"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h__Script_AudioTracing_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Settings_AudioTracingSettings_h__Script_AudioTracing_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
