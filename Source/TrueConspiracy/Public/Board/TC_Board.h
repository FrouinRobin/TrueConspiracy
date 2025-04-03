// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Board.generated.h"

class ATC_BoardSlot;
class ATC_LandCardSlot;
class ATC_Slot;
class ATC_Card;

USTRUCT(BlueprintType)
struct FBoardZone
{
	GENERATED_BODY()

	UPROPERTY()
	int32 OwnerPlayerIndex;

	UPROPERTY()
	TArray<ATC_BoardSlot*> Slots; 

};


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

	void InitializeBoard();
	bool TryPlaceCard(APlayerController* Player, ATC_Card* Card, ATC_Slot* Slot);

	//UPROPERTY()
	//FBoardZone PlayerZones[2];

	//UPROPERTY()
	 //TArray<ATC_LandCardSlot*> SharedLands;

};
