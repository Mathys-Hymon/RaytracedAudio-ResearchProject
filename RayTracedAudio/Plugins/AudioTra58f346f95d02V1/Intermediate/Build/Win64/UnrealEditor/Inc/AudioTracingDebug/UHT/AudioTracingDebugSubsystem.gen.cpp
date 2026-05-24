// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AudioTracingDebugSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAudioTracingDebugSubsystem() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACINGDEBUG_API UClass* Z_Construct_UClass_UAudioTracingDebugSubsystem();
AUDIOTRACINGDEBUG_API UClass* Z_Construct_UClass_UAudioTracingDebugSubsystem_NoRegister();
EDITORSUBSYSTEM_API UClass* Z_Construct_UClass_UEditorSubsystem();
UPackage* Z_Construct_UPackage__Script_AudioTracingDebug();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAudioTracingDebugSubsystem **********************************************
void UAudioTracingDebugSubsystem::StaticRegisterNativesUAudioTracingDebugSubsystem()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAudioTracingDebugSubsystem;
UClass* UAudioTracingDebugSubsystem::GetPrivateStaticClass()
{
	using TClass = UAudioTracingDebugSubsystem;
	if (!Z_Registration_Info_UClass_UAudioTracingDebugSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AudioTracingDebugSubsystem"),
			Z_Registration_Info_UClass_UAudioTracingDebugSubsystem.InnerSingleton,
			StaticRegisterNativesUAudioTracingDebugSubsystem,
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
	return Z_Registration_Info_UClass_UAudioTracingDebugSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UAudioTracingDebugSubsystem_NoRegister()
{
	return UAudioTracingDebugSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "AudioTracingDebugSubsystem.h" },
		{ "ModuleRelativePath", "Public/AudioTracingDebugSubsystem.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAudioTracingDebugSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEditorSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracingDebug,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics::ClassParams = {
	&UAudioTracingDebugSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAudioTracingDebugSubsystem()
{
	if (!Z_Registration_Info_UClass_UAudioTracingDebugSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAudioTracingDebugSubsystem.OuterSingleton, Z_Construct_UClass_UAudioTracingDebugSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAudioTracingDebugSubsystem.OuterSingleton;
}
UAudioTracingDebugSubsystem::UAudioTracingDebugSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAudioTracingDebugSubsystem);
UAudioTracingDebugSubsystem::~UAudioTracingDebugSubsystem() {}
// ********** End Class UAudioTracingDebugSubsystem ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingDebug_Public_AudioTracingDebugSubsystem_h__Script_AudioTracingDebug_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAudioTracingDebugSubsystem, UAudioTracingDebugSubsystem::StaticClass, TEXT("UAudioTracingDebugSubsystem"), &Z_Registration_Info_UClass_UAudioTracingDebugSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAudioTracingDebugSubsystem), 1770898839U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingDebug_Public_AudioTracingDebugSubsystem_h__Script_AudioTracingDebug_3319164785(TEXT("/Script/AudioTracingDebug"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingDebug_Public_AudioTracingDebugSubsystem_h__Script_AudioTracingDebug_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingDebug_Public_AudioTracingDebugSubsystem_h__Script_AudioTracingDebug_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
