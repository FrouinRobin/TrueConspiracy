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
	bool HasCard;
	ATC_Card* GetCard();
	void SetCard(ATC_Card*) ;

protected:
	ATC_Card* _card;
};
