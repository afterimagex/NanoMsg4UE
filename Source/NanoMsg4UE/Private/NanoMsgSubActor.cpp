#pragma once

#include "NanoMsgSubActor.h"
#include "Kismet/KismetSystemLibrary.h"

#include <nanomsg/pubsub.h>

// Sets default values
ANanoMsgSubActor::ANanoMsgSubActor()
	: bIsInitialized(false), Socket(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ANanoMsgSubActor::~ANanoMsgSubActor()
{
	if (bIsInitialized)
	{
		// Socket->shutdown(0);
	}
}

// Called when the game starts or when spawned
void ANanoMsgSubActor::BeginPlay()
{
	Super::BeginPlay();

	if (UKismetSystemLibrary::IsDedicatedServer(GetWorld()) == false)
	{
		const char *optval = "skeletal";
		Socket = new nn::socket(AF_SP, NN_SUB);
		Socket->setsockopt(NN_SUB, NN_SUB_SUBSCRIBE, optval, strlen(optval));
		int rc = Socket->connect("tcp://127.0.0.1:7788");
		if (rc < 0)
		{
			UE_LOG(LogTemp, Log, TEXT("socket in NanoMsgSubActor connect failed."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("socket in NanoMsgSubActor connect success."));
			bIsInitialized = true;
			NanoMsgRunnable = new FNanoMsgRunnable(Socket, 0.1, TEXT("FNanoMsgSubscribe"));
			NanoMsgRunnable->Start();
		}
	}
}

void ANanoMsgSubActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (bIsInitialized)
	{
		NanoMsgRunnable->Stop();
	}
}

// Called every frame
void ANanoMsgSubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}