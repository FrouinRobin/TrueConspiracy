// Fill out your copyright notice in the Description page of Project Settings.

#include "Board/TC_Board.h"
#include "Board/TC_BoardZone.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_LandCardSlot.h"
#include "Board/TC_Slot.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

ATC_Board::ATC_Board()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	LayoutRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LayoutRoot"));
	LayoutRoot->SetupAttachment(RootComponent);

	P0_ZoneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("P0_ZoneAnchor"));
	P0_ZoneAnchor->SetupAttachment(LayoutRoot);

	P1_ZoneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("P1_ZoneAnchor"));
	P1_ZoneAnchor->SetupAttachment(LayoutRoot);

	for (int32 i = 0; i < 3; i++)
	{
		FName AnchorName = FName(*FString::Printf(TEXT("LandAnchor_%d"), i));
		USceneComponent* LandAnchor = CreateDefaultSubobject<USceneComponent>(AnchorName);
		LandAnchor->SetupAttachment(LayoutRoot);
		LandAnchors.Add(LandAnchor);
	}
}

void ATC_Board::BeginPlay()
{
	Super::BeginPlay();
	InitializeBoard();
}

void ATC_Board::InitializeBoard()
{
	UWorld* World = GetWorld();
	if (!World || !BoardZoneClass || !BoardSlotClass || !SlotClass || !LandSlotClass) return;

	for (int32 PlayerIndex = 0; PlayerIndex < 2; PlayerIndex++)
	{
		USceneComponent* Anchor = (PlayerIndex == 0) ? P0_ZoneAnchor : P1_ZoneAnchor;
		FVector ZoneLocation = Anchor->GetComponentLocation();
		FRotator ZoneRotation = (PlayerIndex == 1) ? FRotator(0.f, 180.f, 0.f) : FRotator::ZeroRotator;

		FActorSpawnParameters ZoneParams;
		ATC_BoardZone* NewZone = World->SpawnActor<ATC_BoardZone>(BoardZoneClass, ZoneLocation, ZoneRotation, ZoneParams);
		if (!NewZone) continue;

		NewZone->OwnerPlayerIndex = PlayerIndex;
		NewZone->AttachToComponent(Anchor, FAttachmentTransformRules::KeepWorldTransform);
		PlayerZones.Add(NewZone);

		NewZone->InitializeBoardSlots(BoardSlotClass, SlotClass);
	}

	// Spawn 3 LandSlots à partir des anchors
	for (int32 i = 0; i < 3 && i < LandAnchors.Num(); i++)
	{
		FVector Location = LandAnchors[i]->GetComponentLocation();
		FActorSpawnParameters Params;

		ATC_LandCardSlot* NewLand = World->SpawnActor<ATC_LandCardSlot>(LandSlotClass, Location, FRotator::ZeroRotator, Params);
		if (!NewLand) continue;

		NewLand->AttachToComponent(LandAnchors[i], FAttachmentTransformRules::KeepWorldTransform);
		SharedLands.Add(NewLand);
	}
}

bool ATC_Board::TryPlaceCard(APlayerController* Player, ATC_Card* Card, ATC_Slot* Slot)
{
	if (!Card || !Slot || Slot->HasCard())
		return false;

	Slot->SetCard(Card);
	//Card->OnCardPlace();
	return true;
}