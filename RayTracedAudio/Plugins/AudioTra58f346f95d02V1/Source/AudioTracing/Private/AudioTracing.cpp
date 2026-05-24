// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "AudioTracing.h"

#include "AudioTracingLog.h"
#include "Components/ATSoundMaterialComponent.h"
#include "Interfaces/IPluginManager.h"
#include "Features/IModularFeatures.h"
#include "ShaderCore.h"
#include "SceneTypes.h"
#include "Settings/AudioTracingSettings.h"
#include "Sound/SoundMaterial.h"

#define LOCTEXT_NAMESPACE "FAudioTracingModule"

void FAudioTracingModule::StartupModule()
{
    IModularFeatures::Get().RegisterModularFeature(FAudioTracingSpatializerFactory::GetModularFeatureName(), &ATSpatializerFactory);
    IModularFeatures::Get().RegisterModularFeature(FATAudioSourceDataOverrideFactory::GetModularFeatureName(), &ATAudioSourceDataOverrideFactory);
    
    const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("AudioTracing"))->GetBaseDir(), TEXT("Shaders"));
    if (!AllShaderSourceDirectoryMappings().Contains(TEXT("/AudioTracing")))
    {
        AddShaderSourceDirectoryMapping(TEXT("/AudioTracing"), PluginShaderDir);
    }

#if WITH_EDITOR
    OnPostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FAudioTracingModule::InitializeSettings);
#endif
}

void FAudioTracingModule::ShutdownModule()
{
    IModularFeatures::Get().UnregisterModularFeature(
        IAudioSourceDataOverrideFactory::GetModularFeatureName(), 
        &ATAudioSourceDataOverrideFactory
    );

    IModularFeatures::Get().UnregisterModularFeature(
        FAudioTracingSpatializerFactory::GetModularFeatureName(), 
        &ATSpatializerFactory
    );

#if WITH_EDITOR
    if (OnPostEngineInitHandle.IsValid())
    {
        FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitHandle);
        OnPostEngineInitHandle.Reset();
    }
    
    UnregisterSettingsAndConsoleVariables();
#endif
}

#if WITH_EDITOR
void FAudioTracingModule::InitializeSettings()
{
    if (UAudioTracingSettings* AudioTracingSettings = GetMutableDefault<UAudioTracingSettings>())
    {
        AudioTracingSettings->UpdateConsoleVariablesFromSettings();
    }
    
    RegisterCVarCallbacks();
}

void FAudioTracingModule::RegisterCVarCallbacks()
{
    UAudioTracingSettings* AudioTracingSettings = GetMutableDefault<UAudioTracingSettings>();
    if (!AudioTracingSettings)
    {
        return;
    }

    for (TFieldIterator<FProperty> PropIt(AudioTracingSettings->GetClass()); PropIt; ++PropIt)
    {
        FProperty* Property = *PropIt;

        if (Property->HasMetaData(TEXT("ConsoleVariable")))
        {
            const FString& CVarName = Property->GetMetaData(TEXT("ConsoleVariable"));

            if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*CVarName))
            {
                if (FFloatProperty* FloatProperty = CastField<FFloatProperty>(Property))
                {
                    FloatProperty->SetPropertyValue_InContainer(AudioTracingSettings, CVar->GetFloat());
                    FDelegateHandle Handle = CVar->OnChangedDelegate().AddLambda(
                        [AudioTracingSettings, FloatProperty](IConsoleVariable* Var)
                        {
                            FloatProperty->SetPropertyValue_InContainer(AudioTracingSettings, Var->GetFloat());
                            AudioTracingSettings->UpdateSinglePropertyInConfigFile(FloatProperty, AudioTracingSettings->GetDefaultConfigFilename());
                        }
                    );
                    CVarChangedHandles.Add(MakeTuple(FName(CVarName), Handle));
                }
                else if (FIntProperty* IntProperty = CastField<FIntProperty>(Property))
                {
                    IntProperty->SetPropertyValue_InContainer(AudioTracingSettings, CVar->GetInt());
                    FDelegateHandle Handle = CVar->OnChangedDelegate().AddLambda(
                        [AudioTracingSettings, IntProperty](IConsoleVariable* Var)
                        {
                            IntProperty->SetPropertyValue_InContainer(AudioTracingSettings, Var->GetInt());
                            AudioTracingSettings->UpdateSinglePropertyInConfigFile(IntProperty, AudioTracingSettings->GetDefaultConfigFilename());
                        }
                    );
                    CVarChangedHandles.Add(MakeTuple(FName(CVarName), Handle));
                }
                else if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
                {
                    BoolProperty->SetPropertyValue_InContainer(AudioTracingSettings, CVar->GetBool());
                    FDelegateHandle Handle = CVar->OnChangedDelegate().AddLambda(
                        [AudioTracingSettings, BoolProperty](IConsoleVariable* Var)
                        {
                            BoolProperty->SetPropertyValue_InContainer(AudioTracingSettings, Var->GetBool());
                            AudioTracingSettings->UpdateSinglePropertyInConfigFile(BoolProperty, AudioTracingSettings->GetDefaultConfigFilename());
                        }
                    );
                    CVarChangedHandles.Add(MakeTuple(FName(CVarName), Handle));
                }
            }
        }
    }
}

void FAudioTracingModule::UnregisterSettingsAndConsoleVariables()
{
    for (const TPair<FName, FDelegateHandle>& Pair : CVarChangedHandles)
    {
        const FName& CVarName = Pair.Key;
        const FDelegateHandle& Handle = Pair.Value;

        if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*CVarName.ToString()))
        {
            CVar->OnChangedDelegate().Remove(Handle);
        }
    }

    CVarChangedHandles.Empty();
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAudioTracingModule, AudioTracing)


static TAutoConsoleVariable<float> CVarAudioTracingSoundSpeed(
    TEXT("AudioTracing.SoundSpeed"),
    34300.f,
    TEXT("The speed of sound used for time-of-flight calculations.\n")
    TEXT("Default: 34300.0 (343 m/s in cm/s)."),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<float> CVarAudioTracingMaxTraceTime(
    TEXT("AudioTracing.HardwareRayTracing.MaxTraceTime"),
    5.f,
    TEXT("The maximum time in seconds that a sound ray is allowed to travel. This determines the maximum trace distance (MaxTraceDistance = SoundSpeed * MaxTraceTime).\n")
    TEXT("Default: 5.0 s."),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<float> CVarAudioTracingHeadWidth(
    TEXT("AudioTracing.HeadWidth"),
    30.f,
    TEXT("The simulated width of the listener's head in centimeters. Used for binaural audio calculations such as Interaural Time Difference (ITD).\n")
    TEXT("Default: 30.0 cm."),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<int32> CVarAudioTracingShowDebugVirtualAudio(
    TEXT("AudioTracing.ShowDebugVirtualAudio"),
    0,
    TEXT("Visualize Virtual Audio for debugging purposes.\n")
    TEXT("0: Disable (default)\n")
    TEXT("1: Enable visualization."),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<int32> CVarAudioTracingMaxActiveSoundSources(
    TEXT("AudioTracing.HardwareRayTracing.MaxActiveSoundSources"),
    10,
    TEXT("The maximum number of active sound sources to consider for ray tracing calculations per frame.\n")
    TEXT("Higher values increase realism for complex scenes but have a significant performance cost. A value of 0 might disable the effect."),
    ECVF_RenderThreadSafe
);

static TAutoConsoleVariable<float> CVarAudioTracingMinUpdateInterval(
    TEXT("AudioTracing.MinUpdateInterval"),
    0.04f,
    TEXT("The minimum time interval in seconds between audio tracing calculations.\n")
    TEXT("Increasing this value reduces CPU usage but lowers the responsiveness of environmental audio changes.\n")
    TEXT("Recommended values are between 0.0333 (33ms) and 0.15 (150ms)."),
    ECVF_RenderThreadSafe
);

namespace AudioTracing
{
    static FThreadSafeCounter CustomPrimitiveDataStartFloat4Index(0);
}

float AudioTracing::GetMaxTraceDistance()
{
    return GetMaxTraceTime() * GetSoundSpeed();
}

float AudioTracing::GetSoundSpeed()
{
    if (IsInRenderingThread())
    {
        return CVarAudioTracingSoundSpeed.GetValueOnRenderThread();
    }
    if (IsInGameThread())
    {
        return CVarAudioTracingSoundSpeed.GetValueOnGameThread();
    }
    return CVarAudioTracingSoundSpeed.GetValueOnAnyThread();
}

float AudioTracing::GetMaxTraceTime()
{
    if (IsInRenderingThread())
    {
        return CVarAudioTracingMaxTraceTime.GetValueOnRenderThread();
    }
    if (IsInGameThread())
    {
        return CVarAudioTracingMaxTraceTime.GetValueOnGameThread();
    }
    return CVarAudioTracingMaxTraceTime.GetValueOnAnyThread();
}

float AudioTracing::GetHeadWidth()
{
    if (IsInRenderingThread())
    {
        return CVarAudioTracingHeadWidth.GetValueOnRenderThread();
    }
    if (IsInGameThread())
    {
        return CVarAudioTracingHeadWidth.GetValueOnGameThread();
    }
    return CVarAudioTracingHeadWidth.GetValueOnAnyThread();
}

uint32 AudioTracing::GetCustomPrimitiveDataStartFloat4Index()
{
    int32 UserFloat4Index = CustomPrimitiveDataStartFloat4Index.GetValue();
    
    constexpr uint32 NumAvailableFloat4Indices = FCustomPrimitiveData::NumCustomPrimitiveDataFloat4s; // 9
    constexpr uint32 DeactivationFloat4Index = FCustomPrimitiveData::NumCustomPrimitiveDataFloat4s;

    if (UserFloat4Index < 0)
    {
        return DeactivationFloat4Index;
    }
    
    constexpr uint32 NumProperties = USoundMaterial::NumProperties;
    constexpr uint32 RequiredFloat4Indices = (NumProperties + 3) / 4; // Round up to nearest multiple of 4
        
    if (UserFloat4Index + RequiredFloat4Indices > NumAvailableFloat4Indices)
    {
        UE_LOG(LogAudioTracing, Warning,
            TEXT("Invalid Custom Primitive Data Start Index %u for Audio Tracing: Not enough space for %d required properties. Custom Primitive Data Start Index must be <= %d. Using default value."),
            UserFloat4Index, RequiredFloat4Indices, NumAvailableFloat4Indices - RequiredFloat4Indices
        );
        
        return DeactivationFloat4Index;
    }
    
    return UserFloat4Index;
}

int32 AudioTracing::GetMaxActiveSoundSources()
{
    int32 MaxActiveSoundSources = 0;
    if (IsInRenderingThread())
    {
        MaxActiveSoundSources = CVarAudioTracingMaxActiveSoundSources.GetValueOnRenderThread();
    }
    else if (IsInGameThread())
    {
        MaxActiveSoundSources = CVarAudioTracingMaxActiveSoundSources.GetValueOnGameThread();
    }
    else
    {
        MaxActiveSoundSources = CVarAudioTracingMaxActiveSoundSources.GetValueOnAnyThread();
    }

    return FMath::Max(MaxActiveSoundSources, 0);
}

bool AudioTracing::IsVirtualAudioDebugEnabled()
{
    return CVarAudioTracingShowDebugVirtualAudio.GetValueOnAnyThread() > 0;
}

float AudioTracing::GetMinUpdateInterval()
{
    if (IsInGameThread())
    {
        return CVarAudioTracingMinUpdateInterval.GetValueOnGameThread();
    }
    return CVarAudioTracingMinUpdateInterval.GetValueOnAnyThread();
}

void AudioTracing::SetCustomPrimitiveDataStartFloat4Index(int32 NewIndex)
{
    CustomPrimitiveDataStartFloat4Index.Set(NewIndex);
}
