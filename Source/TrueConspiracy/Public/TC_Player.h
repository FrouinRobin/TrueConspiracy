// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cards/TC_Card.h"
#include "TC_Player.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATC_Player();

	UPROPERTY(BlueprintReadWrite)
	uint8 PlayerID;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<ATC_Card*> _playerHand;
	TArray<ATC_Card*> _playerDeck;

	uint8 _playerCurrentMana;
	uint8 _playerMaxMana;

	ATC_Card* _selectedCard;

private:
	class UCameraComponent* _playerCamera;
	class USceneComponent* _cardAnchor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	ATC_Card* GetCardFromDeckByName(FString name, bool checkAllFaces);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	ATC_Card* GetCardFromDeckById(ETC_CardID id);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	void SetDeck(TArray<ATC_Card*> newDeck);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	TArray<ATC_Card*> GetDeck();
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	bool AddCardToDeck(ATC_Card* card);

	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	void SetHand(TArray<ATC_Card*> newDeck);
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	TArray<ATC_Card*> GetHand();
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	ATC_Card* GetCardFromHandByName(FString name, bool checkAllFaces);
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	ATC_Card* GetCardFromHandById(ETC_CardID id);
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	void ShowHandOnCamera();
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	bool AddCardToHand(ATC_Card* card);

	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	TArray<ATC_Card*> GetAvailableCards();
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	bool CanPlayAnyCard();
	UFUNCTION(BlueprintCallable, Category = "Player Hand")
	bool CanPlayCard(ATC_Card* card);

	UFUNCTION(BlueprintCallable, Category = "Player Mana")
	void SetPlayerMana(uint8 mana);
	UFUNCTION(BlueprintCallable, Category = "Player Mana")
	uint8 GetPlayerMana() const;
	UFUNCTION(BlueprintCallable, Category = "Player Mana")
	uint8 IncreaseManaLimit(uint8 value);
	UFUNCTION(BlueprintCallable, Category = "Player Mana")
	uint8 ChangeMana(uint8 value, bool allowOverflow);

	UFUNCTION(BlueprintCallable, Category = "Player Card")
	void SetSelectedCard(ATC_Card* card);
	UFUNCTION(BlueprintPure, Category = "Player Card", meta = (ReturnDisplayName = "Selected Card"))
	ATC_Card* GetSelectedCard();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSelectCard(ATC_Card* card, ATC_Card* oldCard);

};
