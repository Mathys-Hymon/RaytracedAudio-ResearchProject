// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AudioTracingWorldSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAudioTracingWorldSubsystem() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingWorldSubsystem();
AUDIOTRACING_API UClass* Z_Construct_UClass_UAudioTracingWorldSubsystem_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTickableWorldSubsystem();
UPackage* Z_Construct_UPackage__Script_AudioTracing();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAudioTracingWorldSubsystem Function SetDebugVirtualAudioEnabled *********
struct Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics
{
	struct AudioTracingWorldSubsystem_eventSetDebugVirtualAudioEnabled_Parms
	{
		bool bIsEnabled;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AudioTracing" },
		{ "ModuleRelativePath", "Public/AudioTracingWorldSubsystem.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bIsEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::NewProp_bIsEnabled_SetBit(void* Obj)
{
	((AudioTracingWorldSubsystem_eventSetDebugVirtualAudioEnabled_Parms*)Obj)->bIsEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::NewProp_bIsEnabled = { "bIsEnabled", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AudioTracingWorldSubsystem_eventSetDebugVirtualAudioEnabled_Parms), &Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::NewProp_bIsEnabled_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::NewProp_bIsEnabled,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAudioTracingWorldSubsystem, nullptr, "SetDebugVirtualAudioEnabled", Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::AudioTracingWorldSubsystem_eventSetDebugVirtualAudioEnabled_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::AudioTracingWorldSubsystem_eventSetDebugVirtualAudioEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAudioTracingWorldSubsystem::execSetDebugVirtualAudioEnabled)
{
	P_GET_UBOOL(Z_Param_bIsEnabled);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDebugVirtualAudioEnabled(Z_Param_bIsEnabled);
	P_NATIVE_END;
}
// ********** End Class UAudioTracingWorldSubsystem Function SetDebugVirtualAudioEnabled ***********

// ********** Begin Class UAudioTracingWorldSubsystem **********************************************
void UAudioTracingWorldSubsystem::StaticRegisterNativesUAudioTracingWorldSubsystem()
{
	UClass* Class = UAudioTracingWorldSubsystem::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "SetDebugVirtualAudioEnabled", &UAudioTracingWorldSubsystem::execSetDebugVirtualAudioEnabled },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAudioTracingWorldSubsystem;
UClass* UAudioTracingWorldSubsystem::GetPrivateStaticClass()
{
	using TClass = UAudioTracingWorldSubsystem;
	if (!Z_Registration_Info_UClass_UAudioTracingWorldSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AudioTracingWorldSubsystem"),
			Z_Registration_Info_UClass_UAudioTracingWorldSubsystem.InnerSingleton,
			StaticRegisterNativesUAudioTracingWorldSubsystem,
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
	return Z_Registration_Info_UClass_UAudioTracingWorldSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UAudioTracingWorldSubsystem_NoRegister()
{
	return UAudioTracingWorldSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "AudioTracingWorldSubsystem.h" },
		{ "ModuleRelativePath", "Public/AudioTracingWorldSubsystem.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAudioTracingWorldSubsystem_SetDebugVirtualAudioEnabled, "SetDebugVirtualAudioEnabled" }, // 2159207363
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAudioTracingWorldSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UTickableWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracing,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics::ClassParams = {
	&UAudioTracingWorldSubsystem::StaticClass,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAudioTracingWorldSubsystem()
{
	if (!Z_Registration_Info_UClass_UAudioTracingWorldSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAudioTracingWorldSubsystem.OuterSingleton, Z_Construct_UClass_UAudioTracingWorldSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAudioTracingWorldSubsystem.OuterSingleton;
}
UAudioTracingWorldSubsystem::UAudioTracingWorldSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAudioTracingWorldSubsystem);
UAudioTracingWorldSubsystem::~UAudioTracingWorldSubsystem() {}
// ********** End Class UAudioTracingWorldSubsystem ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h__Script_AudioTracing_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAudioTracingWorldSubsystem, UAudioTracingWorldSubsystem::StaticClass, TEXT("UAudioTracingWorldSubsystem"), &Z_Registration_Info_UClass_UAudioTracingWorldSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAudioTracingWorldSubsystem), 2219492353U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h__Script_AudioTracing_3873466629(TEXT("/Script/AudioTracing"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h__Script_AudioTracing_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_AudioTracingWorldSubsystem_h__Script_AudioTracing_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
