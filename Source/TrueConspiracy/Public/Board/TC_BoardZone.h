// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.h"
#include "TC_BoardZone.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_BoardZone : public AActor
{
	GENERATED_BODY()

public:
	ATC_BoardZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardZone")
	TArray<ATC_BoardSlot*> BoardSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardZone")
	int32 PlayerID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoardZone")
	USceneComponent* BoardZoneRoot;
};
