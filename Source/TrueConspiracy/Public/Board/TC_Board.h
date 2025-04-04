// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Board.generated.h"

class ATC_Player;
class ATC_BoardSlot;
class ATC_Plate;

UCLASS()
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()

public:

	ATC_Board();

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
	TArray<ATC_Card*> GetBoardDraw();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDrawDataFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDrawDataCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDrawDataLastCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDrawGameFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDrawGameCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDrawGameCardLastCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_Card*> GetBoardDiscard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDiscardDataFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDiscardDataCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDiscardDataLastCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDiscardGameFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDiscardGameCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetBoardDiscardGameCardLastCard();


	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardPlater(ATC_Plate* newBoardPlate);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardPlayer(ATC_Player* player);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardSlots(const TArray<ATC_BoardSlot*> slots);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDraw(const TArray<ATC_Card*> draw);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDrawDataFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDrawDataCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDrawDataLastCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDrawGameFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDrawGameCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDrawGameCardLastCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscard(const TArray<ATC_Card*> discard);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscardDataFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscardDataCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscardDataLastCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscardGameFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscardGameCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetBoardDiscardGameCardLastCard(ATC_Card* card);

	UFUNCTION(BlueprintCallable, Category = "ShuffleCards")
	TArray<ATC_Card*> ShuffleCard(TArray<ATC_Card*> PlayerDeckToShuffle);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDrawCard(ATC_Card* CardToDraw);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init();


private:
	ATC_Plate* _boardPlate;
	ATC_Player* _boardPlayer;
	TArray<ATC_BoardSlot*> _boardSlots;
	TArray<ATC_Card*> _boardDraw;
	TArray<ATC_Card*> _boardDiscard;
};
