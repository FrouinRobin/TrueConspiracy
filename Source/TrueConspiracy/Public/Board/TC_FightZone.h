// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_BoardSlot.h"
#include "TC_FightZone.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API UTC_FightZone : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_BoardSlot*> BoardSlots;
};

