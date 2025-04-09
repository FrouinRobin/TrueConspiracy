// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TC_GameManager.h"
#include "TC_MainServer.generated.h"

class ATC_Player;

UCLASS()
class TRUECONSPIRACY_API ATC_MainServer : public AGameModeBase
{
	GENERATED_BODY()
public:
	TArray<ATC_GameManager*> ActiveSessions;

	TArray<ATC_Player*> ConnectedPlayer;
protected:
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
public:
	UFUNCTION(BlueprintCallable)
	void HandlePlayerConnection(ATC_Player* newPlayer);
	UFUNCTION(BlueprintCallable)
	void CreateNewSession(TArray<ATC_Player*> Players);
	UFUNCTION(BlueprintCallable)
	TArray<ATC_Player*> GetAvailablePlayer();
private:

};
