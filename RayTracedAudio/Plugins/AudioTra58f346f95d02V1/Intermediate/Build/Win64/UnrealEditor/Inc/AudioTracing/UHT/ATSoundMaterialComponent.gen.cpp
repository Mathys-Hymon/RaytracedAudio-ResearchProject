// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Components/ATSoundMaterialComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeATSoundMaterialComponent() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACING_API UClass* Z_Construct_UClass_UATSoundMaterialComponent();
AUDIOTRACING_API UClass* Z_Construct_UClass_UATSoundMaterialComponent_NoRegister();
AUDIOTRACING_API UClass* Z_Construct_UClass_USoundMaterial_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
UPackage* Z_Construct_UPackage__Script_AudioTracing();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UATSoundMaterialComponent Function GetAbsorptionCoefficient **************
struct Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics
{
	struct ATSoundMaterialComponent_eventGetAbsorptionCoefficient_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventGetAbsorptionCoefficient_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "GetAbsorptionCoefficient", Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::ATSoundMaterialComponent_eventGetAbsorptionCoefficient_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::ATSoundMaterialComponent_eventGetAbsorptionCoefficient_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execGetAbsorptionCoefficient)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetAbsorptionCoefficient();
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function GetAbsorptionCoefficient ****************

// ********** Begin Class UATSoundMaterialComponent Function GetReflectionFactor *******************
struct Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics
{
	struct ATSoundMaterialComponent_eventGetReflectionFactor_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventGetReflectionFactor_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "GetReflectionFactor", Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::ATSoundMaterialComponent_eventGetReflectionFactor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::ATSoundMaterialComponent_eventGetReflectionFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execGetReflectionFactor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetReflectionFactor();
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function GetReflectionFactor *********************

// ********** Begin Class UATSoundMaterialComponent Function GetScatteringFactor *******************
struct Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics
{
	struct ATSoundMaterialComponent_eventGetScatteringFactor_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventGetScatteringFactor_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "GetScatteringFactor", Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::ATSoundMaterialComponent_eventGetScatteringFactor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::ATSoundMaterialComponent_eventGetScatteringFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execGetScatteringFactor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetScatteringFactor();
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function GetScatteringFactor *********************

// ********** Begin Class UATSoundMaterialComponent Function GetSoundMaterial **********************
struct Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics
{
	struct ATSoundMaterialComponent_eventGetSoundMaterial_Parms
	{
		USoundMaterial* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventGetSoundMaterial_Parms, ReturnValue), Z_Construct_UClass_USoundMaterial_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "GetSoundMaterial", Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::ATSoundMaterialComponent_eventGetSoundMaterial_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::ATSoundMaterialComponent_eventGetSoundMaterial_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execGetSoundMaterial)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USoundMaterial**)Z_Param__Result=P_THIS->GetSoundMaterial();
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function GetSoundMaterial ************************

// ********** Begin Class UATSoundMaterialComponent Function IsComponentOverrideSoundMaterial ******
struct Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics
{
	struct ATSoundMaterialComponent_eventIsComponentOverrideSoundMaterial_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((ATSoundMaterialComponent_eventIsComponentOverrideSoundMaterial_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ATSoundMaterialComponent_eventIsComponentOverrideSoundMaterial_Parms), &Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "IsComponentOverrideSoundMaterial", Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::ATSoundMaterialComponent_eventIsComponentOverrideSoundMaterial_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::ATSoundMaterialComponent_eventIsComponentOverrideSoundMaterial_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execIsComponentOverrideSoundMaterial)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsComponentOverrideSoundMaterial();
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function IsComponentOverrideSoundMaterial ********

// ********** Begin Class UATSoundMaterialComponent Function OnSoundMaterialPropertyChanged ********
#if WITH_EDITOR
struct Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "OnSoundMaterialPropertyChanged", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x20040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
#endif // WITH_EDITOR
#if WITH_EDITOR
DEFINE_FUNCTION(UATSoundMaterialComponent::execOnSoundMaterialPropertyChanged)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSoundMaterialPropertyChanged();
	P_NATIVE_END;
}
#endif // WITH_EDITOR
// ********** End Class UATSoundMaterialComponent Function OnSoundMaterialPropertyChanged **********

// ********** Begin Class UATSoundMaterialComponent Function SetAbsorptionCoefficient **************
struct Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics
{
	struct ATSoundMaterialComponent_eventSetAbsorptionCoefficient_Parms
	{
		float NewAbsorptionCoefficient;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewAbsorptionCoefficient;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::NewProp_NewAbsorptionCoefficient = { "NewAbsorptionCoefficient", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventSetAbsorptionCoefficient_Parms, NewAbsorptionCoefficient), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::NewProp_NewAbsorptionCoefficient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "SetAbsorptionCoefficient", Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::ATSoundMaterialComponent_eventSetAbsorptionCoefficient_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::ATSoundMaterialComponent_eventSetAbsorptionCoefficient_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execSetAbsorptionCoefficient)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewAbsorptionCoefficient);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAbsorptionCoefficient(Z_Param_NewAbsorptionCoefficient);
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function SetAbsorptionCoefficient ****************

// ********** Begin Class UATSoundMaterialComponent Function SetComponentOverrideSoundMaterial *****
struct Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics
{
	struct ATSoundMaterialComponent_eventSetComponentOverrideSoundMaterial_Parms
	{
		bool bOverride;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bOverride_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverride;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::NewProp_bOverride_SetBit(void* Obj)
{
	((ATSoundMaterialComponent_eventSetComponentOverrideSoundMaterial_Parms*)Obj)->bOverride = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::NewProp_bOverride = { "bOverride", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ATSoundMaterialComponent_eventSetComponentOverrideSoundMaterial_Parms), &Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::NewProp_bOverride_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::NewProp_bOverride,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "SetComponentOverrideSoundMaterial", Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::ATSoundMaterialComponent_eventSetComponentOverrideSoundMaterial_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::ATSoundMaterialComponent_eventSetComponentOverrideSoundMaterial_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execSetComponentOverrideSoundMaterial)
{
	P_GET_UBOOL(Z_Param_bOverride);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetComponentOverrideSoundMaterial(Z_Param_bOverride);
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function SetComponentOverrideSoundMaterial *******

// ********** Begin Class UATSoundMaterialComponent Function SetReflectionFactor *******************
struct Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics
{
	struct ATSoundMaterialComponent_eventSetReflectionFactor_Parms
	{
		float NewReflectionFactor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewReflectionFactor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::NewProp_NewReflectionFactor = { "NewReflectionFactor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventSetReflectionFactor_Parms, NewReflectionFactor), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::NewProp_NewReflectionFactor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "SetReflectionFactor", Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::ATSoundMaterialComponent_eventSetReflectionFactor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::ATSoundMaterialComponent_eventSetReflectionFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execSetReflectionFactor)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewReflectionFactor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetReflectionFactor(Z_Param_NewReflectionFactor);
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function SetReflectionFactor *********************

// ********** Begin Class UATSoundMaterialComponent Function SetScatteringFactor *******************
struct Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics
{
	struct ATSoundMaterialComponent_eventSetScatteringFactor_Parms
	{
		float NewScatteringFactor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewScatteringFactor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::NewProp_NewScatteringFactor = { "NewScatteringFactor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventSetScatteringFactor_Parms, NewScatteringFactor), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::NewProp_NewScatteringFactor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "SetScatteringFactor", Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::ATSoundMaterialComponent_eventSetScatteringFactor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::ATSoundMaterialComponent_eventSetScatteringFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execSetScatteringFactor)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewScatteringFactor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetScatteringFactor(Z_Param_NewScatteringFactor);
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function SetScatteringFactor *********************

// ********** Begin Class UATSoundMaterialComponent Function SetSoundMaterial **********************
struct Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics
{
	struct ATSoundMaterialComponent_eventSetSoundMaterial_Parms
	{
		USoundMaterial* NewMaterial;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio Tracing|Sound Material Component" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NewMaterial;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::NewProp_NewMaterial = { "NewMaterial", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATSoundMaterialComponent_eventSetSoundMaterial_Parms, NewMaterial), Z_Construct_UClass_USoundMaterial_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::NewProp_NewMaterial,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UATSoundMaterialComponent, nullptr, "SetSoundMaterial", Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::PropPointers), sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::ATSoundMaterialComponent_eventSetSoundMaterial_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::Function_MetaDataParams), Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::ATSoundMaterialComponent_eventSetSoundMaterial_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UATSoundMaterialComponent::execSetSoundMaterial)
{
	P_GET_OBJECT(USoundMaterial,Z_Param_NewMaterial);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSoundMaterial(Z_Param_NewMaterial);
	P_NATIVE_END;
}
// ********** End Class UATSoundMaterialComponent Function SetSoundMaterial ************************

// ********** Begin Class UATSoundMaterialComponent ************************************************
void UATSoundMaterialComponent::StaticRegisterNativesUATSoundMaterialComponent()
{
	UClass* Class = UATSoundMaterialComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetAbsorptionCoefficient", &UATSoundMaterialComponent::execGetAbsorptionCoefficient },
		{ "GetReflectionFactor", &UATSoundMaterialComponent::execGetReflectionFactor },
		{ "GetScatteringFactor", &UATSoundMaterialComponent::execGetScatteringFactor },
		{ "GetSoundMaterial", &UATSoundMaterialComponent::execGetSoundMaterial },
		{ "IsComponentOverrideSoundMaterial", &UATSoundMaterialComponent::execIsComponentOverrideSoundMaterial },
#if WITH_EDITOR
		{ "OnSoundMaterialPropertyChanged", &UATSoundMaterialComponent::execOnSoundMaterialPropertyChanged },
#endif // WITH_EDITOR
		{ "SetAbsorptionCoefficient", &UATSoundMaterialComponent::execSetAbsorptionCoefficient },
		{ "SetComponentOverrideSoundMaterial", &UATSoundMaterialComponent::execSetComponentOverrideSoundMaterial },
		{ "SetReflectionFactor", &UATSoundMaterialComponent::execSetReflectionFactor },
		{ "SetScatteringFactor", &UATSoundMaterialComponent::execSetScatteringFactor },
		{ "SetSoundMaterial", &UATSoundMaterialComponent::execSetSoundMaterial },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UATSoundMaterialComponent;
UClass* UATSoundMaterialComponent::GetPrivateStaticClass()
{
	using TClass = UATSoundMaterialComponent;
	if (!Z_Registration_Info_UClass_UATSoundMaterialComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ATSoundMaterialComponent"),
			Z_Registration_Info_UClass_UATSoundMaterialComponent.InnerSingleton,
			StaticRegisterNativesUATSoundMaterialComponent,
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
	return Z_Registration_Info_UClass_UATSoundMaterialComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UATSoundMaterialComponent_NoRegister()
{
	return UATSoundMaterialComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UATSoundMaterialComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "AudioTracing" },
		{ "DisplayName", "Audio Tracing Sound Material" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Components/ATSoundMaterialComponent.h" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundMaterial_MetaData[] = {
		{ "Category", "Audio Tracing" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOverrideSoundMaterial_MetaData[] = {
		{ "Category", "Audio Tracing|Override" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatteringFactor_MetaData[] = {
		{ "Category", "Audio Tracing|Override" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "EditCondition", "bOverrideSoundMaterial" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReflectionFactor_MetaData[] = {
		{ "Category", "Audio Tracing|Override" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "EditCondition", "bOverrideSoundMaterial" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbsorptionCoefficient_MetaData[] = {
		{ "Category", "Audio Tracing|Override" },
		{ "ClampMin", "0.0" },
		{ "DisplayName", "Absorption Coefficient (per cm)" },
		{ "EditCondition", "bOverrideSoundMaterial" },
		{ "ModuleRelativePath", "Public/Components/ATSoundMaterialComponent.h" },
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SoundMaterial;
	static void NewProp_bOverrideSoundMaterial_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverrideSoundMaterial;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScatteringFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReflectionFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AbsorptionCoefficient;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_GetAbsorptionCoefficient, "GetAbsorptionCoefficient" }, // 1945610991
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_GetReflectionFactor, "GetReflectionFactor" }, // 3424749068
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_GetScatteringFactor, "GetScatteringFactor" }, // 649575270
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_GetSoundMaterial, "GetSoundMaterial" }, // 1746659861
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_IsComponentOverrideSoundMaterial, "IsComponentOverrideSoundMaterial" }, // 3523479283
#if WITH_EDITOR
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_OnSoundMaterialPropertyChanged, "OnSoundMaterialPropertyChanged" }, // 1363252207
#endif // WITH_EDITOR
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_SetAbsorptionCoefficient, "SetAbsorptionCoefficient" }, // 4256554623
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_SetComponentOverrideSoundMaterial, "SetComponentOverrideSoundMaterial" }, // 1775310233
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_SetReflectionFactor, "SetReflectionFactor" }, // 1955713871
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_SetScatteringFactor, "SetScatteringFactor" }, // 3560411182
		{ &Z_Construct_UFunction_UATSoundMaterialComponent_SetSoundMaterial, "SetSoundMaterial" }, // 4242978754
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UATSoundMaterialComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_SoundMaterial = { "SoundMaterial", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UATSoundMaterialComponent, SoundMaterial), Z_Construct_UClass_USoundMaterial_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundMaterial_MetaData), NewProp_SoundMaterial_MetaData) };
void Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_bOverrideSoundMaterial_SetBit(void* Obj)
{
	((UATSoundMaterialComponent*)Obj)->bOverrideSoundMaterial = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_bOverrideSoundMaterial = { "bOverrideSoundMaterial", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UATSoundMaterialComponent), &Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_bOverrideSoundMaterial_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOverrideSoundMaterial_MetaData), NewProp_bOverrideSoundMaterial_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_ScatteringFactor = { "ScatteringFactor", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UATSoundMaterialComponent, ScatteringFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatteringFactor_MetaData), NewProp_ScatteringFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_ReflectionFactor = { "ReflectionFactor", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UATSoundMaterialComponent, ReflectionFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReflectionFactor_MetaData), NewProp_ReflectionFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_AbsorptionCoefficient = { "AbsorptionCoefficient", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UATSoundMaterialComponent, AbsorptionCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbsorptionCoefficient_MetaData), NewProp_AbsorptionCoefficient_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UATSoundMaterialComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_SoundMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_bOverrideSoundMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_ScatteringFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_ReflectionFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UATSoundMaterialComponent_Statics::NewProp_AbsorptionCoefficient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UATSoundMaterialComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UATSoundMaterialComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_AudioTracing,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UATSoundMaterialComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UATSoundMaterialComponent_Statics::ClassParams = {
	&UATSoundMaterialComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UATSoundMaterialComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UATSoundMaterialComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UATSoundMaterialComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UATSoundMaterialComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UATSoundMaterialComponent()
{
	if (!Z_Registration_Info_UClass_UATSoundMaterialComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UATSoundMaterialComponent.OuterSingleton, Z_Construct_UClass_UATSoundMaterialComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UATSoundMaterialComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UATSoundMaterialComponent);
UATSoundMaterialComponent::~UATSoundMaterialComponent() {}
// ********** End Class UATSoundMaterialComponent **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h__Script_AudioTracing_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UATSoundMaterialComponent, UATSoundMaterialComponent::StaticClass, TEXT("UATSoundMaterialComponent"), &Z_Registration_Info_UClass_UATSoundMaterialComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UATSoundMaterialComponent), 1911576044U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h__Script_AudioTracing_2083824047(TEXT("/Script/AudioTracing"),
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h__Script_AudioTracing_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Components_ATSoundMaterialComponent_h__Script_AudioTracing_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
