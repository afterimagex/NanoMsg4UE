#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Misc/SingleThreadRunnable.h"

#include <nanomsg/nn.hpp>

/**
 * Asynchronously receives data from an NanoMsg socket.
 */
class FNanoMsgRunnable : public FRunnable, private FSingleThreadRunnable
{
public:
	FNanoMsgRunnable(nn::socket *InSocket, const float InWaitTime, const TCHAR *InThreadName);

	/** Virtual destructor. */
	virtual ~FNanoMsgRunnable();

public:
	/** Set the maximum size allocated to read off of the socket. */
	void SetMaxReadBufferSize(uint32 InMaxReadBufferSize)
	{
		MaxReadBufferSize = InMaxReadBufferSize;
	}

	/** Start the receiver thread. */
	void Start()
	{
		Thread = FRunnableThread::Create(this, *ThreadName, 128 * 1024, TPri_AboveNormal, FPlatformAffinity::GetPoolThreadMask());
	}

	/**
	 * Returns a delegate that is executed when data has been received.
	 *
	 * This delegate must be bound before the receiver thread is started with
	 * the Start() method. It cannot be unbound while the thread is running.
	 *
	 * @return The delegate.
	 */
	// FOnSocketDataReceived& OnDataReceived()
	// {
	// 	check(Thread == nullptr);
	// 	return DataReceivedDelegate;
	// }

public:
	//~ FRunnable interface
	virtual FSingleThreadRunnable *GetSingleThreadInterface() override
	{
		return this;
	}

	virtual bool Init() override
	{
		return true;
	}

	virtual uint32 Run() override;

	virtual void Stop() override
	{
		Stopping = true;
	}

	virtual void Exit() override {}

protected:
	/** Update this socket receiver. */
	void Update(const float SocketWaitTime);

protected:
	//~ FSingleThreadRunnable interface

	virtual void Tick() override
	{
		Update(0.0f);
	}

private:
	/** The network socket. */
	nn::socket *Socket;

	/** Flag indicating that the thread is stopping. */
	bool Stopping;

	/** The thread object. */
	FRunnableThread *Thread;

	/** The thread's name. */
	FString ThreadName;

	/** The amount of time to wait for inbound packets. */
	float WaitTime;

	/** The maximum read buffer size used to read the socket. */
	uint32 MaxReadBufferSize = 2048u;

	char *RecvBuffer;

	// private:

	/** Holds the data received delegate. */
	// FOnSocketDataReceived DataReceivedDelegate;
};