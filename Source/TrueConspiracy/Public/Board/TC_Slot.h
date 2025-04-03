// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Slot.generated.h"

class ATC_Card;

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_Slot : public AActor
{
	GENERATED_BODY()

public:
	ATC_Slot();

	bool HasCard() const { return OccupyingCard != nullptr;  }
	void SetCard(ATC_Card* Card);

	UPROPERTY()
	ATC_Card* OccupyingCard;

};