// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_Player.h"
#include "Camera/CameraComponent.h"
#include <Components/CapsuleComponent.h>
#include <Cards/Faces/TC_Face.h>
#include <Components/SphereComponent.h>
#include <TC_GameInstance.h>
#include "TC_AIActions.h"
#include <TC_ActionsSystem.h>
#include <Kismet/GameplayStatics.h>
#include "TC_GameManager.h"
#include "Board/TC_Slot.h"
#include "Board/TC_Board.h"

// Sets default values
ATC_Player::ATC_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	_playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	_playerCamera->SetupAttachment(RootComponent);
	_playerCamera->bUsePawnControlRotation = true;

	_cardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CardAnchor"));
	_cardAnchor->SetupAttachment(_playerCamera);
	_cardAnchor->SetRelativeLocation(FVector(150, 0, -120));
}

//ATC_Card* ATC_Player::GetCardFromDeckByName(FString name, bool checkAllFaces)
//{
//	for (TSubclassOf<ATC_Card> card : GetDeck())
//	{
//		if (!checkAllFaces) {
//			UTC_Face* cardFace = card->GetCardCurrentFace();
//
//			if (/*cardFace->name == name */ false) // TODO: See how IDs and names will be implemented
//				return card;
//		}
//		else
//		{
//			// Why is there a need for more than two faces I don't know but just in case
//			TArray<UTC_Face*> cardFaces = card->GetCardFaceList();
//
//			for (auto face : cardFaces)
//			{
//				if (/*face->name == name */ false) // TODO: Ditto
//					return card;
//			}
//		}
//	}
//	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
//	return nullptr;
//}

//ATC_Card* ATC_Player::GetCardFromDeckById(ETC_CardID id)
//{
//	for (TSubclassOf<ATC_Card> card : GetDeck())
//	{
//		if (card->GetCardID() == id)
//			return card;
//	}
//	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
//	return nullptr;
//}

ATC_Card* ATC_Player::GetCardFromHandByName(FString name, bool checkAllFaces)
{
	for (ATC_Card* card : GetHand())
	{
		if (!checkAllFaces) {
			UTC_Face* cardFace = card->GetCardCurrentFace();

			if (/*cardFace->name == name */ false) // TODO: See how IDs and names will be implemented
				return card;
		}
		else
		{
			// Why is there a need for more than two faces I don't know but just in case
			TArray<UTC_Face*> cardFaces = card->GetCardFaceList();

			for (auto face : cardFaces)
			{
				if (/*face->name == name */ false) // TODO: Ditto
					return card;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
	return nullptr;
}

ATC_Card* ATC_Player::GetCardFromHandById(ETC_CardID id)
{
	for (ATC_Card* card : GetHand())
	{
		if (card->GetCardID() == id)
			return card;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
	return nullptr;
}

ATC_Board* ATC_Player::GetPlayerBaord()
{
	return _playerBoard;
}

void ATC_Player::SetPlayerBoard(ATC_Board* newBoard)
{
	_playerBoard = newBoard;
}

void ATC_Player::SetDeck(TArray<TSubclassOf<ATC_Card>> newDeck)
{
	_playerDeck = newDeck;
}

TArray<TSubclassOf<ATC_Card>> ATC_Player::GetDeck()
{

	return _playerDeck;
	/*if (_playerDeck.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetDeck() did not return any card!"));
		return TArray<ATC_Card*>();
	}
	return _playerDeck;*/
}

bool ATC_Player::AddCardToHand(TSubclassOf<ATC_Card> card)
{
	
	ATC_Card* NewCard = GetWorld()->SpawnActor<ATC_Card>(card, _cardAnchor->GetComponentLocation(), _cardAnchor->GetComponentRotation());
	_playerHand.Add(NewCard);
	NewCard->AttachToComponent(_cardAnchor, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true));
	NewCard->CardAnchor->SetWorldRotation(FRotator(-69.f,180.f,0.f));

	ShowHandOnCamera();
	return true;
}

bool ATC_Player::AddCardToDeck(TSubclassOf<ATC_Card> card)
{
	_playerDeck.Add(card);

	return true;
}

void ATC_Player::SetHand(TArray<ATC_Card*> newDeck)
{
	_playerHand = newDeck;
}

TArray<ATC_Card*> ATC_Player::GetHand()
{
	return _playerHand;
}

void ATC_Player::SetPlayerMana(uint8 mana)
{
	_playerCurrentMana = mana;
}

uint8 ATC_Player::GetPlayerMana() const
{
	return _playerCurrentMana;
}

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
		if (_playerDeck.Num() % 2 == 0)
			base = FVector(0, -20, 0);

		float interval = ((float)i - ((float)_playerHand.Num() - 1) / 2) * 50;

		card->SetActorLocation(card->GetActorLocation() + base + FVector(0, 0, box.Y) + FVector(0, interval, 0));
	}
}

TArray<ATC_Card*> ATC_Player::GetAvailableCards()
{
	TArray<ATC_Card*> cards;
	for(auto card : GetHand())
	{
		if (card->GetCardCurrentMana() >= GetPlayerMana())
			cards.Add(card);
	}
	return cards;
}

bool ATC_Player::CanPlayAnyCard()
{
	return GetAvailableCards().Num() > 0;
}

bool ATC_Player::CanPlayCard(ATC_Card* card)
{
	return card->GetCardCurrentMana() >= GetPlayerMana();
}

// Called when the game starts or when spawned
void ATC_Player::BeginPlay()
{
	Super::BeginPlay();

	_playerCamera->SetRelativeRotation(FRotator(-90, 180, 0));
}

// Called every frame
void ATC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

uint8 ATC_Player::IncreaseManaLimit(uint8 value)
{
	_playerMaxMana += value;
	return _playerMaxMana;
}

uint8 ATC_Player::ChangeMana(uint8 value, bool allowOverflow)
{
	_playerCurrentMana += value;
	if (!allowOverflow && _playerCurrentMana > _playerMaxMana)
		_playerCurrentMana = _playerMaxMana;
	return _playerCurrentMana;
}

void ATC_Player::SetSelectedCard(ATC_Card* card)
{
	if (_selectedCard == card)
		return;

	ATC_Card* oldCard = _selectedCard;
	_selectedCard = card;

	OnSelectCard(card, oldCard);
}

ATC_Card* ATC_Player::GetSelectedCard()
{
	return _selectedCard;
}

void ATC_Player::SetPhaseState(ETC_PhaseState InPhaseState)
{
	_PhaseState = InPhaseState;
}

ETC_PhaseState ATC_Player::GetPhaseState() const
{
	return _PhaseState;
}

void ATC_Player::SetPlayerMaxMana(uint8 InMaxMana)
{
	_playerMaxMana = InMaxMana;
}

uint8 ATC_Player::GetPlayerMaxMana() const
{
	return _playerMaxMana;
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
void ATC_Player::PlayCard(ATC_Card* Card, ATC_Slot* Slot)
{
	//ATC_Card* NewCard = GetWorld()->SpawnActor<ATC_Card>(Card->GetClass(), FVector(Slot->GetActorLocation().X, Slot->GetActorLocation().Y, Slot->GetActorLocation().Z + 1), Slot->GetActorRotation());
	/*AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	
	TC_ActionsSystem::PlayCard(GameManager->GetCurrentGameState(), Card, Slot);*/

	if (!Card || !Slot)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Paramètre invalide (carte ou slot)."));
		return;
	}

	// Crée une action PlayCard
	FAIActions PlayAction(EActionType::PlayCard);
	PlayAction.CardInHand = Card;
	PlayAction.PlayingSlot = Slot;
	PlayAction.CardinHandIndex = _playerHand.Find(Card);

	PlayAction.BoardSlotIndex = Slot->GetSlaotBoardSlot()->GetBoardSlotBoard()->GetBoardSlots().Find(Slot->GetSlaotBoardSlot());
	PlayAction.BoardSlotCardIndex = Slot->GetSlaotBoardSlot()->GetBoardSlotSlots().Find(Slot);

	// Récupère le GameManager actif
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayCard: GameManager introuvable."));
		return;
	}

	// Applique l'action au GameState actuel
	GameManager->GetCurrentGameState().ApplyAction(PlayAction);
	
}

void ATC_Player::SwitchFace(ATC_Card* Card)
{
	Card->SwitchPhase();
}