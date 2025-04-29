// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TC_CardIfoGameWiget.generated.h"


class ATC_Card;
class UTC_Face;

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UTC_CardIfoGameWiget : public UUserWidget
{
	GENERATED_BODY()
	

public:

protected:

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetPureWidgetCard"))
	ATC_Card* GetPureWidgetCard();

	UFUNCTION(BlueprintCallable)
	ATC_Card* GetWidgetCard();

	UFUNCTION(BlueprintCallable)
	void SetWidgetCard(ATC_Card* newCard);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUpdateCardData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInit(UTC_Face* FaceRef);

private:
	ATC_Card* _widgetCard;
};
