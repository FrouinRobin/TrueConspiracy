// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TC_CardDataStruct.h"
#include "TC_CardIfoGameWiget.generated.h"


class ATC_Card;
/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UTC_CardIfoGameWiget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	/*UPROPERTY(meta = (BindWidget))
	UTextBlock * CardNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardManaText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardScoreText;*/

protected:

	virtual void NativeConstruct();

public:
	UFUNCTION(BlueprintCallable)
	void SetCardInstance(ATC_Card* Instance);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateCardData(FTC_CardDataStruct CardData);

private:
	UPROPERTY()
	ATC_Card* CardInstance;

};
