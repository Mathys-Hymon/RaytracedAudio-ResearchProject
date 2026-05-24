// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Sound/ATAudioSourceDataOverrideFactory.h"
#include "Sound/AudioTracingSpatializerFactory.h"

namespace AudioTracing
{
    AUDIOTRACING_API float GetMaxTraceDistance();
    AUDIOTRACING_API float GetSoundSpeed();
    AUDIOTRACING_API float GetMaxTraceTime();
    AUDIOTRACING_API float GetHeadWidth();
    AUDIOTRACING_API uint32 GetCustomPrimitiveDataStartFloat4Index();
    AUDIOTRACING_API int32 GetMaxActiveSoundSources();
    AUDIOTRACING_API bool IsVirtualAudioDebugEnabled();
    AUDIOTRACING_API float GetMinUpdateInterval();
    
    void SetCustomPrimitiveDataStartFloat4Index(int32 NewIndex);
}

class FAudioTracingModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    FATAudioSourceDataOverrideFactory ATAudioSourceDataOverrideFactory;
    FAudioTracingSpatializerFactory ATSpatializerFactory;

#if WITH_EDITOR
private:
    void InitializeSettings();
    void RegisterCVarCallbacks();
    void UnregisterSettingsAndConsoleVariables();

    FDelegateHandle OnPostEngineInitHandle;
    TMap<FName, FDelegateHandle> CVarChangedHandles;
#endif
};
