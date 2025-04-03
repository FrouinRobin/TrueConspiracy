// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BoardSlot.generated.h"

class ATC_Slot;

UCLASS()
class TRUECONSPIRACY_API ATC_BoardSlot : public AActor
{
	GENERATED_BODY()

public:
	ATC_BoardSlot();

	UFUNCTION()
	void InitializeSlots();

public:
	UPROPERTY()
	int32 OwnerPlayerIndex;

	// Composant racine
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	// Représentation visuelle du BoardSlot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SlotVisual;

	// Chaque BoardSlot contient 4 emplacements de carte
	UPROPERTY()
	TArray<ATC_Slot*> Slots;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<ATC_Slot> SlotClass;
};
