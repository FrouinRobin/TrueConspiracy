// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_DiscardDeck.generated.h"

class ATC_Card;
class ATC_Board;

UCLASS()
class TRUECONSPIRACY_API ATC_DiscardDeck : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATC_DiscardDeck();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor", Replicated)
	USceneComponent* MainAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor", Replicated)
	USceneComponent* CardAnchor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	ATC_Board* _discardDeckBoard;
	UPROPERTY(Replicated)
	TArray<ATC_Card*> _discardDeck;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Board* GetDiscardDeckBoard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_Card*> GetDiscardDeck();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDiscardDeckDataFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDiscardDeckDataCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDiscardDeckDataLastCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDiscardDeckGameFirstCard();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDiscardDeckGameCardAtIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Card* GetDiscardDeckGameCardLastCard();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckBoard(ATC_Board* newDiscardDeckBoard);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeck(TArray<ATC_Card*> newDiscardDeck);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckDataFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckDataCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckDataLastCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckGameFirstCard(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckGameCardAtIndex(int index, ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetDiscardDeckGameCardLastCard(ATC_Card* card);

	UFUNCTION(BlueprintCallable, Category = "Add")
	void AddToDiscard(ATC_Card* CardToDiscard);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

};
