// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardZone.h"
#include "TC_FightZone.h"
#include "TC_LandCard.h"
#include "TC_BoardSlot.h"
#include "TC_Slot.h"
#include "TC_Card.h"
#include "TC_Board.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()

public:
	ATC_Board();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitializeBoard();

	UFUNCTION(BlueprintCallable)
	bool PlaceCard(ATC_Card* Card, UTC_Slot* Slot);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_BoardZone*> BoardZones; // 2 zones (1 par joueur)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_FightZone*> FightZones; // 6 FightZones (3 par joueur)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_LandCard*> LandCards; // 6 LandCards (1 par FightZone)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_BoardSlot*> BoardSlots; // 6 BoardSlots (3 par joueur)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_Slot*> Slots; // 24 Slots (4 par BoardSlot)
};
