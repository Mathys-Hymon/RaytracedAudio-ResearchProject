// Copyright (c) 2025 Pinpoint. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ATAlgorithm.h"
#include "Containers/Queue.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "Types/AudioRayTypes.h"

class FAudioTracingParamThread : public FRunnable
{
	
public:
	FAudioTracingParamThread(
		TQueue<TSharedPtr<FAudioTraceParameterizePacket>, EQueueMode::Spsc>* InPacketQueue,
		TQueue<FSingleSourceParameterizationResult, EQueueMode::Mpsc>* InResultQueue,
		FEvent* InWakeupEvent
	);
	virtual ~FAudioTracingParamThread();
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	
	static FSingleSourceParameterizationResult CalculateSingleSourceParameterization(const TSharedPtr<FAudioTraceParameterizePacket>& Packet, int32 Index);
	
private:
	FThreadSafeBool bIsRunning;

	TQueue<TSharedPtr<FAudioTraceParameterizePacket>, EQueueMode::Spsc>* InputPacketQueue;
	TQueue<FSingleSourceParameterizationResult, EQueueMode::Mpsc>* ResultQueue;
	FEvent* WakeupEvent;

	void ProcessPacket(const TSharedPtr<FAudioTraceParameterizePacket>& Packet);
};
