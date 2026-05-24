// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "Sound/ATAudioSourceDataOverrideFactory.h"
#include "Sound/ATAudioSourceDataOverride.h"
#include "AudioDevice.h"

TAudioSourceDataOverridePtr FATAudioSourceDataOverrideFactory::CreateNewSourceDataOverridePlugin(FAudioDevice* OwningDevice)
{
    return MakeShared<FATAudioSourceDataOverride, ESPMode::ThreadSafe>();
}
