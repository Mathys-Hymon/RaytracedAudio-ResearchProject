// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "ATUtils.h"

#include "AudioTracingLog.h"
#include "Types/AudioRayTypes.h"
#include "Settings/AudioTracingSettings.h"

TArray<FVector> FATUtils::MakeUniformDirections(int32 InCount)
{
    if (InCount <= 0)
    {
        return TArray<FVector>();
    }

    TArray<FVector> Directions;
    Directions.Reserve(InCount);
    
    const float GoldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2.0f;
    const float AngleIncrement = 2.0f * UE_PI * GoldenRatio;

    for ( int32 i = 0; i < InCount; ++i )
    {
        const float T = static_cast<float>(i) / static_cast<float>(InCount);
        const float Inclination = FMath::Acos(1.0f - 2.0f * T); // θ
        const float Azimuth = AngleIncrement * i;                    // φ

        // Spherical to Cartesian
        const float X = FMath::Sin(Inclination) * FMath::Cos(Azimuth);
        const float Y = FMath::Sin(Inclination) * FMath::Sin(Azimuth);
        const float Z = FMath::Cos(Inclination);

        FVector Direction(X, Y, Z);
        Directions.Emplace(Direction.GetSafeNormal());
    }

    return Directions;
}

TArray<float> FATUtils::WeightedHistogram(
    const TArray<float>& InDataX,
    const TArray<float>& InDataWeight,
    float InBin,
    float InRangeStart,
    float InRangeEnd
)
{
    if ( InDataX.Num() != InDataWeight.Num() )
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATUtils::WeightedHistogram(...): Size of DataX and DataWeight are not equal."));
        return TArray<float>();
    }

    TArray<float> Result;
    Result.AddZeroed((InRangeEnd - InRangeStart) / InBin);

    for ( int32 i = 0; i < InDataX.Num(); ++i )
    {
        int32 Idx = (InDataX[i] - InRangeStart) / InBin;
        if (Idx < 0 || Result.Num() < Idx) 
        {
            UE_LOG(LogAudioTracing, Error, TEXT("FATUtils::WeightedHistogram(...): Index is Out of Range. InDataX: %f, Range: [%f, %f]"), InDataX[i], InRangeStart, InRangeEnd);
            return TArray<float>();
        }
        Result[Idx] += InDataWeight[i];
    } 

    return Result;
}

TArray<float> FATUtils::KernelDistEstimate(
    const TArray<float>& InDataX, 
    const TArray<float>& InDataWeight, 
    const int32 InKernelSize,
    const float InBin, 
    const float InRangeStart, 
    const float InRangeEnd
)
{
    bool bIsIgnoreWeight = false;
    if (InDataX.Num() != InDataWeight.Num())
    {
        UE_LOG(LogAudioTracing, Warning, TEXT("FATUtils::KernelDistEstimate(...): Size of DataX and DataWeight are not equal. Weight will be ignored."));
        bIsIgnoreWeight = true;
    }

    TArray<float> Kernel = GaussianKernel1D(InKernelSize);
    TArray<float> Result;
    Result.AddZeroed((InRangeEnd - InRangeStart) / InBin);
    for (int32 i = 0; i < InDataX.Num(); ++i) 
    {
        int32 OffsetIdx = (InDataX[i] - InRangeStart) / InBin;
        for (int32 k = 0; k < InKernelSize; ++k) 
        {
            int32 Idx = OffsetIdx + (k - InKernelSize / 2);
            if ( Idx < 0 || Result.Num() <= Idx )
            {
                continue;
            }
            Result[Idx] += Kernel[k] * (bIsIgnoreWeight ? 1.f : InDataWeight[i]);
        }
    }
    return Result;
}

TArray<int32> FATUtils::FindPeakIndices(const TArray<float>& InTarget, const float InThreshold)
{
    if ( InTarget.Num() == 0 )
    {
        return TArray<int32>();
    }
    if ( InTarget.Num() == 1 )
    {
        return TArray<int32>({ 0 });
    }
    if ( InTarget.Num() == 2 )
    {
        return TArray<int32>({ (InTarget[0] > InTarget[1] ? 0 : 1) });
    }
    
    TArray<int32> Result;
    if ( InTarget[0] > InTarget[1] && InTarget[0] > InThreshold )
    {
        Result.Add(0);
    }
    
    for ( int32 i = 2; i < InTarget.Num(); ++i )
    {
        if ( InTarget[i - 2] < InTarget[i - 1] && InTarget[i] < InTarget[i - 1] )
        {
            if ( InTarget[i - 1] > InThreshold )
            {
                Result.Add(i - 1);
            }
        }
    }
    
    int32 LastIdx = InTarget.Num() - 1;
    if ( InTarget[LastIdx] > InTarget[LastIdx - 1] && InTarget[LastIdx] > InThreshold )
    {
        Result.Add(LastIdx);
    }
    
    return Result;
}

void FATUtils::LinearRegression(
    const TArray<float>& InDataX, 
    const TArray<float>& InDataY,
    float& OutSlope,
    float& OutIntercept
)
{
    if (InDataX.IsEmpty())
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATUtils::LinearRegression(...): DataX is Empty."));
        return;
    }
    if (InDataX.Num() != InDataY.Num()) 
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATUtils::LinearRegression(...): Size of DataX and DataY are not equal."));
        return;
    }

    int32 N = InDataX.Num();
    float SumX = 0.f;
    float SumY = 0.f;
    float SumXY = 0.f;
    float SumXx = 0.f;
    for (int32 i = 0; i < N; ++i)
    {
        SumX += InDataX[i];
        SumY += InDataY[i];
        SumXY += InDataX[i] * InDataY[i];
        SumXx += InDataX[i] * InDataX[i];
    }

    float MeanX = SumX / N;
    float MeanY = SumY / N;
    float Numerator = SumXY - N * MeanX * MeanY;
    float Denominator = SumXx - N * MeanX * MeanX;

    if (Denominator < UE_SMALL_NUMBER) 
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATUtils::LinearRegression(...): Divide by zero."));
        return;
    }

    OutSlope = Numerator / Denominator;
    OutIntercept = MeanY - OutSlope * MeanX;
}

TArray<float> FATUtils::GaussianKernel1D(uint32 InKernelSize, float InRange)
{
    if (InKernelSize == 0) 
    {
        return TArray<float>();
    }
    if (InKernelSize == 1)
    {
        return TArray<float>({1});
    }

    TArray<float> Result;
    float Interval = (2 * InRange) / (InKernelSize - 1);
    float Sum = 0.f;
    for (uint32 i = 0; i < InKernelSize; ++i) 
    {
        float X = -InRange + i * Interval;
        float Y = 1 / FMath::Sqrt(2 * PI) * FMath::Exp(-X * X / 2.f);
        Result.Add(Y);
        Sum += Y;
    }

    for (uint32 i = 0; i < InKernelSize; ++i)
    {
        Result[i] /= Sum;
    }
    return Result;
}

TArray<float> FATUtils::VonMisesKernel(const TArray<float>& InCosVals, const float InKappa)
{
    double I0 = PseudoBesselFunction(InKappa);

    float Sum = 0.f;
    TArray<float> Result;
    for (const float CosVal: InCosVals)
    {
        float Numerator = FMath::Exp(InKappa * CosVal);
        float Denominator = 2 * PI * I0;
        float Val = Numerator / Denominator;
        Sum += Val;
        Result.Add(Val);
    }

    for (int32 i = 0; i < Result.Num(); ++i) 
    {
        Result[i] /= Sum;
    }

    return Result;
}

bool FATUtils::IsTraceDataValid(const FTracedAudioData& TracedData)
{
    const UAudioTracingSettings* AudioSettings = GetDefault<UAudioTracingSettings>();

    bool bIsValidDistance = (0.f <= TracedData.Distance);
    bool bIsValidDirectionIdx = (TracedData.DirectionIdx == INDEX_NONE || (0 <= TracedData.DirectionIdx && TracedData.DirectionIdx < AudioSettings->RayCount));
    bool bIsValidVolume = (0.f <= TracedData.Volume && TracedData.Volume <= 2.f);
    bool bIsValidReflectionCount = (0 <= TracedData.ReflectionCount && TracedData.ReflectionCount <= AudioSettings->MaxReflection);
    return bIsValidDistance && bIsValidDirectionIdx && bIsValidVolume && bIsValidReflectionCount;
}

double FATUtils::PseudoBesselFunction(double Kappa, int32 Terms)
{
    double Sum = 1.0;
    double Factorial = 1.0;
    double K2 = Kappa * Kappa / 4.0;
    double Power = 1.0;

    for ( int32 i = 1; i <= Terms; ++i )
    {
        Factorial *= i;
        Power *= K2;
        Sum += Power / (Factorial * Factorial);
    }
    return Sum;
}

void FATUtils::FOnlineLinearRegression::Add(float X, float Y)
{
    SumX += X;
    SumY += Y;
    SumXX += X * X;
    SumXY += X * Y;
    ++N;
}

void FATUtils::FOnlineLinearRegression::Get(float& OutSlope, float& OutIntercept) const
{
    float MeanX = SumX / N;
    float MeanY = SumY / N;
    float Numerator = SumXY - N * MeanX * MeanY;
    float Denominator = SumXX - N * MeanX * MeanX;

    if ( Denominator < UE_SMALL_NUMBER )
    {
        UE_LOG(LogAudioTracing, Error, TEXT("FATUtils::FOnlineLinearRegression::Get(...): Divide by zero."));
        return;
    }

    OutSlope = Numerator / Denominator;
    OutIntercept = MeanY - OutSlope * MeanX;
}