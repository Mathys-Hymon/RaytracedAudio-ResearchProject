// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AudioTracingSettings.generated.h"

// Settings for the Audio Tracing
UCLASS(config = AudioTracing, DefaultConfig, meta = (DisplayName = "Audio Tracing"))
class UAudioTracingSettings : public UDeveloperSettings
{
    GENERATED_BODY()
    
public:
    UAudioTracingSettings();

#if WITH_EDITOR
    virtual bool CanEditChange(const FProperty* InProperty) const override;

    virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
    
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

    void UpdateConsoleVariablesFromSettings();
#endif
    
    /**
     * Enables or disables the entire hardware-accelerated audio tracing feature.
     * Requires a project restart to take full effect.
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Audio Tracing", meta = (
        ConsoleVariable = "AudioTracing.HardwareRayTracing",
        ConfigRestartRequired = true))
    bool bEnableHardwareRaytracing;

    /**
     * The minimum time interval in seconds between audio tracing calculations.
     * Increasing this value reduces CPU usage but lowers the responsiveness of environmental audio changes.
     * Recommended values are between 0.0333 (33ms) and 0.15 (150ms).
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Performance", DisplayName = "Minimum Update Interval (s)", meta = (
        ConsoleVariable = "AudioTracing.MinUpdateInterval",
        ClampMin = "0.016", UIMin = "0.016", ClampMax = "0.25", UIMax = "0.25"))
    float MinUpdateInterval;
    
    /**
     * The maximum number of times a ray can reflect off surfaces.
     * Higher values produce more realistic reverberation but increase computational cost.
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Hardware Raytracing", meta = (
        ConsoleVariable = "AudioTracing.HardwareRayTracing.MaxReflectionDepth",
        ClampMin = "8", ClampMax = "32", UIMin = "8", UIMax = "32"))
    int32 MaxReflection;

    /**
     * The number of rays to cast from the listener for calculating reflections and occlusion.
     * More rays result in a more accurate and stable simulation, at a higher performance cost.
     * This setting cannot be changed during gameplay.
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Hardware Raytracing", meta = (
        ClampMin = "512", ClampMax = "2048", UIMin = "512", UIMax = "2048"))
    int32 RayCount;

    /**
     * The speed of sound in centimeters per second.
     * Used for time-of-flight calculations to determine delay and distance.
     * Default: 34,300 cm/s
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General", DisplayName = "Speed of Sound (cm/s)", meta = (
        ConsoleVariable = "AudioTracing.SoundSpeed"))
    float SoundSpeed;

    /**
     * The simulated width of the listener's head in centimeters.
     * Used for binaural audio calculations such as Interaural Time Difference (ITD).
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General", DisplayName = "Listener Head Width (cm)", meta = (
        ConsoleVariable = "AudioTracing.HeadWidth"))
    float HeadWidth;

    /**
     * The maximum time in seconds a sound ray can travel, determining its maximum distance.
     * Max Trace Distance = Speed of Sound * Max Trace Time.
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Hardware Raytracing", meta = (
        ConsoleVariable = "AudioTracing.HardwareRayTracing.MaxTraceTime",
        ClampMin = "15.0", ClampMax = "45.0", UIMin = "15.0", UIMax = "45.0"))
    float MaxTraceTime;

    /**
     * The maximum number of concurrently active sound sources to trace against per frame.
     * Limiting this helps control performance in scenes with many sounds.
     * When this limit is exceeded, the plugin will only process the sources closest to the listener.
     * Any sounds beyond this count will fall back to standard audio playback without tracing effects.
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Hardware Raytracing", meta = (
        ConsoleVariable = "AudioTracing.HardwareRayTracing.MaxActiveSoundSources",
        ClampMin = "0", ClampMax = "32", UIMin = "0", UIMax = "32"))
    int32 MaxActiveSoundSources;

    /**
     * The starting float4 index in the Custom Primitive Data to read sound material properties from.
     * This index is counted in float4 units (groups of 4 floats).
     * 
     * Example:
     * - Index 0 corresponds to CustomPrimitiveData[0..3]
     * - Index 1 corresponds to CustomPrimitiveData[4..7]
     * 
     * Ensure this does not overlap with other systems using Custom Primitive Data.
     * 
     * Set to a value outside the valid range [0, 8] (e.g., 9 or higher) to disable reading custom data.
     * Disabling this will cause all objects to use default sound material properties.
     */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Hardware Raytracing",
        DisplayName = "Custom Primitive Data Start Index (float4)", meta = (
        UIMin = "-1", UIMax = "9", ClampMin = "-1"))
    int32 CustomPrimitiveDataStartFloat4Index;

    /**
    * Path of submix has short reverb effector.
    */
    UPROPERTY(GlobalConfig, BlueprintReadWrite, EditAnywhere, Category = "Reverb|Submix", meta = (
        AllowedClasses = "/Script/Engine.SoundSubmix"))
    FSoftObjectPath ShortReverbSubmixPath;
    
    /**
    * Path of submix has medium reverb effector.
    */
    UPROPERTY(GlobalConfig, BlueprintReadWrite, EditAnywhere, Category = "Reverb|Submix", meta = (
        AllowedClasses = "/Script/Engine.SoundSubmix"))
    FSoftObjectPath MediumReverbSubmixPath;
    
    /**
    * Path of submix has long reverb effector.
    */
    UPROPERTY(GlobalConfig, BlueprintReadWrite, EditAnywhere, Category = "Reverb|Submix", meta = (
        AllowedClasses = "/Script/Engine.SoundSubmix"))
    FSoftObjectPath LongReverbSubmixPath;

    /**
    * Gain of Direct Sound. 
    */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General|Advanced", DisplayName = "Direct Sound Gain (dB)", meta = (
        ClampMin = "-60.0", ClampMax = "10.0", UIMin = "-60.0", UIMax = "10.0"))
    float DirectSoundGain;

    /**
    * Gain of Early Reflection Sound.
    */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General|Advanced", DisplayName = "Early Reflection Gain (dB)", meta = (
        ClampMin = "-60.0", ClampMax = "10.0", UIMin = "-60.0", UIMax = "10.0"))
    float EarlyReflectionGain;

    /**
    * Gain of Reverb Sound.
    */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General|Advanced", DisplayName = "Reverb Gain (dB)", meta = (
        ClampMin = "-60.0", ClampMax = "10.0", UIMin = "-60.0", UIMax = "10.0"))
    float ReverbGain;

    /**
    * Maximum number of Early Reflections to be played.
    */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General|Advanced", DisplayName = "Early Reflection Max Count", meta = (
        ClampMin = "0", ClampMax = "20", UIMin = "0", UIMax = "20"))
    int32 EarlyReflectionMaxCount;

    /**
    * A Multiplier will be applied to reverberation time.
    * This helps compensate when the number of Max Reflection is reduced for performance reasons.
    */
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "General|Advanced", DisplayName = "Reverb Time Multiplier", meta = (
        ClampMin = "0.25", ClampMax = "4", UIMin = "0.25", UIMax = "4"))
    float ReverbTimeMultiplier;

    virtual FName GetCategoryName() const override;

    virtual void PostInitProperties() override;
    
private:
    bool IsHardwareRaytracingEnabled() const;
    
#if WITH_EDITOR
    void UpdateAllSoundMaterialComponents() const;
    
    int32 PrevCustomPrimitiveDataStartFloat4Index = -1;
#endif
};
