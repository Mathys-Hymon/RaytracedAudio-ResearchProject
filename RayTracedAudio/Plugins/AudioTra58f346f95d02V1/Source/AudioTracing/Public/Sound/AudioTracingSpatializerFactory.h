// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAudioExtensionPlugin.h"

class FAudioDevice;

class FAudioTracingSpatializerFactory : public IAudioSpatializationFactory
{
public:
    virtual FString GetDisplayName() override
    {
        return FString(TEXT("Audio Tracing Spatializer"));
    }
    
    virtual bool SupportsPlatform(const FString& PlatformName) override
    {
        return PlatformName == FString(TEXT("Windows"));
    }
    
    virtual int32 GetMaxSupportedChannels() override
    {
        return 2;
    }
    
    virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) override;
    
};