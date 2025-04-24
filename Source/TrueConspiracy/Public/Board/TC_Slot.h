// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Slot.generated.h"

class ATC_Card;

UCLASS()
class TRUECONSPIRACY_API ATC_Slot : public AActor
{
	GENERATED_BODY()

public:
	ATC_Slot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	UStaticMeshComponent* visualMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	ETC_CardType _slotCardType;

protected:
	UPROPERTY(Replicated)
	ATC_BoardSlot* _slotBoardSlot;
	UPROPERTY(Replicated)
	ATC_Card* _slotCard;
	//ETC_CardType _slotCardType;
public:

	UFUNCTION(BlueprintCallable)
	bool HasCard();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetSlotCard();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_BoardSlot* GetSlotBoardSlot();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ETC_CardType GetSlotCardType();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetSlotCard(ATC_Card* newSlotCard);

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetSlotBoardSlot(ATC_BoardSlot* newSlotBoardSlot);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	void SetSlotCardType(ETC_CardType newSlotCardType);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
};