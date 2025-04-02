// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Slot.h"
#include "TC_BoardSlot.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TRUECONSPIRACY_API ATC_BoardSlot : public AActor
{
	GENERATED_BODY()

public:
	ATC_BoardSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlot")
	int32 PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlot")
	TArray<ATC_Slot*> Slots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoardSlot")
	USceneComponent* BoardSlotRoot;

	UFUNCTION(BlueprintCallable)
	TArray<ATC_Slot*> GetSlots();

	UFUNCTION()
	void OnBoardSlotOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:

};
