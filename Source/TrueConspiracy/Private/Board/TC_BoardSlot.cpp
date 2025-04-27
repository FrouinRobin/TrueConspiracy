// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardSlot.h"
#include "Board/TC_Slot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"


ATC_BoardSlot::ATC_BoardSlot()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = this->GetRootComponent();

	MainAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotOneAnchor"));
	RootComponent = MainAnchor;
	
	SlotOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotOneAnchor"));
	SlotOneAnchor->SetupAttachment(MainAnchor);

	SlotTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotTwoAnchor"));
	SlotTwoAnchor->SetupAttachment(MainAnchor);

	SlotThreeAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotThreeAnchor"));
	SlotThreeAnchor->SetupAttachment(MainAnchor);

	SlotFourAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("SlotFourAnchor"));
	SlotFourAnchor->SetupAttachment(MainAnchor);
}


void ATC_BoardSlot::BeginPlay()
{
	Super::BeginPlay(); 
}

ATC_Board* ATC_BoardSlot::GetBoardSlotBoard()
{
	return _boardSlotBoard;
}

TArray<ATC_Slot*>& ATC_BoardSlot::GetBoardSlotSlots()
{
	return _boardSlotSlots;
}

ATC_BoardSlot* ATC_BoardSlot::GetBoardSlotOppositeBoard()
{
	return _boardSlotOppositeBoard;
}

void ATC_BoardSlot::SetBoardSlotBoard(ATC_Board* newBoard)
{
	_boardSlotBoard = newBoard;
}

void ATC_BoardSlot::SetBoardSlotOppositeBoard(ATC_BoardSlot* newOppositeBoard)
{
	_boardSlotOppositeBoard = newOppositeBoard;
}

void ATC_BoardSlot::Init()
{
	
	for (ATC_Slot* Slot : _boardSlotSlots)
	{
		Slot->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Slot->SetSlotBoardSlot(this);
		Slot->Init();
	}
}

void ATC_BoardSlot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	///*ANCHOR*/
	//DOREPLIFETIME(ATC_BoardSlot, MainAnchor);
	//DOREPLIFETIME(ATC_BoardSlot, SlotOneAnchor);
	//DOREPLIFETIME(ATC_BoardSlot, SlotTwoAnchor);
	//DOREPLIFETIME(ATC_BoardSlot, SlotThreeAnchor);
	//DOREPLIFETIME(ATC_BoardSlot, SlotFourAnchor);

	///*DATA*/
	DOREPLIFETIME(ATC_BoardSlot, _boardSlotBoard);
	DOREPLIFETIME(ATC_BoardSlot, _boardSlotOppositeBoard);
	//DOREPLIFETIME(ATC_BoardSlot, _boardSlotSlots);
	//DOREPLIFETIME(ATC_BoardSlot, _cardMesh);
}
