// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardSlot.h"
#include "Board/TC_Slot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"


ATC_BoardSlot::ATC_BoardSlot()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (MeshAsset.Succeeded())
	{
		_cardMesh = MeshAsset.Object;
	}

	SlotOneAnchor = CreateSlotAnchorWithMesh(TEXT("SlotOneAnchor"), FVector(-25.f, -50.f, 0.f));
	SlotTwoAnchor = CreateSlotAnchorWithMesh(TEXT("SlotTwoAnchor"), FVector(25.f, -50.f, 0.f));
	SlotThreeAnchor = CreateSlotAnchorWithMesh(TEXT("SlotThreeAnchor"), FVector(-25.f, 50.f, 0.f));
	SlotFourAnchor = CreateSlotAnchorWithMesh(TEXT("SlotFourAnchor"), FVector(25.f, 50.f, 0.f));
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

USceneComponent* ATC_BoardSlot::CreateSlotAnchorWithMesh(FName AnchorName, FVector RelativeLocation)
{
	USceneComponent* Anchor = CreateDefaultSubobject<USceneComponent>(AnchorName);
	Anchor->SetupAttachment(RootComponent);
	Anchor->SetRelativeLocation(RelativeLocation);

	UStaticMeshComponent* VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("%s_Mesh"), *AnchorName.ToString()));
	VisualMesh->SetupAttachment(Anchor);
	VisualMesh->SetRelativeLocation(FVector::ZeroVector);
	VisualMesh->SetWorldScale3D(FVector(0.4f, 0.8f, 0.02f));
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (_cardMesh)
	{
		VisualMesh->SetStaticMesh(_cardMesh);
	}

	return Anchor;
}
