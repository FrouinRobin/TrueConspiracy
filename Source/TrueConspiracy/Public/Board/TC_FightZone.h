// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.h"
#include "TC_FightZone.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_FightZone : public AActor
{
	GENERATED_BODY()

public:

	ATC_FightZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FightZone")
	TArray<ATC_BoardSlot*> BoardSlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FightZone")
	USceneComponent* FightZoneRoot;
};

