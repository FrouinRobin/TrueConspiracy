// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.h"
#include "TC_LandCard.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_LandCard : public AActor
{
	GENERATED_BODY()

public:

	ATC_LandCard();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandCard")
	TArray<ATC_BoardSlot*> BoardSlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LandCard")
	USceneComponent* LandCardRoot;

	UFUNCTION(BlueprintCallable)
	void ApplyBonus();

	UFUNCTION(BlueprintCallable)
	void ApplyMalus();
};

