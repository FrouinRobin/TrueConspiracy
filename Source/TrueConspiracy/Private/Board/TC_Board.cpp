// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Board.h"
#include "TC_Card.h"
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
		FActorSpawnParameters SpawnParams;
		ATC_BoardZone* NewBoardZone = GetWorld()->SpawnActor<ATC_BoardZone>(ATC_BoardZone::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (NewBoardZone)
		{
			NewBoardZone->AttachToComponent(_boardZonesRoot, FAttachmentTransformRules::KeepRelativeTransform);
			BoardZones.Add(NewBoardZone);
			UE_LOG(LogTemp, Warning, TEXT("BoardZone %d Created"), i);
		}
	}

	// Création des 6 FightZones (3 par joueur)
	for (int i = 0; i < 6; i++)
	{
		FActorSpawnParameters SpawnParams;
		ATC_FightZone* NewFightZone = GetWorld()->SpawnActor<ATC_FightZone>(ATC_FightZone::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (NewFightZone)
		{
			NewFightZone->AttachToComponent(_fightZonesRoot, FAttachmentTransformRules::KeepRelativeTransform);
			FightZones.Add(NewFightZone);
			UE_LOG(LogTemp, Warning, TEXT("FightZone %d Created"), i);
		}
	}

	// Création des 6 LandCards (1 par FightZone)
	for (int i = 0; i < 6; i++)
	{
		FActorSpawnParameters SpawnParams;
		ATC_LandCardSlot* NewLandCard = GetWorld()->SpawnActor<ATC_LandCardSlot>(ATC_LandCardSlot::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (NewLandCard)
		{
			NewLandCard->AttachToComponent(_fightZonesRoot, FAttachmentTransformRules::KeepRelativeTransform);
			LandCards.Add(NewLandCard);
			UE_LOG(LogTemp, Warning, TEXT("LandCard %d Created"), i);
		}
	}

	// Création des 6 BoardSlots (3 par joueur)
	for (int i = 0; i < 6; i++)
	{
		FActorSpawnParameters SpawnParams;
		ATC_BoardSlot* NewBoardSlot = GetWorld()->SpawnActor<ATC_BoardSlot>(ATC_BoardSlot::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (NewBoardSlot)
		{
			NewBoardSlot->AttachToComponent(_slotsRoot, FAttachmentTransformRules::KeepRelativeTransform);
			BoardSlots.Add(NewBoardSlot);
			UE_LOG(LogTemp, Warning, TEXT("BoardSlot %d Created"), i);
		}
	}

	// Création des 24 Slots (4 par BoardSlot)
	for (int i = 0; i < 24; i++)
	{
		FActorSpawnParameters SpawnParams;
		ATC_Slot* NewSlot = GetWorld()->SpawnActor<ATC_Slot>(ATC_Slot::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (NewSlot)
		{
			NewSlot->AttachToComponent(_slotsRoot, FAttachmentTransformRules::KeepRelativeTransform);
			Slots.Add(NewSlot);
			UE_LOG(LogTemp, Warning, TEXT("Slot %d Created"), i);
		}
	}
}


bool ATC_Board::PlaceCard(ATC_Card* Card, ATC_Slot* Slot)
{
	if (!Card || !Slot)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Card or Slot!"));
		return false;
	}

	// Vérifier si le slot est vide
	if (Slot->HasCard())
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot is already occupied!"));
		return false;
	}

	// Placer la carte dans le slot
	Slot->SetCard(Card);
	UE_LOG(LogTemp, Warning, TEXT("Card placed successfully!"));

	// Appeler l'événement OnCardPlace sur la carte
	Card->OnCardPlace();

	return true;
}
