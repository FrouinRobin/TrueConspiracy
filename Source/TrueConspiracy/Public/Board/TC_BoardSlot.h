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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerID;

	UFUNCTION(BlueprintCallable)
	TArray<UTC_Slot*> GetSlot();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_Slot*> _slot;
};
