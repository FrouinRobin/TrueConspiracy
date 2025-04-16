// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cards/TC_Card.h"
#include <TC_PlayerState.h>
#include "TC_Player.generated.h"

class ATC_Board;

UENUM(BlueprintType)
enum class ETC_PhaseState : uint8
{
	Attack,
	Defense,
};

UCLASS()
class TRUECONSPIRACY_API ATC_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATC_Player();

	UPROPERTY(BlueprintReadWrite)
	uint8 PlayerID;
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* _cameraAnchor;
	UPROPERTY(BlueprintReadOnly)
	class UCameraComponent* _playerCamera;
	UPROPERTY(BlueprintReadOnly)
	class USceneComponent* _cardAnchor;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	uint8 _playerCurrentMana;
	uint8 _playerMaxMana;

	ATC_Card* _selectedCard;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TMap<ETC_PlayerState, FTransform> _playerTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ETC_PhaseState _phaseState;
	ETC_PlayerState _PlayerState;
	
	ATC_Board* _playerBoard;

	TArray<ATC_Card*> _playerHand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<ATC_Card>> _playerDeck;

	float _transformTransitionTimer;
	float _transformTransitionTimerGoal;
	bool _isTransformTransitionOn;
	bool _canUseTransformTransition = false;
	FTransform _transformTransitionGoal;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UFUNCTION(BlueprintCallable, Category = "Player Deck")
	ATC_Card* GetCardFromDeckByName(FString name, bool checkAllFaces);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	ATC_Card* GetCardFromDeckById(ETC_CardID id);*/
	UFUNCTION(BlueprintCallable, Category = "Player Board")
	ATC_Board* GetPlayerBoard();
	UFUNCTION(BlueprintCallable, Category = "Player Board")
	void SetPlayerBoard(ATC_Board* newBoard);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	void SetDeck(TArray<TSubclassOf<ATC_Card>> newDeck);
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	TArray<TSubclassOf<ATC_Card>> GetDeck();
	UFUNCTION(BlueprintCallable, Category = "Player Deck")
	bool AddCardToDeck(TSubclassOf<ATC_Card> card);

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
	bool AddCardToHand(TSubclassOf<ATC_Card> card);

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

	void SetPhaseState(ETC_PhaseState InPhaseState);
	ETC_PhaseState GetPhaseState() const;

	void SetPlayerMaxMana(uint8 InManaMax);
	uint8 GetPlayerMaxMana() const;

	/*UFUNCTION(BlueprintCallable)
	TSubclassOf<ATC_Card> FindCardClassFromInstance(ATC_Card* InstanceCard);*/

	UFUNCTION(BlueprintCallable)
	void PlayCard(ATC_Card* InCard, ATC_Slot* InSlot);

	void SwitchFace(ATC_Card* Card);
	
	UFUNCTION(BlueprintCallable)
	void MoveCard(ATC_Card* InCard, ATC_Slot* InSlot);
	UFUNCTION(BlueprintCallable)
	void SwapCard(ATC_Card* InCardOne, ATC_Card* InCardTwo);
	
	UFUNCTION(BlueprintCallable)
	void RemoveCardFromHand(ATC_Card* Card);

	UFUNCTION(BlueprintCallable, Category = "Player State")
	void SetState(ETC_PlayerState State);
	UFUNCTION(BlueprintPure, Category = "Player State", meta = (ReturnDisplayName = "Current State"))
	ETC_PlayerState GetState();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player State")
	void OnStateChange(ETC_PlayerState newState, ETC_PlayerState oldState);

	UFUNCTION(BlueprintCallable, Category = "Card Validation")
	bool CanPlaceCardOnSlot(ATC_Card* Card, ATC_Slot* Slot);

	UFUNCTION(BlueprintCallable, Category = "Card Validation")
	TArray<ATC_Slot*> GetValidSlotsForCard(ATC_Card* Card);

private:
	UFUNCTION(CallInEditor)
	void ActivateStateTransform(bool on, FTransform goal);
	void TickStateTransform(float dt);
	UFUNCTION(CallInEditor)
	void SwitchTransformTransition();
};
