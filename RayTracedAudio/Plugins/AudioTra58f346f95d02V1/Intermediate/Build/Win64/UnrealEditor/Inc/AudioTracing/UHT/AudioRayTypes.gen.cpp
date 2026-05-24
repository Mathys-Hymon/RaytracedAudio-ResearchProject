// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Types/AudioRayTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAudioRayTypes() {}

// ********** Begin Cross Module References ********************************************************
AUDIOTRACING_API UEnum* Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel();
AUDIOTRACING_API UEnum* Z_Construct_UEnum_AudioTracing_ETracedRayType();
UPackage* Z_Construct_UPackage__Script_AudioTracing();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ETracedRayType ************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETracedRayType;
static UEnum* ETracedRayType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETracedRayType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETracedRayType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AudioTracing_ETracedRayType, (UObject*)Z_Construct_UPackage__Script_AudioTracing(), TEXT("ETracedRayType"));
	}
	return Z_Registration_Info_UEnum_ETracedRayType.OuterSingleton;
}
template<> AUDIOTRACING_API UEnum* StaticEnum<ETracedRayType>()
{
	return ETracedRayType_StaticEnum();
}
struct Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ETT_DirectSound.Name", "ETracedRayType::ETT_DirectSound" },
		{ "ETT_EarlyReflectionSound.Comment", "// \xec\xa7\x81\xec\xa0\x91\xec\x9d\x8c\n" },
		{ "ETT_EarlyReflectionSound.Name", "ETracedRayType::ETT_EarlyReflectionSound" },
		{ "ETT_EarlyReflectionSound.ToolTip", "\xec\xa7\x81\xec\xa0\x91\xec\x9d\x8c" },
		{ "ETT_ReverbSound.Comment", "// \xeb\xb0\x98\xec\x82\xac\xec\x9d\x8c\n" },
		{ "ETT_ReverbSound.Name", "ETracedRayType::ETT_ReverbSound" },
		{ "ETT_ReverbSound.ToolTip", "\xeb\xb0\x98\xec\x82\xac\xec\x9d\x8c" },
		{ "ModuleRelativePath", "Public/Types/AudioRayTypes.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETracedRayType::ETT_DirectSound", (int64)ETracedRayType::ETT_DirectSound },
		{ "ETracedRayType::ETT_EarlyReflectionSound", (int64)ETracedRayType::ETT_EarlyReflectionSound },
		{ "ETracedRayType::ETT_ReverbSound", (int64)ETracedRayType::ETT_ReverbSound },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AudioTracing,
	nullptr,
	"ETracedRayType",
	"ETracedRayType",
	Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AudioTracing_ETracedRayType()
{
	if (!Z_Registration_Info_UEnum_ETracedRayType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETracedRayType.InnerSingleton, Z_Construct_UEnum_AudioTracing_ETracedRayType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETracedRayType.InnerSingleton;
}
// ********** End Enum ETracedRayType **************************************************************

// ********** Begin Enum EATDistanceAttenuationModel ***********************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EATDistanceAttenuationModel;
static UEnum* EATDistanceAttenuationModel_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EATDistanceAttenuationModel.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EATDistanceAttenuationModel.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel, (UObject*)Z_Construct_UPackage__Script_AudioTracing(), TEXT("EATDistanceAttenuationModel"));
	}
	return Z_Registration_Info_UEnum_EATDistanceAttenuationModel.OuterSingleton;
}
template<> AUDIOTRACING_API UEnum* StaticEnum<EATDistanceAttenuationModel>()
{
	return EATDistanceAttenuationModel_StaticEnum();
}
struct Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "EDA_Inverse.Name", "EATDistanceAttenuationModel::EDA_Inverse" },
		{ "EDA_Linear.Name", "EATDistanceAttenuationModel::EDA_Linear" },
		{ "EDA_Logarithmic.Name", "EATDistanceAttenuationModel::EDA_Logarithmic" },
		{ "ModuleRelativePath", "Public/Types/AudioRayTypes.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EATDistanceAttenuationModel::EDA_Linear", (int64)EATDistanceAttenuationModel::EDA_Linear },
		{ "EATDistanceAttenuationModel::EDA_Logarithmic", (int64)EATDistanceAttenuationModel::EDA_Logarithmic },
		{ "EATDistanceAttenuationModel::EDA_Inverse", (int64)EATDistanceAttenuationModel::EDA_Inverse },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AudioTracing,
	nullptr,
	"EATDistanceAttenuationModel",
	"EATDistanceAttenuationModel",
	Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel()
{
	if (!Z_Registration_Info_UEnum_EATDistanceAttenuationModel.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EATDistanceAttenuationModel.InnerSingleton, Z_Construct_UEnum_AudioTracing_EATDistanceAttenuationModel_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EATDistanceAttenuationModel.InnerSingleton;
}
// ********** End Enum EATDistanceAttenuationModel *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Types_AudioRayTypes_h__Script_AudioTracing_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ETracedRayType_StaticEnum, TEXT("ETracedRayType"), &Z_Registration_Info_UEnum_ETracedRayType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4129092712U) },
		{ EATDistanceAttenuationModel_StaticEnum, TEXT("EATDistanceAttenuationModel"), &Z_Registration_Info_UEnum_EATDistanceAttenuationModel, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2071801604U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Types_AudioRayTypes_h__Script_AudioTracing_2099987919(TEXT("/Script/AudioTracing"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Types_AudioRayTypes_h__Script_AudioTracing_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Types_AudioRayTypes_h__Script_AudioTracing_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
