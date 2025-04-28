// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TC_Card.h"
#include "TC_LandCard.generated.h"

class ATC_LandCardSlot;

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API ATC_LandCard : public ATC_Card
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetLandSlot(ATC_LandCardSlot* InLandSlot);
public:
private:
	ATC_LandCardSlot* LandCardSlot;
	
};
