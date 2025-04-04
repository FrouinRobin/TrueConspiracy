// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardSlot.h"
#include "Board/TC_Slot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ATC_BoardSlot::ATC_BoardSlot()
{
	PrimaryActorTick.bCanEverTick = true;
	SlotOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotOneAnchor"));
	SlotTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotTwoAnchor"));
	SlotThreeAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotThreeAnchor"));
	SlotFourAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotFourAnchor"));
}

void ATC_BoardSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

ATC_Board* ATC_BoardSlot::GetBoardSlotBoard()
{
	return _boardSlotBoard;
}

TArray<ATC_Slot*> ATC_BoardSlot::GetBoardSlotSlots()
{
	return _boardSlotSlots;
}

void ATC_BoardSlot::SetBoardSlotBoard(ATC_Board* newBoard)
{
	_boardSlotBoard = newBoard;
}

void ATC_BoardSlot::Init()
{
	_boardSlotSlots.Add(GetWorld()->SpawnActor<ATC_Slot>(SlotOneAnchor->GetComponentLocation(), SlotOneAnchor->GetComponentRotation()));
	_boardSlotSlots.Add(GetWorld()->SpawnActor<ATC_Slot>(SlotTwoAnchor->GetComponentLocation(), SlotTwoAnchor->GetComponentRotation()));
	_boardSlotSlots.Add(GetWorld()->SpawnActor<ATC_Slot>(SlotThreeAnchor->GetComponentLocation(), SlotThreeAnchor->GetComponentRotation()));
	_boardSlotSlots.Add(GetWorld()->SpawnActor<ATC_Slot>(SlotFourAnchor->GetComponentLocation(), SlotFourAnchor->GetComponentRotation()));
	for (ATC_Slot* Slot : _boardSlotSlots)
	{
		Slot->SetSlotBoardSlot(this);
		Slot->Init();
	}
}

