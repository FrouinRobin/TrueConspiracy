// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_LandCardSlot.generated.h"

class ATC_LandCard;

UCLASS()
class TRUECONSPIRACY_API ATC_LandCardSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATC_LandCardSlot();

	//bool IsOccupied() const { return LandCard != nullptr; }
	bool IsUsableBy(APlayerController* Player)const;

	//UPROPERTY()
	//ATC_LandCard* LandCard;


	UPROPERTY()
	APlayerController* indexOwner;

protected:


public:	


};
