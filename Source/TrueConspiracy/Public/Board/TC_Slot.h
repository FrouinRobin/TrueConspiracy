// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_Card.h"
#include "TC_Slot.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API UTC_Slot : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasCard;

	UFUNCTION(BlueprintCallable)
	ATC_Card* GetCard();

	UFUNCTION(BlueprintCallable)
	void SetCard(ATC_Card* card);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATC_Card* _card;
};