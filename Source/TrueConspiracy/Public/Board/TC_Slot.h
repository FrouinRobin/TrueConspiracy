// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Slot.generated.h"

class ATC_Card;

UCLASS()
class TRUECONSPIRACY_API ATC_Slot : public AActor
{
	GENERATED_BODY()

public:
	ATC_Slot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* visualMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETC_CardType _slotCardType;

protected:

public:

	UFUNCTION(BlueprintCallable)
	bool HasCard();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetSlotCard();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_BoardSlot* GetSlaotBoardSlot();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ETC_CardType GetSlotCardType();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetSlotCard(ATC_Card* newSlotCard);

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetSlotBoardSlot(ATC_BoardSlot* newSlotBoardSlot);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	void SetSlotCardType(ETC_CardType newSlotCardType);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init();



private:
	ATC_BoardSlot* _slotBoardSlot;
	ATC_Card* _slotCard;
	//ETC_CardType _slotCardType;
};