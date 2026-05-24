// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAudioTracing_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_AudioTracing;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_AudioTracing()
	{
		if (!Z_Registration_Info_UPackage__Script_AudioTracing.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/AudioTracing",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xE8B8D36D,
				0x1D8D30C0,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_AudioTracing.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_AudioTracing.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_AudioTracing(Z_Construct_UPackage__Script_AudioTracing, TEXT("/Script/AudioTracing"), Z_Registration_Info_UPackage__Script_AudioTracing, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xE8B8D36D, 0x1D8D30C0));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
