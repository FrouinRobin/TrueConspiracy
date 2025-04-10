// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Slot.h"
#include "Cards/TC_Card.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ATC_Slot::ATC_Slot()
{
	PrimaryActorTick.bCanEverTick = false;

	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlotVisual"));
	RootComponent = visualMesh;

	// Set the mesh to a basic cube (engine default)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		visualMesh->SetStaticMesh(CubeMesh.Object);
	}

	// Set the relative scale of the mesh
	visualMesh->SetRelativeScale3D(FVector(0.2f, 0.3f, 0.01f));
}

bool ATC_Slot::HasCard()
{
	if (_slotCard != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

ATC_Card* ATC_Slot::GetSlotCard() {
	return _slotCard;
}
ATC_BoardSlot* ATC_Slot::GetSlaotBoardSlot()
{
	return _slotBoardSlot;
}
ETC_CardType ATC_Slot::GetSlotCardType()
{
	return _slotCardType;
}
void ATC_Slot::SetSlotCard(ATC_Card* newSlotCard)
{
	ATC_Card* card = GetSlotCard();
	if (card)
		card->Destroy();
	_slotCard = newSlotCard;
}

void ATC_Slot::SetSlotBoardSlot(ATC_BoardSlot* newSlotBoardSlot)
{
	_slotBoardSlot = newSlotBoardSlot;
}

void ATC_Slot::SetSlotCardType(ETC_CardType newSlotCardType)
{
	_slotCardType = newSlotCardType;
}

void ATC_Slot::Init()
{
}

