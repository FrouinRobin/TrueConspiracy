// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Board.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

ATC_Board::ATC_Board()
{
	PrimaryActorTick.bCanEverTick = true;


	// Créer la racine du Board
	_boardRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BoardRoot"));
	RootComponent = _boardRoot;

	// Créer les repères pour organiser les zones et slots
	_boardZonesRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BoardZonesRoot"));
	_boardZonesRoot->SetupAttachment(_boardRoot);

	_fightZonesRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FightZonesRoot"));
	_fightZonesRoot->SetupAttachment(_boardRoot);

	_slotsRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SlotsRoot"));
	_slotsRoot->SetupAttachment(_boardRoot);

}

void ATC_Board::BeginPlay()
{
	Super::BeginPlay();
	InitializeBoard();
}

void ATC_Board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATC_Board::InitializeBoard()
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing Board..."));

	// Création des 2 BoardZones (1 par joueur)
	for (int i = 0; i < 2; i++)
	{
		UTC_BoardZone* T_BoardZone = NewObject<UTC_BoardZone>(this);
		if (T_BoardZone)
		{
			BoardZones.Add(T_BoardZone);
			//T_BoardZone->AttachToComponent(_boardZonesRoot, FAttachmentTransformRules::KeepRelativeTransform);
			UE_LOG(LogTemp, Warning, TEXT("BoardZone %d Created"), i);
		}
	}

	// Création des 6 FightZones (3 par joueur)
	for (int i = 0; i < 6; i++)
	{
		UTC_FightZone* T_FightZone = NewObject<UTC_FightZone>(this);
		if (T_FightZone)
		{
			FightZones.Add(T_FightZone);
			UE_LOG(LogTemp, Warning, TEXT("FightZone %d Created"), i);
		}
	}

	// Création des 6 LandCards (1 par FightZone)
	for (int i = 0; i < 6; i++)
	{
		UTC_LandCard* T_LandCard = NewObject<UTC_LandCard>(this);
		if (T_LandCard)
		{
			LandCards.Add(T_LandCard);
			UE_LOG(LogTemp, Warning, TEXT("LandCard %d Created"), i);
		}
	}

	// Création des 6 BoardSlots (3 par joueur)
	for (int i = 0; i < 6; i++)
	{
		UTC_BoardSlot* T_BoardSlot = NewObject<UTC_BoardSlot>(this);
		if (T_BoardSlot)
		{
			BoardSlots.Add(T_BoardSlot);
			UE_LOG(LogTemp, Warning, TEXT("BoardSlot %d Created"), i);
		}
	}

	// Création des 24 Slots (4 par BoardSlot)
	for (int i = 0; i < 24; i++)
	{
		UTC_Slot* T_Slot = NewObject<UTC_Slot>(this);
		if (T_Slot)
		{
			Slots.Add(T_Slot);
			UE_LOG(LogTemp, Warning, TEXT("Slot %d Created"), i);
		}
	}
}

bool ATC_Board::PlaceCard(ATC_Card* Card, UTC_Slot* Slot)
{
	if (!Card || !Slot)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Card or Slot!"));
		return false;
	}

	// Vérifier si le slot est vide
	if (Slot->HasCard)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot is already occupied!"));
		return false;
	}

	// Placer la carte dans le slot
	Slot->SetCard(Card);
	Slot->HasCard = true;
	UE_LOG(LogTemp, Warning, TEXT("Card placed successfully!"));

	// Appeler l'evenement OnCardPlace sur la carte
	Card->OnCardPlace();

	return true;
}
