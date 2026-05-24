// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "Sound/AudioTracingSpatializerFactory.h"

#include "Sound/AudioTracingSpatializer.h"

TAudioSpatializationPtr FAudioTracingSpatializerFactory::CreateNewSpatializationPlugin(FAudioDevice* OwningDevice)
{
	return MakeShared<FAudioTracingSpatializer, ESPMode::ThreadSafe>();
}
