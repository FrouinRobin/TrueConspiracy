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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainAnchor")
	USceneComponent* MainAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotOneAnchor")
	USceneComponent* SlotOneAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotTwoAnchor")
	USceneComponent* SlotTwoAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotThreeAnchor")
	USceneComponent* SlotThreeAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotFourAnchor")
	USceneComponent* SlotFourAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_Slot> SlotBluePrint;
	
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Board* GetBoardSlotBoard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_Slot*> GetBoardSlotSlots();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_BoardSlot* GetBoardSlotOppositeBoard();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardSlotBoard(ATC_Board* newBoard);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardSlotOppositeBoard(ATC_BoardSlot* newOppositeBoard);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init();

private:

	ATC_Board* _boardSlotBoard;
	ATC_BoardSlot* _boardSlotOppositeBoard;
	TArray<ATC_Slot*> _boardSlotSlots;
	UStaticMesh* _cardMesh;
};
