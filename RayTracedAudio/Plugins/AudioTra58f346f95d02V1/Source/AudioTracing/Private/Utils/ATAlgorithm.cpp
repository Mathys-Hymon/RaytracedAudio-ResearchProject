// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "ATAlgorithm.h"

#include "AudioTracingLog.h"
#include "Settings/AudioTracingSettings.h"
#include "Utils/ATUtils.h"

DECLARE_CYCLE_STAT(TEXT("Parameterizing"), STAT_ATParameterizing, STATGROUP_AudioTracing);

TArray<FSynthesizeAudioData> FAudioTracingAlgorithm::Parameterize(const TArray<FTracedAudioData>& TracedDataArray, const FATAlgorithmSettings& InSettings)
{
    static TArray<FVector> RayDirections;
    SCOPE_CYCLE_COUNTER(STAT_ATParameterizing);

    if (RayDirections.Num() != InSettings.RayCount)
    {
        RayDirections = FATUtils::MakeUniformDirections(InSettings.RayCount);
    }

    const float VolumePerRay = FMath::Sqrt(1.f / InSettings.RayCount);
    const float TimeBin = 1.f / InSettings.RayCount;
    const float DotProductThreshold = FMath::Cos(FMath::DegreesToRadians(15.f));

    TArray<FTracedAudioData> AvailableTracedDataArray = TracedDataArray.FilterByPredicate([](const FTracedAudioData& AudioData)
    {
        return FATUtils::IsTraceDataValid(AudioData);
    });

    if (AvailableTracedDataArray.IsEmpty())
    {
        return TArray<FSynthesizeAudioData>();
    }

    Algo::Sort(AvailableTracedDataArray, [](const FTracedAudioData& LHS, const FTracedAudioData& RHS)
    {
        return LHS.Distance < RHS.Distance;
    });

    const int32 AudioID = AvailableTracedDataArray[0].AudioID;
    TArray<FClusterInfo> Clusters;
    FTracedAudioData DirectSound = {};

    // PredictModel: Volume = Coef / Delay, Coef = DirectRayVolume * DirectRayDelay
    // Model Predict Histogram Weighted by Volume, bin = 1.f / RayCount
    // Model follows Calculating Reflection Volume Formular
    const float FirstRayVolume = 1.f;   // assumed
    const float FirstRayDelay = AvailableTracedDataArray[0].Distance / InSettings.SoundSpeed;
    float ModelCoef = FirstRayVolume * FirstRayDelay;   // by Model

    // EarlyReflection / Reverb Threshold is assumed by ratio with Volume of Direct Sound (1.f)
    const float EREndVolumedB = -20.f;
    const float EREndThreshold = FATUtils::DecibelToRatio(EREndVolumedB);
    const float EREnd = ModelCoef / EREndThreshold; // by Model

    const float ReverbStartVolumedB = -5.f;
    const float ReverbStartThreshold = FATUtils::DecibelToRatio(ReverbStartVolumedB);
    const float ReverbStart = ModelCoef / ReverbStartThreshold; // by Model

    const float ReverbEndVolumedB = -25.f;
    const float ReverbEndThreshold = FATUtils::DecibelToRatio(ReverbEndVolumedB);
    const float ReverbEnd = FMath::Min(ModelCoef / ReverbEndThreshold, InSettings.MaxTraceTime); // by Model

    TArray<float> ReverbHist;
    ReverbHist.AddZeroed(InSettings.MaxTraceTime / TimeBin + 1);

    for (const FTracedAudioData& Data: AvailableTracedDataArray)
    {
        if (Data.ReflectionCount == 0) 
        {
            DirectSound = Data;
            const float DataDelay = Data.Distance / InSettings.SoundSpeed;
            const int32 ReverbHistIndex = DataDelay / TimeBin;
            ReverbHist[ReverbHistIndex] += Data.Volume;
            continue;
        }

        const float DataDelay = Data.Distance / InSettings.SoundSpeed;
        if (DataDelay > ReverbStart)
        {
            const int32 ReverbHistIndex = DataDelay / TimeBin;
            ReverbHist[ReverbHistIndex] += Data.Volume * VolumePerRay;
        }

        if ( DataDelay <= EREnd )
        {
            const FVector DataDir = RayDirections[Data.DirectionIdx];
            bool IsClustered = false;
            int32 NearestClusterIndex = -1;

            for (int32 ClusterIndex = 0; ClusterIndex < Clusters.Num(); ++ClusterIndex)
            {
                FClusterInfo& ClusterInfo = Clusters[ClusterIndex];
                const FVector ClusterDir = RayDirections[ClusterInfo.FirstRayDirectionIdx];
                const float ClusterStart = ClusterInfo.FirstRayDelay;

                if (FVector::DotProduct(DataDir, ClusterDir) > DotProductThreshold)
                {
                    NearestClusterIndex = ClusterIndex;
                    IsClustered = true;
                }
            }

            if (!IsClustered)
            {
                FClusterInfo NewCluster;
                NewCluster.FirstRayDelay = DataDelay;
                NewCluster.FirstRayDirectionIdx = Data.DirectionIdx;
                Clusters.Add(NewCluster);
            }
            else
            {
                Clusters[NearestClusterIndex].EarlyReflectionVolumes.Add(Data.Volume * VolumePerRay);
                Clusters[NearestClusterIndex].EarlyReflectionDelays.Add(DataDelay);
            }
        }
    }


    // Processing Early Reflections
    TArray<FEarlyReflectionInfo> EarlyReflectionInfos;
    {
        const float EarlyReflectionVolumeThreshold = FATUtils::DecibelToRatio(-20.f);
        for ( FClusterInfo& ClusterInfo : Clusters )
        {
            TArray<float> VolumeHist;
            VolumeHist.AddZeroed((ReverbStart - FirstRayDelay) / TimeBin + 1);

            for (int32 i = 0; i < ClusterInfo.EarlyReflectionDelays.Num(); ++i)
            {
                int32 HistIndex = (ClusterInfo.EarlyReflectionDelays[i] - FirstRayDelay) / TimeBin;
                if (HistIndex < 0 || VolumeHist.Num() <= HistIndex)
                    continue;
                VolumeHist[HistIndex] += ClusterInfo.EarlyReflectionVolumes[i];
            }
        
            for (int32 i = 0; i < VolumeHist.Num(); ++i)
            {
                if (VolumeHist[i] > EarlyReflectionVolumeThreshold)
                {
                    FEarlyReflectionInfo EarlyReflectionInfo;
                    EarlyReflectionInfo.Delay = FirstRayDelay + i * TimeBin;
                    EarlyReflectionInfo.Volume = VolumeHist[i];
                    EarlyReflectionInfo.DirIdx = ClusterInfo.FirstRayDirectionIdx;
                    EarlyReflectionInfos.Add(EarlyReflectionInfo);
                }
            }
        }

        Algo::Sort(EarlyReflectionInfos, [](const FEarlyReflectionInfo& LHS, const FEarlyReflectionInfo& RHS)
        {
            return LHS.Volume > RHS.Volume;
        });

        const int32 MaxNumEarlyReflection = InSettings.MaxEarlyReflectionCount;
        if (EarlyReflectionInfos.Num() > MaxNumEarlyReflection )
        {
            EarlyReflectionInfos.RemoveAt(MaxNumEarlyReflection, EarlyReflectionInfos.Num() - MaxNumEarlyReflection);
        }
    
        const float TargetEarlyReflectionVolume = 1.f;
        float EarlyReflectionVolumeSum = 0.f;
        for (const FEarlyReflectionInfo& EarlyReflectionInfo :EarlyReflectionInfos)
        {
            EarlyReflectionVolumeSum += EarlyReflectionInfo.Volume;
        }
        
        if (EarlyReflectionVolumeSum >= TargetEarlyReflectionVolume )
        {
            for ( FEarlyReflectionInfo& EarlyReflectionInfo : EarlyReflectionInfos )
            {
                EarlyReflectionInfo.Volume /= EarlyReflectionVolumeSum;
                EarlyReflectionInfo.Volume *= TargetEarlyReflectionVolume;
            }
        }
    }

    // Processing Reverb
    float RT60 = 0.f;
    float ReverbGain = -60.f;
    {
        TArray<float> EDC;
        TArray<float> RegressionX;
        TArray<float> RegressionY;
        EDC.AddZeroed(ReverbHist.Num());
        EDC[ReverbHist.Num() - 1] = ReverbHist[ReverbHist.Num() - 1];
        for (int32 i = ReverbHist.Num() - 2; i >= 0; --i)
        {
            EDC[i] = EDC[i + 1] + ReverbHist[i];
        }

        int32 StartIndex = ReverbStart / TimeBin;
        int32 EndIndex = ReverbEnd / TimeBin;

        for (int32 EDCIndex = StartIndex; EDCIndex < EndIndex; ++EDCIndex)
        {
            if ( UE_SMALL_NUMBER < EDC[EDCIndex] && EDC[EDCIndex] < EDC[0] - UE_SMALL_NUMBER)
            {
                RegressionX.Add(EDCIndex* TimeBin);
                RegressionY.Add(FATUtils::RatioToDecibel(EDC[EDCIndex] / EDC[0]));
            }
        }

        if (RegressionX.Num() >= 20)
        {
            float Slope, Intercept;
            FATUtils::LinearRegression(RegressionX, RegressionY, Slope, Intercept);
            RT60 = -60 / Slope;
            ReverbGain = Intercept + Slope * ReverbStart;
        }
    }

    TArray<FSynthesizeAudioData> Result;

    // Direct Sound
    if (DirectSound.Volume > 0.f)
    {
        FSynthesizeAudioData AudioData;
        AudioData.AudioID = AudioID;
        AudioData.DirectionIdx = DirectSound.DirectionIdx;
        AudioData.Distance = DirectSound.Distance;
        AudioData.Volume = DirectSound.Volume;
        AudioData.ReflectionCount = DirectSound.ReflectionCount;
        AudioData.TraceType = ETracedRayType::ETT_DirectSound;
        AudioData.RT60 = RT60;
        AudioData.ReverbGain = ReverbGain;
        Result.Add(AudioData);
    }

    // Indirect Sound (Early Reflection)
    for (const FEarlyReflectionInfo& EarlyReflectionInfo: EarlyReflectionInfos)
    {
        FSynthesizeAudioData AudioData;
        AudioData.AudioID = AudioID;
        AudioData.DirectionIdx = EarlyReflectionInfo.DirIdx;
        AudioData.Distance = EarlyReflectionInfo.Delay * InSettings.SoundSpeed;
        AudioData.Volume = EarlyReflectionInfo.Volume;
        AudioData.ReflectionCount = 1;
        AudioData.TraceType = ETracedRayType::ETT_EarlyReflectionSound;
        AudioData.RT60 = RT60;
        AudioData.ReverbGain = ReverbGain;
        Result.Add(AudioData);
    }

    return Result;
}

void FAudioTracingAlgorithm::DistanceAttenuateRayTracedData(TArray<FTracedAudioData>& TargetData, const FTransform& SoundTransform, const FVector& ListenerLocation, TSharedPtr<const FSoundAttenuationSettings> AttenuationSetting)
{
    const float DirectSoundDist = FVector::Distance(SoundTransform.GetLocation(), ListenerLocation);

    float RevisedVolume = 1.f;
    if ( AttenuationSetting.IsValid() && AttenuationSetting->bAttenuate )
    {
        const float DirectSoundVolume = DefaultDistanceAttenuate(DirectSoundDist / 100.f);
        RevisedVolume = 1.f / DirectSoundVolume;
    }

    for ( FTracedAudioData& AudioData : TargetData )
    {
        AudioData.Volume *= RevisedVolume * DefaultDistanceAttenuate(AudioData.Distance / 100.f);
    }
}

float FAudioTracingAlgorithm::DefaultDistanceAttenuate(float Distance)
{
    const float IntersectionX = 50.435253f;
    if ( Distance < 1.f )
    {
        return 1.f;
    }
    // y = -0.25 ln(x) + 1
    else if ( Distance < IntersectionX )
    {
        return -0.25f * FMath::Loge(Distance) + 1.f;
    }
    // y = 1 / x
    else
    {
        return 1.f / Distance;
    }
}