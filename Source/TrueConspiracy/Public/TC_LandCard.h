// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_BoardSlot.h"
#include "TC_LandCard.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API UTC_LandCard : public UObject
{
	GENERATED_BODY()
	
public:

	TArray<UTC_BoardSlot> BoardSlot;
	void ApplyBonus();
	void ApplyMalus();
};
