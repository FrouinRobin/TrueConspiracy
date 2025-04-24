// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "TC_BoardSlot.generated.h"

class ATC_Slot;

UCLASS()
class TRUECONSPIRACY_API ATC_BoardSlot : public AActor
{
	GENERATED_BODY()

public:
	ATC_BoardSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainAnchor", Replicated)
	USceneComponent* MainAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotOneAnchor", Replicated)
	USceneComponent* SlotOneAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotTwoAnchor", Replicated)
	USceneComponent* SlotTwoAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotThreeAnchor", Replicated)
	USceneComponent* SlotThreeAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlotFourAnchor", Replicated)
	USceneComponent* SlotFourAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference", Replicated)
	TSubclassOf<ATC_Slot> SlotBluePrint;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_Board* _boardSlotBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_BoardSlot* _boardSlotOppositeBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	TArray<ATC_Slot*> _boardSlotSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	UStaticMesh* _cardMesh;

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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	
};
