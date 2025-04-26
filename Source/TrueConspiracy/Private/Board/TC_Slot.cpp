// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Slot.h"
#include "Cards/TC_Card.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include <Net/UnrealNetwork.h>

ATC_Slot::ATC_Slot()
{
	//bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = sceneComponent;

	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlotVisual"));
	visualMesh->SetupAttachment(RootComponent);

	// Set the mesh to a basic cube (engine default)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/TrueConspiracy/FBX/Card/CardFBX.CardFBX"));
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
		UE_LOG(LogTemp, Error, TEXT("Slot is Occupied"));
		return true;
	}
	else {
		return false;
	}
}

ATC_Card* ATC_Slot::GetSlotCard() {
	return _slotCard;
}
ATC_BoardSlot* ATC_Slot::GetSlotBoardSlot()
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

void ATC_Slot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	///*ANCHOR*/
	DOREPLIFETIME(ATC_Slot, sceneComponent);
	

	///*DATA*/
	DOREPLIFETIME(ATC_Slot, _slotCardType);
	DOREPLIFETIME(ATC_Slot, _slotBoardSlot);
	DOREPLIFETIME(ATC_Slot, _slotCard);
}

