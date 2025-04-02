// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.h"
#include "TC_LandCardSlot.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_LandCardSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATC_LandCardSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandCard")
	TArray<ATC_BoardSlot*> BoardSlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LandCard")
	USceneComponent* LandCardRoot;
protected:


public:	


};
