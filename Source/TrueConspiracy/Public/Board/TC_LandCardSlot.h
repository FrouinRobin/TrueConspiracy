// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Board/TC_Slot.h"
#include "TC_LandCardSlot.generated.h"

class ATC_LandCard;
class ATC_Player;
class ATC_Plate;

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

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetLandCard(ATC_LandCard* InCard);

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetLandPlate(ATC_Plate* InPlate);

	ATC_Plate* GetLandPlate();

	UFUNCTION(BlueprintCallable, Category = "Init")
	void LandCardInit();

private:
	TArray<ATC_BoardSlot*> _landCardBoardSlots;
	ATC_LandCard* _landSlot;

	ATC_Plate* _landPlate;

};
