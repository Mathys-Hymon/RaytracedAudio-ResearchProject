// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ActorUtility/AudioTracingActorActionUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAudioTracingActorActionUtility() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACINGEDITOR_API UClass* Z_Construct_UClass_UAudioTracingActorActionUtility();
AUDIOTRACINGEDITOR_API UClass* Z_Construct_UClass_UAudioTracingActorActionUtility_NoRegister();
BLUTILITY_API UClass* Z_Construct_UClass_UActorActionUtility();
UPackage* Z_Construct_UPackage__Script_AudioTracingEditor();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAudioTracingActorActionUtility Function AddSoundMaterialToSelectedActors 
struct Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* CallInEditor */" },
#endif
		{ "ModuleRelativePath", "Private/ActorUtility/AudioTracingActorActionUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "CallInEditor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAudioTracingActorActionUtility, nullptr, "AddSoundMaterialToSelectedActors", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAudioTracingActorActionUtility::execAddSoundMaterialToSelectedActors)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AddSoundMaterialToSelectedActors();
	P_NATIVE_END;
}
// ********** End Class UAudioTracingActorActionUtility Function AddSoundMaterialToSelectedActors **

// ********** Begin Class UAudioTracingActorActionUtility Function RemoveSoundMaterialFromSelectedActors 
struct Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* CallInEditor */" },
#endif
		{ "ModuleRelativePath", "Private/ActorUtility/AudioTracingActorActionUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "CallInEditor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAudioTracingActorActionUtility, nullptr, "RemoveSoundMaterialFromSelectedActors", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAudioTracingActorActionUtility::execRemoveSoundMaterialFromSelectedActors)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveSoundMaterialFromSelectedActors();
	P_NATIVE_END;
}
// ********** End Class UAudioTracingActorActionUtility Function RemoveSoundMaterialFromSelectedActors 

// ********** Begin Class UAudioTracingActorActionUtility ******************************************
void UAudioTracingActorActionUtility::StaticRegisterNativesUAudioTracingActorActionUtility()
{
	UClass* Class = UAudioTracingActorActionUtility::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AddSoundMaterialToSelectedActors", &UAudioTracingActorActionUtility::execAddSoundMaterialToSelectedActors },
		{ "RemoveSoundMaterialFromSelectedActors", &UAudioTracingActorActionUtility::execRemoveSoundMaterialFromSelectedActors },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAudioTracingActorActionUtility;
UClass* UAudioTracingActorActionUtility::GetPrivateStaticClass()
{
	using TClass = UAudioTracingActorActionUtility;
	if (!Z_Registration_Info_UClass_UAudioTracingActorActionUtility.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AudioTracingActorActionUtility"),
			Z_Registration_Info_UClass_UAudioTracingActorActionUtility.InnerSingleton,
			StaticRegisterNativesUAudioTracingActorActionUtility,
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
	return Z_Registration_Info_UClass_UAudioTracingActorActionUtility.InnerSingleton;
}
UClass* Z_Construct_UClass_UAudioTracingActorActionUtility_NoRegister()
{
	return UAudioTracingActorActionUtility::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAudioTracingActorActionUtility_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "ActorUtility/AudioTracingActorActionUtility.h" },
		{ "ModuleRelativePath", "Private/ActorUtility/AudioTracingActorActionUtility.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAudioTracingActorActionUtility_AddSoundMaterialToSelectedActors, "AddSoundMaterialToSelectedActors" }, // 3312178937
		{ &Z_Construct_UFunction_UAudioTracingActorActionUtility_RemoveSoundMaterialFromSelectedActors, "RemoveSoundMaterialFromSelectedActors" }, // 4071362971
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAudioTracingActorActionUtility>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAudioTracingActorActionUtility_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorActionUtility,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracingEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingActorActionUtility_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAudioTracingActorActionUtility_Statics::ClassParams = {
	&UAudioTracingActorActionUtility::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingActorActionUtility_Statics::Class_MetaDataParams), Z_Construct_UClass_UAudioTracingActorActionUtility_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAudioTracingActorActionUtility()
{
	if (!Z_Registration_Info_UClass_UAudioTracingActorActionUtility.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAudioTracingActorActionUtility.OuterSingleton, Z_Construct_UClass_UAudioTracingActorActionUtility_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAudioTracingActorActionUtility.OuterSingleton;
}
UAudioTracingActorActionUtility::UAudioTracingActorActionUtility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAudioTracingActorActionUtility);
UAudioTracingActorActionUtility::~UAudioTracingActorActionUtility() {}
// ********** End Class UAudioTracingActorActionUtility ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h__Script_AudioTracingEditor_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAudioTracingActorActionUtility, UAudioTracingActorActionUtility::StaticClass, TEXT("UAudioTracingActorActionUtility"), &Z_Registration_Info_UClass_UAudioTracingActorActionUtility, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAudioTracingActorActionUtility), 1640498754U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h__Script_AudioTracingEditor_2038481852(TEXT("/Script/AudioTracingEditor"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h__Script_AudioTracingEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracingEditor_Private_ActorUtility_AudioTracingActorActionUtility_h__Script_AudioTracingEditor_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
