// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAudioExtensionPlugin.h"

class FAudioDevice;

class FATAudioSourceDataOverrideFactory : public IAudioSourceDataOverrideFactory
{
public:
    virtual FString GetDisplayName() override
    {
        static FString DisplayName = FString(TEXT("Audio Tracing Audio Source Data Override"));
        return DisplayName;
    }
    
    virtual bool SupportsPlatform(const FString& PlatformName) override
    {
        return PlatformName == FString(TEXT("Windows"));
    }

    virtual TAudioSourceDataOverridePtr CreateNewSourceDataOverridePlugin(FAudioDevice* OwningDevice) override;
};
