// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TC_TCPComponent.generated.h"

class FTC_TCPClient;

UCLASS(Blueprintable, ClassGroup = (Networking), meta = (BlueprintSpawnableComponent))
class TRUECONSPIRACY_API UTC_TCPComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTC_TCPComponent();

    UFUNCTION(BlueprintCallable, Category = "TCP")
    void StartClient(const FString& ServerIP, int32 ServerPort);

    UFUNCTION(BlueprintCallable, Category = "TCP")
    void SendMessageToServer(const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "TCP")
    void StopClient();

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCP")
    bool CanPing;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UFUNCTION(Category = "TCP")
    void _sendPing();

    FTimerHandle _pingTimerHandle;
    FTC_TCPClient* _tcpClient;
};
