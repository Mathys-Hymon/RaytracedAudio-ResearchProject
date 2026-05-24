// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Sound/SoundSubmix.h"
#include "Types/AudioRayTypes.h"
#include "AudioTracingWorldSubsystem.generated.h"

class FATParameterizeRayToAudioAlgorithmBase;
class FATSceneViewExtension;
class FATAudioSourceDataOverride;
struct FSoundAttenuationSettings;

DECLARE_DELEGATE_OneParam(FOnTracedDataReceivedSignature, FAudioTraceResult&);

/**
 * 
 */
UCLASS()
class AUDIOTRACING_API UAudioTracingWorldSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()
    
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    virtual void Deinitialize() override;

    virtual void Tick(float DeltaTime) override;
    
    virtual TStatId GetStatId() const override;

    UFUNCTION(BlueprintCallable, Category = "AudioTracing")
    void SetDebugVirtualAudioEnabled(bool bIsEnabled);

    const TArray<FVector>& GetRayDirections() const;

    void SetRayCount(int32 NewRayCount);

    TArray<FActiveSoundProxy> GetActiveSounds() const;

    TArray<FActiveSoundProxy> GetBypassSounds() const;

protected:
    virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

private:
    mutable FCriticalSection ActiveSoundProxyMutex;
    
    TArray<FActiveSoundProxy> ActiveSoundProxy;

    TArray<FActiveSoundProxy> BypassActiveSoundProxy;

    void UpdateActiveSound(); 
    
    uint8 bDebugVirtualAudio : 1 = false;

    uint8 bIsRayCountDirty : 1 = false;

    uint8 bIsActiveSoundExist : 1 = false;
    
    int32 RayCount = 0;

    TArray<FVector> RayDirections;

    const int32 MaxNumSubmix = 128;

    void UpdateBypassParam();

    FAudioTraceResult BypassAudioResult;

    void UpdateHardwareRaytracingParam();

    void SendTracedDataReceived(FAudioTraceResult& RayTracedResult);

    void SendBypassData();

    void ProcessDebugVirtualAudio();

    TSharedPtr<FATSceneViewExtension, ESPMode::ThreadSafe> ATSceneViewExtension;

    FATAudioSourceDataOverride* CachedAudioSourceDataOverride = nullptr;

    // Receive Raytracing Result
    void PollRenderThreadResults() const;

    // Delegate when execute on Receiving Raytracing
    FOnTracedDataReceivedSignature OnTracedDataReceived;

    bool GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const;

    TSharedPtr<FDebugDrawData, ESPMode::ThreadSafe> CachedDebugData;

    

public:
    FORCEINLINE FOnTracedDataReceivedSignature& GetTracedDataReceivedDelegate()
    {
        return OnTracedDataReceived;
    }

    FATAudioSourceDataOverride* GetAudioTracingPlugins();
};