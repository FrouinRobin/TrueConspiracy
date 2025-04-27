// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_DrawDeck.generated.h"

class ATC_Card;
class ATC_Board;
class ATC_Player;

UCLASS()
class TRUECONSPIRACY_API ATC_DrawDeck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATC_DrawDeck();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor"/*, Replicated*/)
	USceneComponent* MainAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor"/*, Replicated*/)
	USceneComponent* CardAnchor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Replicated)
	ATC_Player* _drawDeckPlayer;
	UPROPERTY(Replicated)
	ATC_Board* _drawDeckBoard;
	UPROPERTY(Replicated)
	TArray<ATC_Card*> _drawDeck;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Player* GetDrawDeckPlayer();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Board* GetDrawDeckBoard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_Card*> GetDrawDeck();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDrawDeckDataFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDrawDeckDataCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDrawDeckDataLastCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDrawDeckGameFirstCard();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* DrawCard();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDrawDeckGameCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDrawDeckGameCardLastCard();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckPlayer(ATC_Player* newDrawDeckPlayer);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckBoard(ATC_Board* newDrawDeckBoard);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeck(TArray<ATC_Card*> newDrawDeck);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckDataFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckDataCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckDataLastCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckGameFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckGameCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDrawDeckGameCardLastCard(ATC_Card* card);

	UFUNCTION(BlueprintCallable, Category = "Shuffle")
	TArray<TSubclassOf<ATC_Card>> ShuffleCard(TArray<TSubclassOf<ATC_Card>> PlayerDeckToShuffle);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init(TArray<TSubclassOf<ATC_Card>> CardsToSpawn);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
};
