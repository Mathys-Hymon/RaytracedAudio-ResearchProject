// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"
#include "AudioRayTypes.generated.h"

UENUM()
enum class ETracedRayType : uint32
{
    ETT_DirectSound, // 직접음
    ETT_EarlyReflectionSound, // 반사음
    ETT_ReverbSound, // 잔향음
};

UENUM()
enum class EATDistanceAttenuationModel : uint32
{
    EDA_Linear,
    EDA_Logarithmic,
    EDA_Inverse,
};

struct FTracedAudioData 
{
    uint32 AudioID;
    float Volume;
    float Distance;
    int32 DirectionIdx;

    int32 ReflectionCount;
    FVector3f Padding;
};

struct FSynthesizeAudioData
{
    uint32 AudioID;
    float Volume;
    float Distance;
    uint32 DirectionIdx;

    int32 ReflectionCount;
    float RT60;
    ETracedRayType TraceType;
    float ReverbGain;
};

struct FActiveSoundProxy
{
    FVector3f Location = FVector3f(0.f, 0.f, 0.f);
    uint32 AudioID = 0;
};

// Cached Data while Ray Tracing
struct FPendingAudioTracingData
{
    TMap<uint32, FVector> SoundLocations;
    FVector ListenerLocation;
    FVector ListenerForward;
};

// Ray Traced Result
struct FAudioTraceResult
{
    TMap<uint32, TArray<FTracedAudioData>> TracedAudioData;
    FVector ListenerLocation = FVector::ZeroVector;
    FVector ListenerForward = FVector::ZeroVector;
    TMap<uint32, FVector> SoundLocations;
};

struct FGameThreadAudioTracePacket
{
    TSharedPtr<FAudioTraceResult, ESPMode::ThreadSafe> TraceResult;
    bool bDebugVirtualAudio = false;
};

// Effector Parameterized Data
struct FAudioRenderData
{
    uint32 AudioID;
    FVector SoundLocation;
    FVector ListenerLocation;
    FVector ListenerForward;
    TArray<FSynthesizeAudioData> RenderData;
};

struct FSourceAudioPacket
{
    uint32 SourceId;
    uint32 PlayOrder;
    FVector Location;
};

struct FDebugDrawData
{
    FVector ListenerLocation;
    TArray<FVector> RayDirections;

    struct FDebugInfo
    {
        uint32 AudioID;
        FVector SoundLocation;
        TArray<FSynthesizeAudioData> Parameters;
    };
    TArray<FDebugInfo> SoundDebugInfos;
};

#ifndef AUDIOTRACING_STAT_H
#define AUDIOTRACING_STAT_H
DECLARE_STATS_GROUP(TEXT("Audio Tracing"), STATGROUP_AudioTracing, STATCAT_Advanced);
#endif