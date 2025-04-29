// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Cards/TC_Card.h"
#include "TC_PlayerState.h"
#include "TC_Player.generated.h"

class ATC_Board;

UENUM(BlueprintType)
enum class ETC_PhaseState : uint8
{
	Attack		UMETA(DisplayName = "Attack"),
	Defense		UMETA(DisplayName = "Defense")
};

UCLASS()
class TRUECONSPIRACY_API ATC_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATC_Player();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ID")
	int PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anchor")
	USceneComponent* MainAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anchor")
	USceneComponent* CameraAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anchor")
	USceneComponent* PlayerCardAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	TArray<TSubclassOf<ATC_Card>> PlayerDeck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TransformMap")
	TMap<ETC_PlayerState, FTransform> PlayerTransform;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	/*UFUNCTION(BlueprintCallable, Category = "Getter")
	ATC_Card* GetCardFromDeckByName(FString name, bool checkAllFaces);
	UFUNCTION(BlueprintCallable, Category = "Getter")
	ATC_Card* GetCardFromDeckById(ETC_CardID id);*/
	// === Getters ===
	UFUNCTION(BlueprintCallable, Category = "Getter")
	int GetPlayerRoundWon();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ATC_Board* GetPlayerBoard();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	TArray<TSubclassOf<ATC_Card>>& GetDeck();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	TArray<ATC_Card*>& GetHand();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ATC_Card* GetCardFromHandByName(FString name, bool checkAllFaces);

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ATC_Card* GetCardFromHandById(ETC_CardID id);

	UFUNCTION(BlueprintCallable, Category = "Getter")
	int GetPlayerCurrentMana();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	int GetPlayerMaxMana();

	UFUNCTION(BlueprintPure, Category = "Getter", meta = (ReturnDisplayName = "Selected Card"))
	ATC_Card* GetPlayerSelectedCard();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ETC_PhaseState GetPlayerPhaseState();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ETC_PlayerState GetPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	TArray<ATC_Slot*> GetValidSlotsForCard(ATC_Card* Card);

	UFUNCTION(BlueprintCallable, Category = "Getter")
	TArray<ATC_Slot*> GetValidSlotsForCardTarget(ATC_Card* Card);

	UFUNCTION(BlueprintCallable, Category = "Getter", CallInEditor)
	TArray<ATC_Card*> GetAllPlayerCard(bool takeHand);

	UFUNCTION(BlueprintPure)
	TArray<ATC_Card*> GetCardsWaitingTargetList();

	// === Setters ===
	UFUNCTION(BlueprintCallable, Category = "Getter")
	void SetPlayerRoundWon(int newRoundWons);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerBoard(ATC_Board* newBoard);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerDeck(TArray<TSubclassOf<ATC_Card>>& newDeck);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerHand(TArray<ATC_Card*>& newDeck);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerCurrentMana(int newCurrentMana);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerMaxMana(int newMaxMana);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerPhaseState(ETC_PhaseState newPhaseState);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerSelectedCard(ATC_Card* newSelectedCard);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetPlayerState(ETC_PlayerState newState);

	// === Other Functions ===

	/*UFUNCTION(BlueprintCallable, Category = "Getter")
	bool CanPlayCard(ATC_Card* card);*/

	UFUNCTION(BlueprintCallable)
	bool AddCardToDeck(TSubclassOf<ATC_Card> card);

	UFUNCTION(BlueprintCallable)
	void ShowHandOnCamera();

	UFUNCTION(BlueprintCallable)
	bool AddCardToHand(TSubclassOf<ATC_Card> card);

	UFUNCTION(BlueprintCallable)
	ATC_Card* PlayCard(ATC_Card* InCard, ATC_Slot* InSlot);

	UFUNCTION(BlueprintCallable)
	void SwitchFace(ATC_Card* Card);

	UFUNCTION(BlueprintCallable)
	void MoveCard(ATC_Card* InCard, ATC_Slot* InSlot);

	UFUNCTION(BlueprintCallable)
	void SwapCard(ATC_Card* InCardOne, ATC_Card* InCardTwo);

	UFUNCTION(BlueprintCallable)
	void RemoveCardFromHand(ATC_Card* Card);

	UFUNCTION(BlueprintCallable)
	void RemoveCardFromDeck(ATC_Card* Card);

	UFUNCTION(BlueprintCallable)
	bool CanPlaceCardOnSlot(ATC_Card* Card, ATC_Slot* Slot);

	UFUNCTION(BlueprintCallable)
	void ActivateStateTransform(bool on, FTransform goal);

	UFUNCTION(BlueprintCallable)
	void TickStateTransform(float dt);

	UFUNCTION(BlueprintCallable)
	void SwitchTransformTransition();

	UFUNCTION(BlueprintCallable)
	void AddCardToWaitingTargetList(ATC_Card* card);
	UFUNCTION(BlueprintCallable)
	bool RemoveCardToWaitingTargetList(ATC_Card* card);

	UFUNCTION(CallInEditor, Category = "Do Rotation")
	void dorotate();

	// === Events ===
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSelectCard(ATC_Card* card, ATC_Card* oldCard);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnStateChange(ETC_PlayerState newState, ETC_PlayerState oldState);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnChangePhaseState(ETC_PhaseState newPhaseState);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnStartGame();
	

private:

	int _playerRoundWon;

	ETC_PhaseState _playerPhaseState;
	ETC_PlayerState _PlayerState;

	ATC_Board* _playerBoard;

	TArray<ATC_Card*> _playerHand;
	int _playerCurrentMana;
	int _playerMaxMana;

	ATC_Card* _playerSelectedCard;

	TArray<ATC_Card*> _cardsWaitingTarget;

	float _transformTransitionTimer;
	float _transformTransitionTimerGoal;
	bool _isTransformTransitionOn;
	bool _canUseTransformTransition = false;
	FTransform _transformTransitionGoal;

	float _maxCardRotation = 5.f;
	float _minCardRotation = -5.f;
};
