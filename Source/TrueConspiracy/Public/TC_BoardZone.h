// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_BoardSlot.h"
#include "TC_BoardZone.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API UTC_BoardZone : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<UTC_BoardSlot> BoardSlot;
	bool PlayerID;
};
