#include "NanoMsgRunnable.h"

#include <nanomsg/nn.hpp>

FNanoMsgRunnable::FNanoMsgRunnable(nn::socket *InSocket, const float InWaitTime, const TCHAR *InThreadName)
	: Socket(InSocket), Stopping(false), Thread(nullptr), ThreadName(InThreadName), WaitTime(InWaitTime)
{
	check(Socket != nullptr);
}

FNanoMsgRunnable::~FNanoMsgRunnable()
{
	if (Thread != nullptr)
	{
		Thread->Kill(true);
		delete Thread;
	}
}

uint32 FNanoMsgRunnable::Run()
{
	RecvBuffer = new char[MaxReadBufferSize];
	while (!Stopping)
	{
		Update(WaitTime);
	}
	delete[] RecvBuffer;
	RecvBuffer = NULL;
	return 0;
}

void FNanoMsgRunnable::Update(const float SocketWaitTime)
{
	int rc = Socket->recv(RecvBuffer, MaxReadBufferSize, 0);
	try
	{
		Socket->recv(RecvBuffer, MaxReadBufferSize, 0);
		// UE_LOG(LogTemp, Log, TEXT("socket in FNanoMsgRunnable recv success: %s"), UTF8_TO_TCHAR(RecvBuffer));
		FString msg = FString::Printf(TEXT("socket in FNanoMsgRunnable recv success: = %s"), UTF8_TO_TCHAR(RecvBuffer));
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);
	}
	catch (nn::exception e)
	{
		UE_LOG(LogTemp, Log, TEXT("socket in FNanoMsgRunnable recv failed: %s"), UTF8_TO_TCHAR(e.what()));
	}
	FPlatformProcess::Sleep(SocketWaitTime);
}