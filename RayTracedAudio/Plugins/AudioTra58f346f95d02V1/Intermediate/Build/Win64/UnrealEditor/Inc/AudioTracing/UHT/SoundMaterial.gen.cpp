// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Sound/SoundMaterial.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSoundMaterial() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACING_API UClass* Z_Construct_UClass_USoundMaterial();
AUDIOTRACING_API UClass* Z_Construct_UClass_USoundMaterial_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_AudioTracing();
// ********** End Cross Module References **********************************************************

// ********** Begin Class USoundMaterial Function GetAbsorptionCoefficient *************************
struct Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics
{
	struct SoundMaterial_eventGetAbsorptionCoefficient_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material" },
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoundMaterial_eventGetAbsorptionCoefficient_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USoundMaterial, nullptr, "GetAbsorptionCoefficient", Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::PropPointers), sizeof(Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::SoundMaterial_eventGetAbsorptionCoefficient_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::Function_MetaDataParams), Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::SoundMaterial_eventGetAbsorptionCoefficient_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USoundMaterial::execGetAbsorptionCoefficient)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetAbsorptionCoefficient();
	P_NATIVE_END;
}
// ********** End Class USoundMaterial Function GetAbsorptionCoefficient ***************************

// ********** Begin Class USoundMaterial Function GetReflectionFactor ******************************
struct Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics
{
	struct SoundMaterial_eventGetReflectionFactor_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material" },
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoundMaterial_eventGetReflectionFactor_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USoundMaterial, nullptr, "GetReflectionFactor", Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::PropPointers), sizeof(Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::SoundMaterial_eventGetReflectionFactor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::Function_MetaDataParams), Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::SoundMaterial_eventGetReflectionFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USoundMaterial_GetReflectionFactor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USoundMaterial_GetReflectionFactor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USoundMaterial::execGetReflectionFactor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetReflectionFactor();
	P_NATIVE_END;
}
// ********** End Class USoundMaterial Function GetReflectionFactor ********************************

// ********** Begin Class USoundMaterial Function GetScatteringFactor ******************************
struct Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics
{
	struct SoundMaterial_eventGetScatteringFactor_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material" },
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoundMaterial_eventGetScatteringFactor_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USoundMaterial, nullptr, "GetScatteringFactor", Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::PropPointers), sizeof(Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::SoundMaterial_eventGetScatteringFactor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::Function_MetaDataParams), Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::SoundMaterial_eventGetScatteringFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USoundMaterial_GetScatteringFactor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USoundMaterial_GetScatteringFactor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USoundMaterial::execGetScatteringFactor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetScatteringFactor();
	P_NATIVE_END;
}
// ********** End Class USoundMaterial Function GetScatteringFactor ********************************

// ********** Begin Class USoundMaterial ***********************************************************
void USoundMaterial::StaticRegisterNativesUSoundMaterial()
{
	UClass* Class = USoundMaterial::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetAbsorptionCoefficient", &USoundMaterial::execGetAbsorptionCoefficient },
		{ "GetReflectionFactor", &USoundMaterial::execGetReflectionFactor },
		{ "GetScatteringFactor", &USoundMaterial::execGetScatteringFactor },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USoundMaterial;
UClass* USoundMaterial::GetPrivateStaticClass()
{
	using TClass = USoundMaterial;
	if (!Z_Registration_Info_UClass_USoundMaterial.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SoundMaterial"),
			Z_Registration_Info_UClass_USoundMaterial.InnerSingleton,
			StaticRegisterNativesUSoundMaterial,
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
	return Z_Registration_Info_UClass_USoundMaterial.InnerSingleton;
}
UClass* Z_Construct_UClass_USoundMaterial_NoRegister()
{
	return USoundMaterial::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USoundMaterial_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Sound/SoundMaterial.h" },
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatteringFactor_MetaData[] = {
		{ "Category", "Audio Tracing" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Defines how much of the reflected sound energy is scattered diffusely vs. reflected specularly.\n\x09 * A value of 0.0 means perfect mirror-like reflections (specular).\n\x09 * A value of 1.0 means all reflected sound scatters in random directions (fully diffuse).\n\x09 * Range: [0.0, 1.0]\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Defines how much of the reflected sound energy is scattered diffusely vs. reflected specularly.\nA value of 0.0 means perfect mirror-like reflections (specular).\nA value of 1.0 means all reflected sound scatters in random directions (fully diffuse).\nRange: [0.0, 1.0]" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReflectionFactor_MetaData[] = {
		{ "Category", "Audio Tracing" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * The fraction of sound energy that is reflected when it hits a surface.\n\x09 * This value determines how much sound \"bounces off\" the material.\n\x09 * A value of 1.0 means all energy is reflected.\n\x09 * A value of 0.0 means all energy is absorbed.\n\x09 * Range: [0.0, 1.0]\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The fraction of sound energy that is reflected when it hits a surface.\nThis value determines how much sound \"bounces off\" the material.\nA value of 1.0 means all energy is reflected.\nA value of 0.0 means all energy is absorbed.\nRange: [0.0, 1.0]" },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbsorptionCoefficient_MetaData[] = {
		{ "Category", "Audio Tracing" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Defines how much sound energy is lost per centimeter as it travels through the material.\n\x09 * This is used to calculate sound transmission (occlusion) and is unit-dependent.\n\x09 * Higher values mean the material blocks more sound. A value of 0.0 means the material\n\x09 * is acoustically transparent.\n\x09 *\n\x09 * Unit: per centimeter (1/cm)\n\x09 * Range: [0.0, infinity)\n\x09 */" },
#endif
		{ "DisplayName", "Absorption Coefficient (per cm)" },
		{ "ModuleRelativePath", "Public/Sound/SoundMaterial.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Defines how much sound energy is lost per centimeter as it travels through the material.\nThis is used to calculate sound transmission (occlusion) and is unit-dependent.\nHigher values mean the material blocks more sound. A value of 0.0 means the material\nis acoustically transparent.\n\nUnit: per centimeter (1/cm)\nRange: [0.0, infinity)" },
#endif
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScatteringFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReflectionFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AbsorptionCoefficient;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USoundMaterial_GetAbsorptionCoefficient, "GetAbsorptionCoefficient" }, // 2537490093
		{ &Z_Construct_UFunction_USoundMaterial_GetReflectionFactor, "GetReflectionFactor" }, // 3918757580
		{ &Z_Construct_UFunction_USoundMaterial_GetScatteringFactor, "GetScatteringFactor" }, // 962852247
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USoundMaterial>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USoundMaterial_Statics::NewProp_ScatteringFactor = { "ScatteringFactor", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USoundMaterial, ScatteringFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatteringFactor_MetaData), NewProp_ScatteringFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USoundMaterial_Statics::NewProp_ReflectionFactor = { "ReflectionFactor", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USoundMaterial, ReflectionFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReflectionFactor_MetaData), NewProp_ReflectionFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USoundMaterial_Statics::NewProp_AbsorptionCoefficient = { "AbsorptionCoefficient", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USoundMaterial, AbsorptionCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbsorptionCoefficient_MetaData), NewProp_AbsorptionCoefficient_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USoundMaterial_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USoundMaterial_Statics::NewProp_ScatteringFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USoundMaterial_Statics::NewProp_ReflectionFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USoundMaterial_Statics::NewProp_AbsorptionCoefficient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USoundMaterial_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USoundMaterial_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracing,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USoundMaterial_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USoundMaterial_Statics::ClassParams = {
	&USoundMaterial::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USoundMaterial_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USoundMaterial_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USoundMaterial_Statics::Class_MetaDataParams), Z_Construct_UClass_USoundMaterial_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USoundMaterial()
{
	if (!Z_Registration_Info_UClass_USoundMaterial.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USoundMaterial.OuterSingleton, Z_Construct_UClass_USoundMaterial_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USoundMaterial.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USoundMaterial);
USoundMaterial::~USoundMaterial() {}
// ********** End Class USoundMaterial *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h__Script_AudioTracing_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USoundMaterial, USoundMaterial::StaticClass, TEXT("USoundMaterial"), &Z_Registration_Info_UClass_USoundMaterial, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USoundMaterial), 1606478183U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h__Script_AudioTracing_2325658041(TEXT("/Script/AudioTracing"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h__Script_AudioTracing_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Sound_SoundMaterial_h__Script_AudioTracing_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
