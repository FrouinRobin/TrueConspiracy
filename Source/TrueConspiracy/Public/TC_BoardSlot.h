// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_Slot.h"
#include "TC_BoardSlot.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API UTC_BoardSlot : public UObject
{
	GENERATED_BODY()
	
public:
	bool PlayerID;

	TArray<UTC_Slot> GetSlot();

protected:
	TArray<UTC_Slot> _slot;
};
