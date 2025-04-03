// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardZone.h"
#include "TC_FightZone.h"
#include "TC_LandCardSlot.h"
#include "TC_BoardSlot.h"
#include "TC_Slot.h"
#include "TC_Board.generated.h"

class ATC_Card;

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()

public:
	ATC_Board();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TArray<ATC_BoardZone*> BoardZones; // 2 zones (1 par joueur)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TArray<ATC_FightZone*> FightZones; // 6 FightZones (3 par joueur)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TArray<ATC_LandCardSlot*> LandCards; // 6 LandCards (1 par FightZone)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TArray<ATC_BoardSlot*> BoardSlots; // 6 BoardSlots (3 par joueur)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TArray<ATC_Slot*> Slots; // 24 Slots (4 par BoardSlot)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _boardRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _boardZonesRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _fightZonesRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _slotsRoot;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitializeBoard();

	/*UFUNCTION(BlueprintCallable)
	bool PlaceCard(ATC_Card* Card, ATC_Slot* Slot);*/


};
