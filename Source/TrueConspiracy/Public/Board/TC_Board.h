// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_DrawDeck.h"
#include "Board/TC_DiscardDeck.h"
#include "Net/UnrealNetwork.h"
#include "TC_Board.generated.h"

class ATC_Player;
class ATC_Plate;

UCLASS()
class TRUECONSPIRACY_API ATC_Board : public AActor
{
	GENERATED_BODY()

public:

	ATC_Board();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainAnchor"/*, Replicated*/)
	USceneComponent* MainAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlotOneAnchor"/*, Replicated*/)
	USceneComponent* BoardSlotOneAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlotTwoAnchor"/*, Replicated*/)
	USceneComponent* BoardSlotTwoAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardSlotThreeAnchor"/*, Replicated*/)
	USceneComponent* BoardSlotThreeAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardDrawAnchor"/*, Replicated*/)
	USceneComponent* BoardDrawAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardDiscardAnchor"/*, Replicated*/)
	USceneComponent* BoardDiscardAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_BoardSlot> BoardSlotBluePrint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_DrawDeck> DrawDeckBluePrint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BluePrintReference")
	TSubclassOf<ATC_DiscardDeck> DiscardDeckBluePrint;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_Plate* _boardPlate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_Player* _boardPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_DrawDeck* _boardDraw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_DiscardDeck* _boardDiscard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	TArray<ATC_BoardSlot*> _boardSlots;

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

	UFUNCTION(BlueprintCallable, Category = "Slots")
	TArray<ATC_Slot*> GetAllSlots() const;


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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	

};
