// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Containers/ArrayView.h"
#include "Containers/Map.h"
#include "DSP/Delay.h"
#include "DSP/AlignedBuffer.h"
#include "IAudioExtensionPlugin.h"
#include "HAL/CriticalSection.h"

struct FAudioRenderData;

struct FAudioTracingSpatialTapDelayInfo
{
    FAudioTracingSpatialTapDelayInfo();

    void Init(const float InSoundSpeed, const float InBlockSample, const float InSampleRate, const float InInterpolationTime, bool InDontIterpolationInit = false);

    FVector GetChannelLocation() const;
    FVector GetEmitterLocation() const;

    void SetLocationsAndVolume(const FVector& RelativeChannelLocation, const FVector& RelativeEmitterLocation, const float Volume);

    float GetGainValue(float NextTimeSec = 0.f);
    float GetDelayValue(float NextTimeSec = 0.f);

    void LifeDown();
    bool IsFadeOut() const;
    bool IsDone() const;

private:
    FVector ChannelLocation;
    FVector EmitterLocation;

    float BlockSample;
    float SoundSpeed; // cm/s
    float SampleRate; // hz
    float InterpolationTime;  // ms

    Audio::FLinearEase DelayParam;
    Audio::FLinearEase GainParam;

    int32 LifeToFadeOut;
};


struct FAudioTracingSpatialTapDelaySettings
{
    int32 NumChannel;
    int32 MaxNumTaps;
    float BlockSample;
    float SampleRate;
    float InterpolationTimeSecond;
    float MaxDelayLengthSecond;
    float HeadWidth;
    float SoundSpeed;
    float NearestDistanceThreshold;
    float NearestDistanceThresholdSquared;
    TArray<FVector> ChannelDirections = { FVector::LeftVector, FVector::RightVector };
    
    FAudioTracingSpatialTapDelaySettings()
        : NumChannel(0)
        , MaxNumTaps(0)
        , BlockSample(0.0f)
        , SampleRate(0.0f)
        , InterpolationTimeSecond(0.0f)
        , MaxDelayLengthSecond(0.0f)
        , HeadWidth(0.0f)
        , SoundSpeed(0.0f)
        , NearestDistanceThreshold(0.0f)
        , NearestDistanceThresholdSquared(0.0f)
    {}
};


struct FAudioTracingSpatialTapDelayData
{
    FVector ChannelLocation;
    TMap<uint32, FVector> TapsLocations;
    TMap<uint32, float> TapsVolumes;
    
    FAudioTracingSpatialTapDelayData()
        : ChannelLocation(FVector::ZeroVector)
    {}
};


struct FAudioTracingSpatialPrevTapDelayProxy
{
    int32 SourceId;
    TArray<FAudioTracingSpatialTapDelayData> PrevTapProxy;
    
    FAudioTracingSpatialPrevTapDelayProxy()
        : SourceId(-1)
    {}
};


struct FAudioTracingSpatialNewTapDelayProxy
{
    int32 SourceId;
    TArray<FAudioTracingSpatialTapDelayData> NewTapProxy;
    
    FAudioTracingSpatialNewTapDelayProxy()
        : SourceId(-1)
    {}
};


class FSimpleDelay
{
public:
    FSimpleDelay();
    
    void Init(const float InSampleRate, const float InMaxDelayLengthSecond);
    void Write(TArrayView<float> InBuffer);
    TArray<float> ReadFrom(float InDelayedTimeSecond, int32 ReadCount = 0);
    TArray<TArrayView<const float>> ReadRawFrom(float InDelayedTimeSecond, int32 ReadCount = 0);

private:
    Audio::FAlignedFloatBuffer DelayBuffer;
    float SampleRate;
    float MaxDelayLength;
    int32 DelayBufferSize;
    int32 WriteIndex;
};


class FAudioTracingSpatialTapDelay
{
public:
    FAudioTracingSpatialTapDelay();

    void Init(const FAudioTracingSpatialTapDelaySettings& Settings);

    // Update Taps Location to Mapped Locations
    // Used in AudioMixerRender Thread
    FAudioTracingSpatialPrevTapDelayProxy UpdateTaps(const FAudioTracingSpatialNewTapDelayProxy& InProxy);

    // Process Audio with Taps
    // Used in AudioMixerRender Thread
    void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData);

private:
    void ProcessAudioOptimized(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData);

    void ProcessAudioBypass(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData);

    int32 NumChannel;
    int32 MaxNumTaps;
    TArray<FVector> ChannelDirections;
    float BlockSample;
    float SampleRate;
    float MaxDelayLineLength;
    float InterpolationTime;
    float HeadWidth;
    float SoundSpeed;
    float NearestDistanceThresholdSquared;

    // ChannelTaps[ChannelIdx][TapDelayInfoIdx]
    TArray<TMap<uint32, FAudioTracingSpatialTapDelayInfo>> ChannelTaps;
    FCriticalSection TapsMutex;

    FSimpleDelay SimpleDelayLine;

    uint8 bIsInitialized: 1 = false;
    uint8 bIsAttack: 1 = true;
public:
    uint8 bIsBypass : 1 = false;
};

// Instead of Audio::ArrayInterpolate(...)
// resolve float error and formula error
namespace AudioTracing {
    void ArrayInterpolate(const float* InBuffer, float* OutBuffer, const int32 NumInSamples, const int32 NumOutSamples);
}