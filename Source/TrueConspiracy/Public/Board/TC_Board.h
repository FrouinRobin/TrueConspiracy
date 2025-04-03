// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardZone.h"
#include "TC_LandCardSlot.h"
#include "TC_BoardSlot.h"
#include "TC_Slot.h"
#include "TC_Board.generated.h"

class ATC_BoardSlot;
class ATC_LandCardSlot;
class ATC_Slot;
class ATC_Card;
class ATC_BoardZone;

USTRUCT(BlueprintType)
struct FBoardZone
{
	GENERATED_BODY()

	UPROPERTY()
	int32 OwnerPlayerIndex;

	UPROPERTY()
	TArray<ATC_BoardSlot*> Slots; // 3 slots par joueur
};

UCLASS()
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()

public:
	ATC_Board();

	void InitializeBoard();

	bool TryPlaceCard(APlayerController* Player, ATC_Card* Card, ATC_Slot* Slot);

protected:
	virtual void BeginPlay() override;

public:
	// Chaque joueur possède une zone regroupant 3 BoardSlots
	UPROPERTY()
	TArray<ATC_BoardZone*> PlayerZones;

	// 3 lands partagés au centre
	UPROPERTY()
	TArray<ATC_LandCardSlot*> SharedLands;

	UPROPERTY(EditAnywhere, Category = "Spawnables")
	TSubclassOf<ATC_BoardSlot> BoardSlotClass;

	UPROPERTY(EditAnywhere, Category = "Spawnables")
	TSubclassOf<ATC_Slot> SlotClass;

	UPROPERTY(EditAnywhere, Category = "Spawnables")
	TSubclassOf<ATC_LandCardSlot> LandSlotClass;

	UPROPERTY(EditAnywhere, Category = "Spawnables")
	TSubclassOf<ATC_BoardZone> BoardZoneClass;

	UPROPERTY(VisibleAnywhere, Category = "Layout")
	USceneComponent* LayoutRoot;

	UPROPERTY(VisibleAnywhere, Category = "Anchors")
	USceneComponent* P1_ZoneAnchor;

	UPROPERTY(VisibleAnywhere, Category = "Anchors")
	USceneComponent* P0_ZoneAnchor;

	UPROPERTY(VisibleAnywhere, Category = "Anchors")
	TArray<USceneComponent*> LandAnchors;

};
