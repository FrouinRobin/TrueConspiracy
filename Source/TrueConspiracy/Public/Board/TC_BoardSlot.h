// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.generated.h"

class ATC_Slot;

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_BoardSlot : public AActor
{
	GENERATED_BODY()

public:
	ATC_BoardSlot();

	UPROPERTY()
	int32 OwnerPlayerIndex;

	UPROPERTY()
	TArray<ATC_Slot*> Slots;


protected:

};
