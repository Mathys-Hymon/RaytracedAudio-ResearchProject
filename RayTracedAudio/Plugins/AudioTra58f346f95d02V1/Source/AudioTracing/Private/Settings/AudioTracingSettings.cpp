// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "Settings/AudioTracingSettings.h"

#include "AudioTracing.h"
#include "Components/ATSoundMaterialComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/RendererSettings.h"
#include "Sound/SoundMaterial.h"
#include "Sound/SoundSubmix.h"
#include "UObject/UObjectIterator.h"

UAudioTracingSettings::UAudioTracingSettings()
    : bEnableHardwareRaytracing(true)
    , MinUpdateInterval(0.04f)
    , MaxReflection(16)
    , RayCount(1024)
    , SoundSpeed(34300.f)
    , HeadWidth(30.f)
    , MaxTraceTime(30.f)
    , MaxActiveSoundSources(10)
    , CustomPrimitiveDataStartFloat4Index(0)
    , DirectSoundGain(0.f)
    , EarlyReflectionGain(0.f)
    , ReverbGain(0.f)
    , EarlyReflectionMaxCount(20)
    , ReverbTimeMultiplier(1.f)
{
    bEnableHardwareRaytracing = bEnableHardwareRaytracing && IsHardwareRaytracingEnabled();
    
    ShortReverbSubmixPath = FString(TEXT("/AudioTracing/SoundEffects/AudioTracingSubMixShortTail.AudioTracingSubMixShortTail"));
    MediumReverbSubmixPath = FString(TEXT("/AudioTracing/SoundEffects/AudioTracingSubMixMidTail.AudioTracingSubMixMidTail"));
    LongReverbSubmixPath = FString(TEXT("/AudioTracing/SoundEffects/AudioTracingSubMixLongTail.AudioTracingSubMixLongTail"));
}

#if WITH_EDITOR
bool UAudioTracingSettings::CanEditChange(const FProperty* InProperty) const
{
    if (!Super::CanEditChange(InProperty))
    {
        return false;
    }

    const FName PropertyName = InProperty->GetFName();
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UAudioTracingSettings, bEnableHardwareRaytracing))
    {
        return IsHardwareRaytracingEnabled();
    }

    return IsHardwareRaytracingEnabled() && bEnableHardwareRaytracing;
}

void UAudioTracingSettings::PreEditChange(FProperty* PropertyAboutToChange)
{
    Super::PreEditChange(PropertyAboutToChange);
    
    if (PropertyAboutToChange &&
        PropertyAboutToChange->GetFName() == GET_MEMBER_NAME_CHECKED(UAudioTracingSettings, CustomPrimitiveDataStartFloat4Index))
    {
        PrevCustomPrimitiveDataStartFloat4Index = CustomPrimitiveDataStartFloat4Index;
    }
}

void UAudioTracingSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.Property)
    {
        ExportValuesToConsoleVariables(PropertyChangedEvent.Property);

        if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UAudioTracingSettings, CustomPrimitiveDataStartFloat4Index))
        {
            AudioTracing::SetCustomPrimitiveDataStartFloat4Index(CustomPrimitiveDataStartFloat4Index);
            
            UpdateAllSoundMaterialComponents();
        }
    }
}

void UAudioTracingSettings::UpdateConsoleVariablesFromSettings()
{
    for (TFieldIterator<FProperty> PropIt(GetClass()); PropIt; ++PropIt)
    {
        ExportValuesToConsoleVariables(*PropIt);
    }
}
#endif

FName UAudioTracingSettings::GetCategoryName() const
{
    return FName(TEXT("Plugins"));
}

void UAudioTracingSettings::PostInitProperties()
{
    Super::PostInitProperties();
    
    AudioTracing::SetCustomPrimitiveDataStartFloat4Index(CustomPrimitiveDataStartFloat4Index);

    LoadObject<USoundSubmix>(nullptr, *ShortReverbSubmixPath.ToString());
    LoadObject<USoundSubmix>(nullptr, *MediumReverbSubmixPath.ToString());
    LoadObject<USoundSubmix>(nullptr, *LongReverbSubmixPath.ToString());
}

bool UAudioTracingSettings::IsHardwareRaytracingEnabled() const
{
    if (const URendererSettings* RendererSettings = GetDefault<URendererSettings>())
    {
        return RendererSettings->bEnableRayTracing && RendererSettings->bUseHardwareRayTracingForLumen &&
            (RendererSettings->Reflections == EReflectionMethod::Lumen || RendererSettings->DynamicGlobalIllumination == EDynamicGlobalIlluminationMethod::Lumen);
    }
    return false;
}

#if WITH_EDITOR
void UAudioTracingSettings::UpdateAllSoundMaterialComponents() const
{
    for (TObjectIterator<UATSoundMaterialComponent> It; It; ++It)
    {
        UATSoundMaterialComponent* Comp = *It;
        if (IsValid(Comp) && !Comp->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
        {
            if (UPrimitiveComponent* ParentPrimitive = Cast<UPrimitiveComponent>(Comp->GetAttachParent()))
            {
                if (0 <= PrevCustomPrimitiveDataStartFloat4Index &&
                    PrevCustomPrimitiveDataStartFloat4Index < FCustomPrimitiveData::NumCustomPrimitiveDataFloat4s)
                {
                    const int32 PrevStartIndex = PrevCustomPrimitiveDataStartFloat4Index * 4;

                    ParentPrimitive->SetCustomPrimitiveDataFloat(PrevStartIndex, 0.0f);
                    ParentPrimitive->SetCustomPrimitiveDataFloat(PrevStartIndex + 1, 0.0f);
                    ParentPrimitive->SetCustomPrimitiveDataFloat(PrevStartIndex + 2, 0.0f);
                }
            }
            
            Comp->SetSoundMaterialCustomPrimitiveData();
        }
    }
}
#endif
