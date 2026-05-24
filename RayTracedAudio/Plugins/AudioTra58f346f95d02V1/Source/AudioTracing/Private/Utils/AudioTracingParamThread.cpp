// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#include "AudioTracingParamThread.h"

#include "AudioTracingLog.h"


FAudioTracingParamThread::FAudioTracingParamThread(TQueue<TSharedPtr<FAudioTraceParameterizePacket>, EQueueMode::Spsc>* InPacketQueue,
                                                   TQueue<FSingleSourceParameterizationResult, EQueueMode::Mpsc>* InResultQueue, FEvent* InWakeupEvent)
	: bIsRunning(false)
	, InputPacketQueue(InPacketQueue)
	, ResultQueue(InResultQueue)
	, WakeupEvent(InWakeupEvent)
{
}

FAudioTracingParamThread::~FAudioTracingParamThread()
{
	bIsRunning = false;
}

bool FAudioTracingParamThread::Init()
{
	bIsRunning = true;
	return true;
}

uint32 FAudioTracingParamThread::Run()
{
	while (bIsRunning)
	{
		WakeupEvent->Wait();

		if (!bIsRunning)
		{
			break;
		}
		check(InputPacketQueue);
		
		TSharedPtr<FAudioTraceParameterizePacket> LatestPacket;
		TSharedPtr<FAudioTraceParameterizePacket> TempPacket;
		bool bHasNewPacket = false;
		while (InputPacketQueue->Dequeue(TempPacket))
		{
			LatestPacket = TempPacket;
			bHasNewPacket = true;
		}

		if (bHasNewPacket)
		{
			ProcessPacket(LatestPacket);
		}
		
	}

	return 0; 
}

void FAudioTracingParamThread::Exit()
{
	UE_LOG(LogAudioTracing, Log, TEXT("Exit AudioTracingParamThread"));
}

void FAudioTracingParamThread::Stop()
{
	bIsRunning = false;

	if (WakeupEvent)
	{
		WakeupEvent->Trigger();
	}
	
}

void FAudioTracingParamThread::ProcessPacket(const TSharedPtr<FAudioTraceParameterizePacket>& Packet)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(AudioTracing.ProcessPacket);
	check(ResultQueue);
        

	ParallelFor(Packet->SoundProcessData.Num(), [&](int32 Index)
	{
		FSingleSourceParameterizationResult SingleResult = CalculateSingleSourceParameterization(Packet, Index);
		
		ResultQueue->Enqueue(SingleResult);
	});
}

FSingleSourceParameterizationResult FAudioTracingParamThread::CalculateSingleSourceParameterization(
	const TSharedPtr<FAudioTraceParameterizePacket>& Packet, int32 Index)
{
	const FSingleSourceParameterizeData& SoundData = Packet->SoundProcessData[Index];
	const uint32 AudioId = SoundData.PlayOrder;
	TArray<FTracedAudioData> TraceAudioDataArr = SoundData.TracedAudioData;
	const FVector SoundLocation = SoundData.SoundLocation;
	TSharedPtr<const FSoundAttenuationSettings> AttenuationSetting = SoundData.AttenuationSetting;
	const FVector ListenerLocation = Packet->ListenerLocation;
	const FVector ListenerForward = Packet->ListenerForward;
            
	if (AttenuationSetting.IsValid())
	{
		FAudioTracingAlgorithm::DistanceAttenuateRayTracedData(TraceAudioDataArr, FTransform(SoundLocation), ListenerLocation, AttenuationSetting);
	}

	TArray<FSynthesizeAudioData> Parameters = FAudioTracingAlgorithm::Parameterize(TraceAudioDataArr, Packet->AlgorithmSettings);

	FSingleSourceParameterizationResult SingleResult;
	SingleResult.AudioID = AudioId;
	SingleResult.RenderData.AudioID = AudioId;
	SingleResult.RenderData.SoundLocation = SoundLocation;
	SingleResult.RenderData.ListenerForward = ListenerForward;
	SingleResult.RenderData.ListenerLocation = ListenerLocation;
            
	if (Packet->bDebugVirtualAudio)
	{
		SingleResult.bHasDebugData = true;
		SingleResult.SoundLocation = SoundLocation;
		SingleResult.DebugParameters = Parameters; 
	}
            
	SingleResult.RenderData.RenderData = MoveTemp(Parameters); 

	return SingleResult;
}
