// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_Player.h"
#include "Camera/CameraComponent.h"
#include <Cards/Faces/TC_Face.h>
#include <Components/SphereComponent.h>
#include <TC_GameInstance.h>
#include "TC_AIActions.h"
#include <TC_ActionsSystem.h>
#include <Kismet/GameplayStatics.h>
#include "TC_GameManager.h"
#include "Board/TC_Slot.h"
#include "Board/TC_Board.h"
#include "TC_CardCondition.h"



// Sets default values
ATC_Player::ATC_Player()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("MainAnchor"));
	RootComponent = MainAnchor;

	CameraAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CameraAnchor"));
	CameraAnchor->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraAnchor);

	PlayerCardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CardAnchor"));
	PlayerCardAnchor->SetupAttachment(RootComponent);
	PlayerCardAnchor->SetRelativeLocation(FVector(150, 0, -120));


	_PlayerState = ETC_PlayerState::SELECTHAND;
}

// Called when the game starts or when spawned
void ATC_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int ATC_Player::GetPlayerRoundWon()
{
	return _playerRoundWon;
}

ATC_Board* ATC_Player::GetPlayerBoard()
{
	return _playerBoard;
}

TArray<TSubclassOf<ATC_Card>> ATC_Player::GetDeck()
{
	return PlayerDeck;
}

TArray<ATC_Card*> ATC_Player::GetHand()
{
	return _playerHand;
}

ATC_Card* ATC_Player::GetCardFromHandByName(FString name, bool checkAllFaces)
{
	for (ATC_Card* Card : _playerHand)
	{
		if (checkAllFaces)
		{
			// I don't know why we can have more than 2 faces but whatever, let's check them all
			for (UTC_Face* Face : Card->GetCardFaceList())
			{
				if (Face->GetName() == name)
					return Card;
			}
		}
		else
		{
			if (Card->GetCardCurrentFace()->GetName() == name)
			{
				return Card;
			}
		}
	}
	return nullptr;
}

ATC_Card* ATC_Player::GetCardFromHandById(ETC_CardID id)
{
	for (ATC_Card* Card : _playerHand)
	{
		if (Card->GetCardID() == id)
		{
			return Card;
		}
	}
	return nullptr;
}

int ATC_Player::GetPlayerCurrentMana()
{
	return _playerCurrentMana;
}


int ATC_Player::GetPlayerMaxMana()
{
	return _playerMaxMana;
}

ATC_Card* ATC_Player::GetPlayerSelectedCard()
{
	return _playerSelectedCard;
}

ETC_PhaseState ATC_Player::GetPlayerPhaseState()
{
	return _playerPhaseState;
}


ETC_PlayerState ATC_Player::GetPlayerState()
{
	return _PlayerState;
}

TArray<ATC_Slot*> ATC_Player::GetValidSlotsForCard(ATC_Card* Card)
{
	TArray<ATC_Slot*> AvailableSlot;
	for (ATC_BoardSlot* BoardSlot : GetPlayerBoard()->GetBoardSlots())
	{
		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			if (!Slot->HasCard() && Slot->GetSlotCardType() == Card->GetCardType())
			{
				AvailableSlot.Add(Slot);
			}
		}
	}
	return AvailableSlot;
}

TArray<ATC_Card*> ATC_Player::GetAllPlayerCard(bool takeHand)
{
	TArray<ATC_Card*> PlayerCard;
	if (takeHand)
	{
		for (ATC_Card* HandCard : _playerHand)
		{
			if (HandCard != nullptr)
			{
				PlayerCard.Add(HandCard);
			}
		}
	}
	for (ATC_BoardSlot* BoardSlot : _playerBoard->GetBoardSlots())
	{
		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			if(Slot->GetSlotCard() != nullptr)
			{
				PlayerCard.Add(Slot->GetSlotCard());
			}
		}
	}
	return PlayerCard;
}

void ATC_Player::dorotate()
{
	OnChangePhaseState(ETC_PhaseState::Attack);
}

TArray<ATC_Card*> ATC_Player::GetCardsWaitingTargetList()
{
	return _cardsWaitingTarget;
}

void ATC_Player::SetPlayerRoundWon(int newRoundWons)
{
	_playerRoundWon = newRoundWons
}

void ATC_Player::SetPlayerBoard(ATC_Board* newBoard)
{
	_playerBoard = newBoard;
}

void ATC_Player::SetPlayerDeck(TArray<TSubclassOf<ATC_Card>> newDeck)
{
	PlayerDeck = newDeck;
}

void ATC_Player::SetPlayerHand(TArray<ATC_Card*> newDeck)
{
	_playerHand = newDeck;
}

void ATC_Player::SetPlayerCurrentMana(int newCurrrentMana)
{
	_playerCurrentMana = newCurrrentMana;
}

void ATC_Player::SetPlayerPhaseState(ETC_PhaseState newPhaseState)
{
	_playerPhaseState = newPhaseState;
	OnChangePhaseState(_playerPhaseState);
}

void ATC_Player::SetPlayerMaxMana(int newManaMax)
{
	_playerMaxMana = newManaMax;
}

void ATC_Player::SetPlayerSelectedCard(ATC_Card* newSelectedCard)
{
	if (_playerSelectedCard == newSelectedCard)
		return;
	ATC_Card* OldCard = _playerSelectedCard;
	_playerSelectedCard = newSelectedCard;
	OnSelectCard(_playerSelectedCard, OldCard);
}

void ATC_Player::SetPlayerState(ETC_PlayerState newState)
{
	ETC_PlayerState oldState = _PlayerState;
	_PlayerState = newState;
	OnStateChange(_PlayerState, oldState);
}



bool ATC_Player::AddCardToHand(TSubclassOf<ATC_Card> card)
{
	if (card)
	{
		ATC_Card* NewCard = GetWorld()->SpawnActor<ATC_Card>(card, PlayerCardAnchor->GetComponentLocation(), PlayerCardAnchor->GetComponentRotation());
		_playerHand.Add(NewCard);
		NewCard->AttachToComponent(PlayerCardAnchor, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true));
		NewCard->SetPlayer(this);
		NewCard->CardAnchor->SetRelativeRotation(FRotator(-69.f, 180.f, 0.f));
		NewCard->CardAnchor->UpdateComponentToWorld();
		NewCard->Init();
	}


	ShowHandOnCamera();
	return true;
}

bool ATC_Player::AddCardToDeck(TSubclassOf<ATC_Card> card)
{
	PlayerDeck.Add(card);

	return true;
}

// Can someone smarter that knows how a card hand works rework this function?
void ATC_Player::ShowHandOnCamera()
{
	for (size_t i = 0; i < _playerHand.Num(); i++)
	{
		auto card = _playerHand[i];
		card->SetActorRelativeLocation(FVector::ZeroVector);

		FVector origin;
		FVector box;
		card->GetActorBounds(false, origin, box, false);

		UE_LOG(LogTemp, Warning, TEXT("Origin is %s"), *origin.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Box is %s"), *box.ToString());

		FVector base = FVector::ZeroVector;
		if (PlayerDeck.Num() % 2 == 0)
			base = FVector(0, -20, 0);

		float interval = ((float)i - ((float)_playerHand.Num() - 1) / 2) * 50;

		card->SetActorLocation(card->GetActorLocation() + base + FVector(0, 0, box.Y) + FVector(0, interval, 0));
	}
}

bool ATC_Player::CanPlayCard(ATC_Card* card)
{
	return card->GetCardCurrentMana() >= GetPlayerCurrentMana();
}

//TSubclassOf<ATC_Card> ATC_Player::FindCardClassFromInstance(ATC_Card* InstanceCard)
//{
//	if (!InstanceCard) return nullptr;
//
//	for (TSubclassOf<ATC_Card> CardClass : _playerHand)
//	{
//		if (CardClass && InstanceCard->GetClass() == CardClass)
//		{
//			return CardClass;
//		}
//	}
//
//	return nullptr;
//}


void ATC_Player::RemoveCardFromHand(ATC_Card* Card)
{
	if (!_playerHand.Contains(Card)) return;

	_playerHand.Remove(Card);
	Card->Destroy();
	ShowHandOnCamera();
}

void ATC_Player::RemoveCardFromDeck(ATC_Card* Card)
{
	if (!Card) return;

	TSubclassOf<ATC_Card> CardClass = Card->GetClass();

	if (!PlayerDeck.Contains(CardClass)) return;

	PlayerDeck.Remove(CardClass);
	Card->Destroy();
	ShowHandOnCamera();
}

void ATC_Player::SwitchFace(ATC_Card* Card)
{
	Card->SwitchPhase();
}

void ATC_Player::PlayCard(ATC_Card* InCard, ATC_Slot* InSlot)
{
	//ATC_Card* NewCard = GetWorld()->SpawnActor<ATC_Card>(Card->GetClass(), FVector(Slot->GetActorLocation().X, Slot->GetActorLocation().Y, Slot->GetActorLocation().Z + 1), Slot->GetActorRotation());
	/*AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);

	TC_ActionsSystem::PlayCard(GameManager->GetCurrentGameState(), Card, Slot);*/

	if (!InCard || !InSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Parametre invalide (carte ou slot)."));
		return;
	}

	// Cr�e une action PlayCard
	FAIActions PlayAction(EActionType::PlayCard);
	PlayAction.CardInHand = InCard;
	PlayAction.PlayingSlot = InSlot;
	PlayAction.CardinHandIndex = _playerHand.Find(InCard);

	PlayAction.BoardSlotIndex = InSlot->GetSlotBoardSlot()->GetBoardSlotBoard()->GetBoardSlots().Find(InSlot->GetSlotBoardSlot());
	PlayAction.BoardSlotCardIndex = InSlot->GetSlotBoardSlot()->GetBoardSlotSlots().Find(InSlot);

	InSlot->SetSlotCard(InCard);
	InCard->SetSlot(InSlot);

	UE_LOG(LogTemp, Warning, TEXT("la carte %s "), *InCard->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Place at slot %s "), *InSlot->GetName());
	UE_LOG(LogTemp, Warning, TEXT("so Slot have card %s "), *InSlot->GetSlotCard()->GetName());
	// R�cup�re le GameManager actif
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayCard: GameManager introuvable."));
		return;
	}

	// Applique l'action au GameState actuel
	GameManager->GetCurrentGameState().ApplyAction(PlayAction);
	RemoveCardFromHand(InCard);
}

void ATC_Player::MoveCard(ATC_Card* InCard, ATC_Slot* InSlot)
{
	if (!InCard || !InSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveCard: Parametre invalide (carte ou slot)."));
		return;
	}

	FAIActions MoveAction(EActionType::MoveCard);
	MoveAction.CardInHand = InCard;
	MoveAction.PlayingSlot = InSlot;
	//Relatif � Card (Origine)
	MoveAction.BoardSlotIndex = InCard->GetSlot()->GetSlotBoardSlot()->GetBoardSlotBoard()->GetBoardSlots().Find(InCard->GetSlot()->GetSlotBoardSlot());
	MoveAction.BoardSlotCardIndex = InCard->GetSlot()->GetSlotBoardSlot()->GetBoardSlotSlots().Find(InCard->GetSlot());
	//Relatif � Slot (Destination)
	MoveAction.DestinationBoardSlotIndex = InSlot->GetSlotBoardSlot()->GetBoardSlotBoard()->GetBoardSlots().Find(InSlot->GetSlotBoardSlot());
	MoveAction.DestinationBoardSlotCardIndex = InSlot->GetSlotBoardSlot()->GetBoardSlotSlots().Find(InSlot);

	// R�cup�re le GameManager actif
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayCard: GameManager introuvable."));
		return;
	}

	//Appliquer l'action au GameState actuel
	GameManager->GetCurrentGameState().ApplyAction(MoveAction);
}

void ATC_Player::SwapCard(ATC_Card* InCardOne, ATC_Card* InCardTwo)
{
}

void ATC_Player::ActivateStateTransform(bool on, FTransform goal)
{
	if (!_canUseTransformTransition) return;
	_isTransformTransitionOn = on;
	if (!_isTransformTransitionOn) return;

	//_transformTransitionTimerGoal = timerGoal;
	//if (resetTimer)
	//	_transformTransitionTimer = 0;

	_transformTransitionGoal = goal;
}

void ATC_Player::TickStateTransform(float dt)
{
	FVector newPos = FMath::VInterpTo(GetActorLocation(), _transformTransitionGoal.GetLocation(), dt, 2);
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), _transformTransitionGoal.Rotator(), dt, 2);
	FVector newScale = FMath::VInterpTo(GetActorScale3D(), _transformTransitionGoal.GetScale3D(), dt, 2);

	SetActorLocationAndRotation(newPos, newRot);
	SetActorScale3D(newScale);

	_transformTransitionTimer += dt;
	if (GetTransform().Equals(_transformTransitionGoal))
		ActivateStateTransform(false, FTransform::Identity);
}

void ATC_Player::SwitchTransformTransition()
{
	_canUseTransformTransition = not _canUseTransformTransition;
	if (_isTransformTransitionOn && !_canUseTransformTransition)
	{
		_isTransformTransitionOn = false;
		SetActorLocationAndRotation(_transformTransitionGoal.GetLocation(), _transformTransitionGoal.Rotator());
		SetActorScale3D(_transformTransitionGoal.GetScale3D());
	}
}

void ATC_Player::AddCardToWaitingTargetList(ATC_Card* card)
{
	_cardsWaitingTarget.Add(card);
}

bool ATC_Player::RemoveCardToWaitingTargetList(ATC_Card* card)
{
	return (bool)_cardsWaitingTarget.Remove(card);
}

bool ATC_Player::CanPlaceCardOnSlot(ATC_Card* Card, ATC_Slot* Slot)
{
	if (!Card || !Slot) return false;

	// Créer une instance du vérificateur de conditions
	UTC_CardCondition* ConditionChecker = NewObject<UTC_CardCondition>();

	// Appelle les conditions centralisées
	return ConditionChecker->IsValidForCard(Card, Slot);
}