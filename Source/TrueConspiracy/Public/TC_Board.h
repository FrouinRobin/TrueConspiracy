// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardZone.h"
#include "TC_FightZone.h"
#include "TC_LandCard.h"
#include "TC_Board.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATC_Board();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TArray<UTC_BoardZone> BoardZones;
	TArray<UTC_FightZone> FightZones;
	TArray<UTC_LandCard> LandCards;
};
