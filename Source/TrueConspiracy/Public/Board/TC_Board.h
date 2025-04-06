// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_DrawDeck.h"
#include "Board/TC_DiscardDeck.h"
#include "TC_Board.generated.h"

class ATC_Player;
class ATC_Plate;

UCLASS()
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()

public:

	ATC_Board();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainAnchor")
	USceneComponent* MainAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlotOneAnchor")
	USceneComponent* BoardSlotOneAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlotTwoAnchor")
	USceneComponent* BoardSlotTwoAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlotThreeAnchor")
	USceneComponent* BoardSlotThreeAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardDrawAnchor")
	USceneComponent* BoardDrawAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardDiscardAnchor")
	USceneComponent* BoardDiscardAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_BoardSlot> BoardSlotBluePrint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_DrawDeck> DrawDeckBluePrint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_DiscardDeck> DiscardDeckBluePrint;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Plate* GetBoardPlate();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Player* GetBoardPlayer();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_BoardSlot*> GetBoardSlots();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_DrawDeck* GetBoardDraw();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_DiscardDeck* GetBoardDiscard();



	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardPlater(ATC_Plate* newBoardPlate);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardPlayer(ATC_Player* player);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardSlots(TArray<ATC_BoardSlot*> slots);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDraw(ATC_DrawDeck* draw);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscard(ATC_DiscardDeck* draw);

	UFUNCTION(BlueprintCallable, Category = "ShuffleCards")
	TArray<TSubclassOf<ATC_Card>> ShuffleCard(TArray<TSubclassOf<ATC_Card>> PlayerDeckToShuffle);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDrawCard(ATC_Card* CardToDraw);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDrawNumberOfCard(int NbCardToDraw);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init();


private:
	ATC_Plate* _boardPlate;
	ATC_Player* _boardPlayer;
	ATC_DrawDeck* _boardDraw;
	ATC_DiscardDeck* _boardDiscard;
	TArray<ATC_BoardSlot*> _boardSlots;
};
