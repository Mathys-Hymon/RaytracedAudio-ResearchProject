// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Types/AudioRayTypes.h"

#ifdef AUDIOTRACING_AudioRayTypes_generated_h
#error "AudioRayTypes.generated.h already included, missing '#pragma once' in AudioRayTypes.h"
#endif
#define AUDIOTRACING_AudioRayTypes_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RayTracedAudio_Plugins_AudioTra58f346f95d02V1_Source_AudioTracing_Public_Types_AudioRayTypes_h

// ********** Begin Enum ETracedRayType ************************************************************
#define FOREACH_ENUM_ETRACEDRAYTYPE(op) \
	op(ETracedRayType::ETT_DirectSound) \
	op(ETracedRayType::ETT_EarlyReflectionSound) \
	op(ETracedRayType::ETT_ReverbSound) 

enum class ETracedRayType : uint32;
template<> struct TIsUEnumClass<ETracedRayType> { enum { Value = true }; };
template<> AUDIOTRACING_API UEnum* StaticEnum<ETracedRayType>();
// ********** End Enum ETracedRayType **************************************************************

// ********** Begin Enum EATDistanceAttenuationModel ***********************************************
#define FOREACH_ENUM_EATDISTANCEATTENUATIONMODEL(op) \
	op(EATDistanceAttenuationModel::EDA_Linear) \
	op(EATDistanceAttenuationModel::EDA_Logarithmic) \
	op(EATDistanceAttenuationModel::EDA_Inverse) 

enum class EATDistanceAttenuationModel : uint32;
template<> struct TIsUEnumClass<EATDistanceAttenuationModel> { enum { Value = true }; };
template<> AUDIOTRACING_API UEnum* StaticEnum<EATDistanceAttenuationModel>();
// ********** End Enum EATDistanceAttenuationModel *************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
