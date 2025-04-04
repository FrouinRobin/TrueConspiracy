// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Plate.h"
#include "TC_Player.h"

// Sets default values
ATC_Plate::ATC_Plate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	RootComponent = PlateMesh;
	BoardPlayerOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardPlayerOneAnchor"));
	BoardPlayerOneAnchor->SetupAttachment(PlateMesh);
	BoardPlayerTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardPlayerTwoAnchor"));
	BoardPlayerTwoAnchor->SetupAttachment(PlateMesh);
	LandCardSlotOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardSlotOneAnchor"));
	LandCardSlotOneAnchor->SetupAttachment(PlateMesh);
	LandCardSlotTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardSlotTwoAnchor"));
	LandCardSlotTwoAnchor->SetupAttachment(PlateMesh);
	LandCardSlotThreeAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardSlotThreeAnchor"));
	LandCardSlotThreeAnchor->SetupAttachment(PlateMesh);
}

// Called when the game starts or when spawned
void ATC_Plate::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void ATC_Plate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATC_Player* ATC_Plate::GetPlayerOne()
{
	return _playerOne;
}

ATC_Player* ATC_Plate::GetPlayerTwo()
{
	return _playerTwo;
}

ATC_Board* ATC_Plate::GetBoardPlayerOne()
{
	return _boardPlayerOne;
}

ATC_Board* ATC_Plate::GetBoardPlayerTwo()
{
	return _boardPlayerTwo;
}

TArray<ATC_LandCardSlot*> ATC_Plate::GetLandCardSlots()
{
	return _landCardSlots;
}

ATC_LandCardSlot* ATC_Plate::GetLandCardSlotAtIndex(int index)
{
	return _landCardSlots[index];
}


void ATC_Plate::SetPlayerOne(ATC_Player* newPlayerOne)
{
	_playerOne = newPlayerOne;
}

void ATC_Plate::SetPlayerTwo(ATC_Player* newPlayerTwo)
{
	_playerTwo = newPlayerTwo;
}

void ATC_Plate::SetBoardPlayerOne(ATC_Board* newBoardPlayerOne)
{
	_boardPlayerOne = newBoardPlayerOne;
}

void ATC_Plate::SetBoardPlayerTwo(ATC_Board* newBoardPlayerTwo)
{
	_boardPlayerTwo = newBoardPlayerTwo;
}

void ATC_Plate::Init()
{
	_boardPlayerOne = GetWorld()->SpawnActor<ATC_Board>(BoardPlayerOneAnchor->GetComponentLocation(), BoardPlayerOneAnchor->GetComponentRotation());
	_boardPlayerOne->SetBoardPlayer(GetPlayerOne());
	_boardPlayerTwo = GetWorld()->SpawnActor<ATC_Board>(BoardPlayerTwoAnchor->GetComponentLocation(), BoardPlayerOneAnchor->GetComponentRotation());
	_boardPlayerTwo->SetBoardPlayer(GetPlayerTwo());
	_landCardSlots.Add(GetWorld()->SpawnActor<ATC_LandCardSlot>(LandCardSlotOneAnchor->GetComponentLocation(), LandCardSlotOneAnchor->GetComponentRotation()));
	_landCardSlots.Add(GetWorld()->SpawnActor<ATC_LandCardSlot>(LandCardSlotTwoAnchor->GetComponentLocation(), LandCardSlotTwoAnchor->GetComponentRotation()));
	_landCardSlots.Add(GetWorld()->SpawnActor<ATC_LandCardSlot>(LandCardSlotThreeAnchor->GetComponentLocation(), LandCardSlotThreeAnchor->GetComponentRotation()));
	for (int i = 0; i < _landCardSlots.Num(); i++)
	{
		_landCardSlots[i]->Init();
		_landCardSlots[i]->SetSlotCardType(ETC_CardType::LandCard);
	}
	_boardPlayerOne->Init();
	_boardPlayerTwo->Init();
}

