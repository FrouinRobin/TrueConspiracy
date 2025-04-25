// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Board/TC_Slot.h"
#include "TC_LandCardSlot.generated.h"

class ATC_LandCard;
class ATC_Player;

UCLASS()
class TRUECONSPIRACY_API ATC_LandCardSlot : public ATC_Slot
{
	GENERATED_BODY()

public:
	ATC_LandCardSlot();
public:
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_BoardSlot*>& GetLandCardBordSlot();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_BoardSlot* GetLandCardBordSlotByPlayer(ATC_Player* PlayerReference);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void LandCardInit();

private:
	TArray<ATC_BoardSlot*> _landCardBoardSlots;

};
