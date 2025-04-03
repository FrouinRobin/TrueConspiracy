// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_Player.h"
#include "Camera/CameraComponent.h"
#include <Components/CapsuleComponent.h>
#include <TC_Face.h>
#include <Components/SphereComponent.h>

// Sets default values
ATC_Player::ATC_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	_playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	_playerCamera->SetupAttachment(RootComponent);
	_playerCamera->bUsePawnControlRotation = false;

	_cardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CardAnchor"));
	_cardAnchor->SetupAttachment(_playerCamera);
	_cardAnchor->SetRelativeLocation(FVector(150, 0, -120));
}

ATC_Card* ATC_Player::GetCardFromDeckByName(FString name, bool checkAllFaces)
{
	for (ATC_Card* card : GetDeck())
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

ATC_Card* ATC_Player::GetCardFromDeckById(ETC_CardID id)
{
	for (ATC_Card* card : GetDeck())
	{
		if (card->GetCardID() == id)
			return card;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
	return nullptr;
}

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

void ATC_Player::SetDeck(TArray<ATC_Card*> newDeck)
{
	_playerDeck = newDeck;
}

TArray<ATC_Card*> ATC_Player::GetDeck()
{
	return _playerDeck;
}

bool ATC_Player::AddCardToDeck(ATC_Card* card)
{
	_playerHand.Add(card);
	card->AttachToComponent(_cardAnchor, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true));
	card->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));

	ShowHandOnCamera();
	return true;
}

bool ATC_Player::AddCardToHand(ATC_Card* card)
{
	_playerHand.Add(card);

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
		card->SetActorRelativeRotation(FRotator(69, 0, 0));
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

