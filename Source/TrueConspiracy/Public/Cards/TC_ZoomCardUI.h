// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TC_ZoomCardUI.generated.h"

class ATC_Player;
/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UTC_ZoomCardUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	ATC_Player* GetWidgetPlayer();

	UFUNCTION(BlueprintCallable)
	void SetWidgetPlayer(ATC_Player* newPlayer);

private:
	ATC_Player* _PlayerWidget;
	
};
