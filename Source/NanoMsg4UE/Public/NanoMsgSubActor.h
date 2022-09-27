#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NanoMsgRunnable.h"

#include <nanomsg/nn.hpp>
#include "NanoMsgSubActor.generated.h"

UCLASS()
class NANOMSG4UE_API ANanoMsgSubActor : public AActor
{
    GENERATED_BODY()

public:
    ANanoMsgSubActor();
    ~ANanoMsgSubActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    bool bIsInitialized;
    nn::socket *Socket;
    FNanoMsgRunnable *NanoMsgRunnable;
};