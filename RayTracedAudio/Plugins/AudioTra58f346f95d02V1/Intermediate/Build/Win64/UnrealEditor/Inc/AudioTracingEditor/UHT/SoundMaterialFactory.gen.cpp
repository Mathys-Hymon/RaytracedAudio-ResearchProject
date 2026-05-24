// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Factories/SoundMaterialFactory.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSoundMaterialFactory() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACINGEDITOR_API UClass* Z_Construct_UClass_USoundMaterialFactory();
AUDIOTRACINGEDITOR_API UClass* Z_Construct_UClass_USoundMaterialFactory_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UFactory();
UPackage* Z_Construct_UPackage__Script_AudioTracingEditor();
// ********** End Cross Module References **********************************************************

// ********** Begin Class USoundMaterialFactory ****************************************************
void USoundMaterialFactory::StaticRegisterNativesUSoundMaterialFactory()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_USoundMaterialFactory;
UClass* USoundMaterialFactory::GetPrivateStaticClass()
{
	using TClass = USoundMaterialFactory;
	if (!Z_Registration_Info_UClass_USoundMaterialFactory.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SoundMaterialFactory"),
			Z_Registration_Info_UClass_USoundMaterialFactory.InnerSingleton,
			StaticRegisterNativesUSoundMaterialFactory,
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
	return Z_Registration_Info_UClass_USoundMaterialFactory.InnerSingleton;
}
UClass* Z_Construct_UClass_USoundMaterialFactory_NoRegister()
{
	return USoundMaterialFactory::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USoundMaterialFactory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Factories/SoundMaterialFactory.h" },
		{ "ModuleRelativePath", "Private/Factories/SoundMaterialFactory.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USoundMaterialFactory>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USoundMaterialFactory_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFactory,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USoundMaterialFactory_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USoundMaterialFactory_Statics::ClassParams = {
	&USoundMaterialFactory::StaticClass,
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
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USoundMaterialFactory_Statics::Class_MetaDataParams), Z_Construct_UClass_USoundMaterialFactory_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USoundMaterialFactory()
{
	if (!Z_Registration_Info_UClass_USoundMaterialFactory.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USoundMaterialFactory.OuterSingleton, Z_Construct_UClass_USoundMaterialFactory_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USoundMaterialFactory.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USoundMaterialFactory);
USoundMaterialFactory::~USoundMaterialFactory() {}
// ********** End Class USoundMaterialFactory ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_Factories_SoundMaterialFactory_h__Script_AudioTracingEditor_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USoundMaterialFactory, USoundMaterialFactory::StaticClass, TEXT("USoundMaterialFactory"), &Z_Registration_Info_UClass_USoundMaterialFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USoundMaterialFactory), 1843139388U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_Factories_SoundMaterialFactory_h__Script_AudioTracingEditor_112661385(TEXT("/Script/AudioTracingEditor"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_Factories_SoundMaterialFactory_h__Script_AudioTracingEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_Factories_SoundMaterialFactory_h__Script_AudioTracingEditor_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
