// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.h"
#include "TC_BoardZone.generated.h"

class ATC_BoardSlot;

UCLASS()
class TRUECONSPIRACY_API ATC_BoardZone : public AActor
{
	GENERATED_BODY()

public:
	ATC_BoardZone();

	void InitializeBoardSlots(TSubclassOf<ATC_BoardSlot> BoardSlotClass, TSubclassOf<ATC_Slot> SlotClass);

protected:
	virtual void BeginPlay() override;

public:
	// Le joueur auquel cette zone appartient (0 ou 1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	int32 OwnerPlayerIndex;

	// Slots appartenant à cette zone
	UPROPERTY()
	TArray<ATC_BoardSlot*> BoardSlots;

	// Visuel de la zone (ex: cadre, fond...)
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ZoneVisual;

};
