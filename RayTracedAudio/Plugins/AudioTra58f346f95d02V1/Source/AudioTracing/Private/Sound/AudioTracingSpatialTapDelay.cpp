// Copyright (c) 2025 Pinpoint. All Rights Reserved.


#include "Sound/AudioTracingSpatialTapDelay.h"

#include "Stats/Stats.h"
#include "Types/AudioRayTypes.h"
#include "Utils/ATUtils.h"
#include "DSP/FloatArrayMath.h"

DECLARE_CYCLE_STAT(TEXT("TapDelay Update"), STAT_TapDelayUpdate, STATGROUP_AudioTracing);
DECLARE_CYCLE_STAT(TEXT("TapDelay Processing"), STAT_TapDelayProcessing, STATGROUP_AudioTracing);

// FAudioTracingSpatialTapDelayInfo

FAudioTracingSpatialTapDelayInfo::FAudioTracingSpatialTapDelayInfo()
    : ChannelLocation(FVector::ZeroVector)
    , EmitterLocation(FVector::ZeroVector)
    , SoundSpeed(0)
    , SampleRate(0)
    , InterpolationTime(0)
    , LifeToFadeOut(0)
{}

void FAudioTracingSpatialTapDelayInfo::Init(const float InSoundSpeed, const float InBlockSample, const float InSampleRate, const float InInterpolationTime, bool InDontIterpolationInit)
{
    BlockSample = InBlockSample;
    SoundSpeed = InSoundSpeed;
    SampleRate = InSampleRate;
    InterpolationTime = InInterpolationTime;
    
    DelayParam.Init(SampleRate);
    GainParam.Init(SampleRate);
    
    LifeToFadeOut = 1;
    
    if (!InDontIterpolationInit)
    {
        GainParam.SetValue(1e-3f, InterpolationTime);
    }
}

FVector FAudioTracingSpatialTapDelayInfo::GetChannelLocation() const
{
    return ChannelLocation;
}

FVector FAudioTracingSpatialTapDelayInfo::GetEmitterLocation() const
{
    return EmitterLocation;
}

void FAudioTracingSpatialTapDelayInfo::SetLocationsAndVolume(const FVector& RelativeChannelLocation, const FVector& RelativeEmitterLocation, const float Volume)
{
    if (IsFadeOut())
    {
        return;
    }

    const float LifeCoef = (SampleRate / BlockSample) / 46.875f;

    LifeToFadeOut = FMath::Max(30 + FATUtils::RatioToDecibel(Volume), 0) * LifeCoef;
    ChannelLocation = RelativeChannelLocation;
    EmitterLocation = RelativeEmitterLocation;

    const FVector ChannelToEmitter = EmitterLocation - ChannelLocation;
    const float Distance = ChannelToEmitter.Length();
    const float Delay = Distance / SoundSpeed;
    const float Level = (FVector::DotProduct(RelativeChannelLocation.GetSafeNormal(), RelativeEmitterLocation.GetSafeNormal()) * 0.5f + 1.f) * Volume;

    DelayParam.SetValue(Delay * 1000.f, InterpolationTime);
    GainParam.SetValue(Level, InterpolationTime);
}


float FAudioTracingSpatialTapDelayInfo::GetGainValue(float NextTimeSec)
{
    if (NextTimeSec <= 0.f)
    {
        return GainParam.GetNextValue(0);
    }
    return GainParam.GetNextValue(NextTimeSec * SampleRate);
}

float FAudioTracingSpatialTapDelayInfo::GetDelayValue(float NextTimeSec)
{
    if (NextTimeSec <= 0.f)
    {
        return DelayParam.GetNextValue(0);
    }
    return DelayParam.GetNextValue(NextTimeSec * SampleRate);
}

void FAudioTracingSpatialTapDelayInfo::LifeDown()
{
    if (LifeToFadeOut >= 0)
    {
        --LifeToFadeOut;
        if ( LifeToFadeOut == 0 )
        {
            GainParam.SetValue(0.f, InterpolationTime);
        }
    }
}

bool FAudioTracingSpatialTapDelayInfo::IsFadeOut() const
{
    return LifeToFadeOut <= 0;
}

bool FAudioTracingSpatialTapDelayInfo::IsDone() const
{
    return GainParam.IsDone();
}

// FSimpleDelay

FSimpleDelay::FSimpleDelay()
    : SampleRate(0)
    , DelayBufferSize(0)
    , WriteIndex(0)
{
}

void FSimpleDelay::Init(const float InSampleRate, const float InMaxDelayLengthSecond)
{
    SampleRate = InSampleRate;
    MaxDelayLength = InMaxDelayLengthSecond;
    DelayBufferSize = static_cast<int32>(InMaxDelayLengthSecond * InSampleRate) + 1;
    DelayBuffer.AddZeroed(DelayBufferSize);
    WriteIndex = 0;
}

void FSimpleDelay::Write(TArrayView<float> InBuffer)
{
    TArrayView<float> TruncInBuffer = InBuffer;
    if (InBuffer.Num() > DelayBufferSize)
    {
        TruncInBuffer = InBuffer.Slice(InBuffer.Num() - DelayBufferSize, DelayBufferSize);
    }

    int32 WriteEndIndex = WriteIndex + TruncInBuffer.Num();
    if (WriteEndIndex >= DelayBufferSize)
    {
        WriteEndIndex -= DelayBufferSize;
    }

    if (WriteIndex < WriteEndIndex)
    {
        TArrayView<float> BufferView(&DelayBuffer[WriteIndex], TruncInBuffer.Num());
        Audio::ArraySetToConstantInplace(BufferView, 0.f);
        Audio::ArrayAddInPlace(TruncInBuffer, BufferView);
    }
    else
    {
        int32 TailBufferSize = DelayBufferSize - WriteIndex;
        TArrayView<float> BufferView1(&DelayBuffer[WriteIndex], TailBufferSize);
        TArrayView<float> InBuffer1(&TruncInBuffer[0], TailBufferSize);
        Audio::ArraySetToConstantInplace(BufferView1, 0.f);
        Audio::ArrayAddInPlace(InBuffer1, BufferView1);

        int32 HeadBufferSize = TruncInBuffer.Num() - TailBufferSize;
        TArrayView<float> BufferView2(&DelayBuffer[0], HeadBufferSize);
        TArrayView<float> InBuffer2(&TruncInBuffer[TailBufferSize], HeadBufferSize);
        Audio::ArraySetToConstantInplace(BufferView2, 0.f);
        Audio::ArrayAddInPlace(InBuffer2, BufferView2);
    }

    WriteIndex = WriteEndIndex;
}

TArray<float> FSimpleDelay::ReadFrom(float InDelayedTimeSecond, int32 ReadCount)
{
    if (InDelayedTimeSecond < 0.f)
        InDelayedTimeSecond = 0.f;
    if (InDelayedTimeSecond > MaxDelayLength)
        InDelayedTimeSecond = MaxDelayLength;

    int32 StartIndex = WriteIndex - InDelayedTimeSecond * SampleRate;
    if ( StartIndex < 0 )
    {
        StartIndex += DelayBufferSize;
    }

    int32 EndIndex = WriteIndex;
    if ( ReadCount > 0 )
    {
        EndIndex = StartIndex + ReadCount;
        if ( EndIndex >= DelayBufferSize )
        {
            EndIndex -= DelayBufferSize;
        }
    }

    TArray<float> Result;
    if ( StartIndex < EndIndex )
    {
        TArrayView<const float> BufferView(&DelayBuffer[StartIndex], EndIndex - StartIndex);
        Result.Append(BufferView);
    }
    else
    {
        TArrayView<const float> BufferView1(&DelayBuffer[StartIndex], DelayBufferSize - StartIndex);
        TArrayView<const float> BufferView2(&DelayBuffer[0], EndIndex);
        Result.Append(BufferView1);
        Result.Append(BufferView2);
    }
    
    return Result;
}

TArray<TArrayView<const float>> FSimpleDelay::ReadRawFrom(float InDelayedTimeSecond, int32 ReadCount)
{
    if ( InDelayedTimeSecond < 0.f )
        InDelayedTimeSecond = 0.f;
    if ( InDelayedTimeSecond > MaxDelayLength )
        InDelayedTimeSecond = MaxDelayLength;

    int32 StartIndex = WriteIndex - InDelayedTimeSecond * SampleRate;
    if (StartIndex < 0)
    {
        StartIndex += DelayBufferSize;
    }

    int32 EndIndex = WriteIndex;
    if (ReadCount > 0)
    {
        EndIndex = StartIndex + ReadCount;
        if (EndIndex >= DelayBufferSize)
        {
            EndIndex -= DelayBufferSize;
        }
    }

    TArray<TArrayView<const float>> Result;
    if (StartIndex < EndIndex)
    {
        TArrayView<const float> BufferView(&DelayBuffer[StartIndex], EndIndex - StartIndex);
        Result.Add(BufferView);
    }
    else
    {
        TArrayView<const float> BufferView1(&DelayBuffer[StartIndex], DelayBufferSize - StartIndex);
        TArrayView<const float> BufferView2(&DelayBuffer[0], EndIndex);
        if (BufferView1.Num() > 0)
        {
            Result.Add(BufferView1);
        }
        if (BufferView2.Num() > 0)
        {
            Result.Add(BufferView2);
        }
    }
    return Result;
}


// FAudioTracingSpatialTapDelay

FAudioTracingSpatialTapDelay::FAudioTracingSpatialTapDelay()
    : NumChannel(0)
    , MaxNumTaps(0)
    , SampleRate(0)
    , MaxDelayLineLength(0)
    , InterpolationTime(0)
    , HeadWidth(0)
    , SoundSpeed(0)
    , NearestDistanceThresholdSquared(0)
{
}

void FAudioTracingSpatialTapDelay::Init(const FAudioTracingSpatialTapDelaySettings& Settings)
{
    BlockSample = Settings.BlockSample;
    SampleRate = Settings.SampleRate;
    InterpolationTime = Settings.InterpolationTimeSecond;
    MaxDelayLineLength = Settings.MaxDelayLengthSecond;
    HeadWidth = Settings.HeadWidth;
    SoundSpeed = Settings.SoundSpeed;
    NearestDistanceThresholdSquared = Settings.NearestDistanceThreshold * Settings.NearestDistanceThreshold;

    SimpleDelayLine.Init(SampleRate, MaxDelayLineLength);

    NumChannel = Settings.NumChannel;
    MaxNumTaps = Settings.MaxNumTaps;
    ChannelTaps.AddDefaulted(NumChannel);
    ChannelDirections = { FVector::LeftVector, FVector::RightVector };

    bIsInitialized = true;
    bIsAttack = true;
}

FAudioTracingSpatialPrevTapDelayProxy FAudioTracingSpatialTapDelay::UpdateTaps(const FAudioTracingSpatialNewTapDelayProxy& InProxy)
{
    SCOPE_CYCLE_COUNTER(STAT_TapDelayUpdate);

    TArray<FAudioTracingSpatialTapDelayData> NewTaps = InProxy.NewTapProxy;
    TArray<FAudioTracingSpatialTapDelayData> CurrentTaps;

    for ( int32 i = 0; i < NumChannel; ++i )
    {
        const FAudioTracingSpatialTapDelayData& NewTapsByChannel = NewTaps[i];
        FAudioTracingSpatialTapDelayData CurrentTapsByChannel;

        TSet<uint32> UpdatedTapIndices;
        TArray<uint32> NewTapIndices;
        NewTapsByChannel.TapsLocations.GetKeys(NewTapIndices);

        for ( int32 NewTapIndicesPos = 0; NewTapIndicesPos < NewTapIndices.Num(); ++NewTapIndicesPos )
        {
            const uint32 NewTapIndex = NewTapIndices[NewTapIndicesPos];
            const FVector NewChannelLocation = NewTapsByChannel.ChannelLocation;
            const FVector NewTapLocation = NewTapsByChannel.TapsLocations[NewTapIndex];
            const float NewTapVolume = NewTapsByChannel.TapsVolumes[NewTapIndex];

            // if tap is exsist, update tap
            if ( ChannelTaps[i].Contains(NewTapIndex) )
            {
                ChannelTaps[i][NewTapIndex].SetLocationsAndVolume(NewChannelLocation, NewTapLocation, NewTapVolume);
            }
            // if tap is not, add tap
            else
            {
                FAudioTracingSpatialTapDelayInfo NewTap;
                NewTap.Init(SoundSpeed, BlockSample, SampleRate, InterpolationTime, bIsAttack);
                NewTap.SetLocationsAndVolume(NewChannelLocation, NewTapLocation, NewTapVolume);

                ChannelTaps[i].Add(NewTapIndex, NewTap);
            }

            UpdatedTapIndices.Add(NewTapIndex);
            CurrentTapsByChannel.TapsLocations.Add(NewTapIndex, NewTapLocation);
            CurrentTapsByChannel.TapsVolumes.Add(NewTapIndex, NewTapVolume);
        }
        CurrentTaps.Add(CurrentTapsByChannel);
    }

    FAudioTracingSpatialPrevTapDelayProxy PrevTapsProxy;
    PrevTapsProxy.SourceId = InProxy.SourceId;
    PrevTapsProxy.PrevTapProxy = MoveTemp(CurrentTaps);
    return PrevTapsProxy;
}

void FAudioTracingSpatialTapDelay::ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)
{
    SCOPE_CYCLE_COUNTER(STAT_TapDelayProcessing);

    if ( InputData.SpatializationParams == nullptr )
    {
        return;
    }
        
    if ( InputData.AudioBuffer == nullptr || InputData.AudioBuffer->IsEmpty() )
    {
        return;
    }

    if ( bIsAttack )
    {
        bIsAttack = false;
    }

    if (bIsBypass)
    {
        ProcessAudioBypass(InputData, OutputData);
    }
    else
    {
        ProcessAudioOptimized(InputData, OutputData);
    }
}

void FAudioTracingSpatialTapDelay::ProcessAudioOptimized(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)
{
    const int32 InputChannelNum = InputData.NumChannels;
    const int32 OutputChannelNum = NumChannel;
    const int32 InputBufferNum = InputData.AudioBuffer->Num();
    const int32 OutputBufferNum = OutputData.AudioBuffer.Num();
    const int32 OutputBufferNumByChannel = OutputBufferNum / OutputChannelNum;

    const FVector EmitterLocation = InputData.SpatializationParams->EmitterWorldPosition;
    const FVector ListenerLocation = InputData.SpatializationParams->ListenerPosition;
    
    // Write Input to DelayBuffer
    TArray<float> InputBuffer;
    InputBuffer.AddZeroed(InputBufferNum / InputChannelNum);
    for ( int32 InputBufferIndex = 0; InputBufferIndex < InputBufferNum / InputChannelNum; ++InputBufferIndex )
    {
        if ( InputBufferIndex < InputBufferNum )
        {
            float Input = 0.f;
            for ( int32 InputChannel = 0; InputChannel < InputChannelNum; ++InputChannel )
            {
                Input += (*InputData.AudioBuffer)[InputChannelNum * InputBufferIndex + InputChannel];
            }
            InputBuffer[InputBufferIndex] = Input / InputChannelNum;
        }
    }
    SimpleDelayLine.Write(InputBuffer);

    // check tap is empty
    bool bIsTapEmpty = true;
    for ( int32 i = 0; i < NumChannel; ++i )
    {
        if ( !ChannelTaps[i].IsEmpty() )
        {
            bIsTapEmpty = false;
        }
    }
    if ( bIsTapEmpty )
    {
        return;
    }

    // down tap's life
    // if tap's life is zero, tap will fade out
    for ( int32 i = 0; i < NumChannel; ++i )
    {
        for ( auto& [CurrentTapIndex, CurrentTap] : ChannelTaps[i] )
        {
            CurrentTap.LifeDown();
        }
    }


    TArray<TArray<float>> OutputBuffers;
    const float BlockInterval = static_cast<float>(OutputBufferNumByChannel) / SampleRate;
    const float InterpolationMargin = 4;

    TArray<TSet<uint32>> PendingDeleteTapIndices;
    PendingDeleteTapIndices.AddDefaulted(NumChannel);

    for ( int32 OutputChannelIdx = 0; OutputChannelIdx < NumChannel; ++OutputChannelIdx )
    {
        TArray<uint32> TapIndices;
        ChannelTaps[OutputChannelIdx].GetKeys(TapIndices);

        TArray<float> OutputBuffer;
        OutputBuffer.AddZeroed(OutputBufferNumByChannel);

        for ( const uint32 TapIndex : TapIndices )
        {
            FAudioTracingSpatialTapDelayInfo& ChannelTap = ChannelTaps[OutputChannelIdx][TapIndex];

            const float StartDelay = ChannelTap.GetDelayValue(1.f / SampleRate);
            const float EndDelay = ChannelTap.GetDelayValue(BlockInterval);
            const float StartGain = ChannelTap.GetGainValue(1.f / SampleRate);
            const float EndGain = ChannelTap.GetGainValue(BlockInterval);

            if ( ChannelTap.IsFadeOut() && ChannelTap.IsDone() )
            {
                PendingDeleteTapIndices[OutputChannelIdx].Add(TapIndex);
                continue;
            }

            // because delay write cursor is incremented, add BlockInterval
            // because interpolation, read margin more sample
            float ReadStartSecond = StartDelay / 1000.f + BlockInterval + InterpolationMargin / SampleRate;
            float ReadEndSecond = EndDelay / 1000.f - InterpolationMargin / SampleRate;

            /* Code which Not Interpolating in Time
            int32 ReadCount = OutputBufferNumByChannel;
            TArray<TArrayView<const float>> DelayedBuffer = SimpleDelayLine.ReadRawFrom(ReadStartSecond, ReadCount);

            int32 OutputWriteIndex = 0;
            const float GainSlope = (EndGain - StartGain) / OutputBufferNumByChannel;
            for (TArrayView<const float> DelayBuffer: DelayedBuffer)
            {
                TArrayView<float> SplitedOutputBuffer(&OutputBuffer[OutputWriteIndex], DelayBuffer.Num());
                Audio::ArrayMixIn(DelayBuffer, SplitedOutputBuffer, StartGain + GainSlope * OutputWriteIndex, StartGain + GainSlope * (OutputWriteIndex + DelayBuffer.Num()));
                OutputWriteIndex += DelayBuffer.Num();
            }
            */

            int32 ReadCount = FMath::RoundToInt32(FMath::Abs(ReadEndSecond - ReadStartSecond) * SampleRate);
            TArray<float> DelayedBuffer = SimpleDelayLine.ReadFrom(ReadStartSecond, ReadCount);

            if ( DelayedBuffer.Num() != OutputBufferNumByChannel + 2 * InterpolationMargin)
            {
                int32 NumDelayedBuffer = DelayedBuffer.Num();
                TArray<float> InterpBuffer;
                InterpBuffer.AddZeroed(OutputBufferNumByChannel + 2 * InterpolationMargin);

                // Border element calculation is strange...
                DelayedBuffer.AddZeroed();
                //Audio::ArrayInterpolate(DelayedBuffer.GetData(), InterpBuffer.GetData(), DelayedBuffer.Num() - 1, OutputBufferNumByChannel + 2 * InterpolationMargin);
                AudioTracing::ArrayInterpolate(DelayedBuffer.GetData(), InterpBuffer.GetData(), DelayedBuffer.Num() - 1, OutputBufferNumByChannel + 2 * InterpolationMargin);


                TArrayView<float> InterpBufferView = TArrayView<float>(&InterpBuffer[InterpolationMargin], OutputBufferNumByChannel);
                Audio::ArrayMixIn(InterpBufferView, OutputBuffer, StartGain, EndGain);
            } else
            {
                TArrayView<float> DelayedBufferView = TArrayView<float>(&DelayedBuffer[InterpolationMargin], OutputBufferNumByChannel);
                Audio::ArrayMixIn(DelayedBufferView, OutputBuffer, StartGain, EndGain);
            }
        }

        OutputBuffers.Add(OutputBuffer);
    }

    for ( int32 OutputBufferIndex = 0; OutputBufferIndex < OutputBufferNumByChannel; ++OutputBufferIndex )
    {
        for ( int32 OutputChannelIdx = 0; OutputChannelIdx < NumChannel; ++OutputChannelIdx )
        {
            OutputData.AudioBuffer[NumChannel * OutputBufferIndex + OutputChannelIdx] = OutputBuffers[OutputChannelIdx][OutputBufferIndex];
        }
    }


    for ( int32 OutputChannelIdx = 0; OutputChannelIdx < NumChannel; ++OutputChannelIdx ) 
    {
        for ( const uint32 PendingDeleteIndex : PendingDeleteTapIndices[OutputChannelIdx] )
        {
            ChannelTaps[OutputChannelIdx].Remove(PendingDeleteIndex);
        }
    }
}

void FAudioTracingSpatialTapDelay::ProcessAudioBypass(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)
{
    check(NumChannel == 2)
    if ( InputData.NumChannels == 1 )
    {
        Audio::MixMonoTo2ChannelsFast(*InputData.AudioBuffer, OutputData.AudioBuffer);
    } else if ( InputData.NumChannels == 2 )
    {
        Audio::ArrayMixIn(*InputData.AudioBuffer, OutputData.AudioBuffer);
    }
}


// AudioTracing::ArrayInterpolate

void AudioTracing::ArrayInterpolate(const float* InBuffer, float* OutBuffer, const int32 NumInSamples, const int32 NumOutSamples)
{
    if ( NumOutSamples <= 0 || NumInSamples <= 0 )
    {
        return;
    }

    const float SampleStride = (float)NumInSamples / (float)NumOutSamples;
    
    const int32 NumToSimd = NumOutSamples & 0xFFFFFFFC;
    const int32 NumNotToSimd = NumOutSamples & 0x00000003;

    if ( NumToSimd )
    {
        VectorRegister4Float Indices = VectorSet(
            0.f * SampleStride,
            1.f * SampleStride,
            2.f * SampleStride,
            3.f * SampleStride
        );

        for ( int32 OutputIndex = 0; OutputIndex < NumToSimd; OutputIndex += AUDIO_NUM_FLOATS_PER_VECTOR_REGISTER )
        {
            Indices = VectorSet(
                (OutputIndex + 0.f) * SampleStride,
                (OutputIndex + 1.f) * SampleStride,
                (OutputIndex + 2.f) * SampleStride,
                (OutputIndex + 3.f) * SampleStride
            );

            alignas(16) int32 LeftIndecesRaw[4];
            alignas(16) int32 RightIndecesRaw[4];

            VectorRegister4Float LeftIndeces = VectorFloor(Indices);
            VectorRegister4Float Fractions = VectorSubtract(Indices, LeftIndeces);
            VectorRegister4Float InvFractions = VectorSubtract(GlobalVectorConstants::FloatOne, Fractions);

            VectorRegister4Int LeftIndecesInt = VectorFloatToInt(LeftIndeces);

            // Lookup samples for interpolation
            VectorIntStoreAligned(LeftIndecesInt, LeftIndecesRaw);
            VectorIntStoreAligned(VectorIntAdd(LeftIndecesInt, GlobalVectorConstants::IntOne), RightIndecesRaw);

            VectorRegister4Float LowerSamples = VectorSet(
                InBuffer[LeftIndecesRaw[0]],
                InBuffer[LeftIndecesRaw[1]],
                InBuffer[LeftIndecesRaw[2]],
                InBuffer[LeftIndecesRaw[3]]
            );
            VectorRegister4Float UpperSamples = VectorSet(
                InBuffer[RightIndecesRaw[0]],
                InBuffer[RightIndecesRaw[1]],
                InBuffer[RightIndecesRaw[2]],
                InBuffer[RightIndecesRaw[3]]
            );

            VectorRegister4Float VOut = VectorMultiplyAdd(
                UpperSamples,
                Fractions,
                VectorMultiply(LowerSamples, InvFractions));
            VectorStore(VOut, &OutBuffer[OutputIndex]);
        }
    }

    if ( NumNotToSimd )
    {
        float SampleIndex = (float)(NumToSimd)*SampleStride;

        for ( int32 OutputIndex = NumToSimd; OutputIndex < NumOutSamples; OutputIndex++ )
        {
            const int32 LeftSample = FMath::FloorToInt32(SampleIndex);
            int32 RightSample = FMath::CeilToInt32(SampleIndex);

            const float Frac = SampleIndex - LeftSample;
            OutBuffer[OutputIndex] = (Frac * InBuffer[RightSample]) + ((1.f - Frac) * InBuffer[LeftSample]);

            SampleIndex += SampleStride;
        }
    }
}
