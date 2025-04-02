// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Card.h"
#include "TC_Slot.generated.h"

UENUM(BlueprintType)
enum class ETC_SlotState : uint8
{
	Empty,
	Occupied
};

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_Slot : public AActor
{
	GENERATED_BODY()

public:
	ATC_Slot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ETC_SlotState SlotState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ATC_Card* _card;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot")
	USceneComponent* SlotRoot;

	UFUNCTION(BlueprintCallable)
	ATC_Card* GetCard();

	UFUNCTION(BlueprintCallable)
	void SetCard(ATC_Card* NewCard);

	UFUNCTION(BlueprintCallable)
	bool HasCard();

	UFUNCTION()
	void OnSlotOverlap(AActor* OverlappedActor, AActor* OtherActor);
};