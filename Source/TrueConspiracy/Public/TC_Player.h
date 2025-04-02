// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <TC_Card.h>
#include "TC_Player.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATC_Player();

	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	ATC_Card* GetCardFromDeckByName(FString name, bool checkAllFaces);

	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	// To know: how IDs would work for cards
	// Would a card have an ID for both faces or would each faces have their unique IDs?
	ATC_Card* GetCardFromDeckById(FString id);

	//ATC_Card* GetCardFromDeckByCondition();
		
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	void SetDeck(TArray<ATC_Card*> newDeck);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	TArray<ATC_Card*> GetDeck();

	UFUNCTION(BlueprintCallable, Category = "Player Mana")
	void SetPlayerMana(uint8 mana);
	UFUNCTION(BlueprintCallable, Category = "Player Mana")
	uint8 GetPlayerMana() const;

	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	bool AddCardToDeck(ATC_Card* card);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	void ShowDeckOnCamera();

	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	TArray<ATC_Card*> GetAvailableCards();
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	bool CanPlayACard();
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	bool CanPlayCard(ATC_Card* card);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<ATC_Card*> _playerDeck;

	uint8 _playerMana;

private:
	class UCameraComponent* _playerCamera;
	class USceneComponent* _cardAnchor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
