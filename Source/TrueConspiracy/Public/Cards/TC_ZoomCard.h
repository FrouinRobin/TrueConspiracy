// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TC_ZoomCard.generated.h"

class ATC_Player;
/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UTC_ZoomCard : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	ATC_Player* GetWidgetPlayer();

	UFUNCTION(BlueprintCallable)
	void SetWidgetPlayer(ATC_Player* newPlayer);

private:

	ATC_Player* _playerWidget;

};
