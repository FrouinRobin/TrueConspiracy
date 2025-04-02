// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Slot.h"

ATC_Slot::ATC_Slot()
{
	PrimaryActorTick.bCanEverTick = false;

	SlotRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SlotRoot"));
	RootComponent = SlotRoot;

	SlotState = ETC_SlotState::Empty;
	_card = nullptr;

	OnActorBeginOverlap.AddDynamic(this, &ATC_Slot::OnSlotOverlap);
}

ATC_Card* ATC_Slot::GetCard()
{
	return _card;
}

void ATC_Slot::SetCard(ATC_Card* NewCard)
{
	_card = NewCard;
	SlotState = (_card) ? ETC_SlotState::Occupied : ETC_SlotState::Empty;
}

bool ATC_Slot::HasCard()
{
	return _card != nullptr;
}

void ATC_Slot::OnSlotOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Gérer l'overlap ici
}