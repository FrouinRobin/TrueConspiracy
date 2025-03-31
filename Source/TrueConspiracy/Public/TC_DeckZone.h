// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_Card.h"
#include "TC_DeckZone.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API UTC_DeckZone : public UObject
{
	GENERATED_BODY()
	
public:

	bool PlayerID;
	TArray<ATC_Card*> GetHand();

	void AddCard(ATC_Card*);
	void RemoveCard(ATC_Card*);

	ATC_Card* GetCard(float);
	ATC_Card* GetCard(ATC_Card);

protected:

	TArray<ATC_Card*> _hand;
};
