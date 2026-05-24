// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FTracedAudioData;

class AUDIOTRACING_API FATUtils
{
public:
    static TArray<FVector> MakeUniformDirections(int32 InCount);

    static TArray<float> WeightedHistogram(
        const TArray<float>& InDataX, 
        const TArray<float>& InDataWeight,
        float InBin, 
        float InRangeStart = 0.f, 
        float InRangeEnd = 1.f
    );
    
    static TArray<float> KernelDistEstimate(
        const TArray<float>& InDataX, 
        const TArray<float>& InDataWeight, 
        const int32 InKernelSize = 15, 
        const float InBin = 0.0005f,
        const float InRangeStart = 0.f,
        const float InRangeEnd = 1.f
    );

    static TArray<int32> FindPeakIndices(const TArray<float>& InTarget, const float InThreshold = UE_KINDA_SMALL_NUMBER);

    static void LinearRegression(
        const TArray<float>& InDataX,
        const TArray<float>& InDataY,
        float& OutSlope,
        float& OutIntercept
    );

    static TArray<float> GaussianKernel1D(uint32 InKernelSize, float InRange = 3.0f);

    static TArray<float> VonMisesKernel(const TArray<float>& InCosVals, const float InKappa = 10.0);

    struct FOnlineLinearRegression
    {
        float SumX = 0.f;
        float SumY = 0.f;
        float SumXX = 0.f;
        float SumXY = 0.f;
        int32 N = 0;

        void Add(float X, float Y);
        void Get(float& OutSlope, float& OutIntercept) const;
    };

    inline static float RatioToDecibel(float Ratio) { return 10.f * FMath::LogX(10.f, Ratio); }
    inline static float DecibelToRatio(float Decibel) { return FMath::Pow(10.f, Decibel / 10.f); }

    static bool IsTraceDataValid(const FTracedAudioData& TracedData);

private:
    static double PseudoBesselFunction(double Kappa, int32 Terms = 20);
};