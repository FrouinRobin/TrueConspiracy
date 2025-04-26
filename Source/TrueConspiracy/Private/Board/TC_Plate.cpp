// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Plate.h"
#include "TC_Player.h"


// Sets default values
ATC_Plate::ATC_Plate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = SceneComponent;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(RootComponent);

	BoardPlayerOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardPlayerOneAnchor"));

	BoardPlayerTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardPlayerTwoAnchor"));

	LandCardSlotOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardSlotOneAnchor"));

	LandCardSlotTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardSlotTwoAnchor"));

	LandCardSlotThreeAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardSlotThreeAnchor"));

}

// Called when the game starts or when spawned
void ATC_Plate::BeginPlay()
{
	Super::BeginPlay();

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

ATC_Board* ATC_Plate::GetBoardByPlayer(ATC_Player* PlayerRef)
{
	ATC_Board* PlayerBoard = nullptr;
	for (ATC_Board* Board : _plateBoard)
	{
		if (Board->GetBoardPlayer() == PlayerRef)
		{
			return Board;
		}
		else
		{
			PlayerBoard = nullptr;
		}
	}
	return PlayerBoard;
}

TArray<ATC_LandCardSlot*>& ATC_Plate::GetLandCardSlots()
{
	return _landCardSlots;
}

ATC_LandCardSlot* ATC_Plate::GetLandCardSlotAtIndex(int index)
{
	return _landCardSlots[index];
}

TArray<ATC_Board*>& ATC_Plate::GetPlateBoard()
{
	return _plateBoard;
}


void ATC_Plate::SetPlayerOne(ATC_Player* newPlayerOne)
{
	_playerOne = newPlayerOne;
}

void ATC_Plate::SetPlayerTwo(ATC_Player* newPlayerTwo)
{
	_playerTwo = newPlayerTwo;
}

void ATC_Plate::Init()
{
	_plateBoard.Add(GetWorld()->SpawnActor<ATC_Board>(BoardBluePrint, BoardPlayerOneAnchor->GetComponentLocation(), BoardPlayerOneAnchor->GetComponentRotation()));
	_plateBoard[0]->SetBoardPlayer(_playerOne);
	_plateBoard[0]->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	
	_playerOne->SetPlayerBoard(_plateBoard[0]);
	_plateBoard.Add(GetWorld()->SpawnActor<ATC_Board>(BoardBluePrint, BoardPlayerTwoAnchor->GetComponentLocation(), BoardPlayerTwoAnchor->GetComponentRotation()));
	_plateBoard[1]->SetBoardPlayer(_playerTwo);
	_plateBoard[1]->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	
	_playerTwo->SetPlayerBoard(_plateBoard[1]);

	_landCardSlots.Add(GetWorld()->SpawnActor<ATC_LandCardSlot>(LandCardSlotBluePrint,LandCardSlotOneAnchor->GetComponentLocation(), LandCardSlotOneAnchor->GetComponentRotation()));
	_landCardSlots.Add(GetWorld()->SpawnActor<ATC_LandCardSlot>(LandCardSlotBluePrint,LandCardSlotTwoAnchor->GetComponentLocation(), LandCardSlotTwoAnchor->GetComponentRotation()));
	_landCardSlots.Add(GetWorld()->SpawnActor<ATC_LandCardSlot>(LandCardSlotBluePrint,LandCardSlotThreeAnchor->GetComponentLocation(), LandCardSlotThreeAnchor->GetComponentRotation()));
	_plateBoard[0]->Init();
	_plateBoard[1]->Init();
	_landCardSlots[0]->GetLandCardBordSlot().Add(_plateBoard[0]->GetBoardSlots()[0]);
	_landCardSlots[0]->GetLandCardBordSlot().Add(_plateBoard[1]->GetBoardSlots()[2]);
	_landCardSlots[1]->GetLandCardBordSlot().Add(_plateBoard[0]->GetBoardSlots()[1]);
	_landCardSlots[1]->GetLandCardBordSlot().Add(_plateBoard[1]->GetBoardSlots()[1]);
	_landCardSlots[2]->GetLandCardBordSlot().Add(_plateBoard[0]->GetBoardSlots()[2]);
	_landCardSlots[2]->GetLandCardBordSlot().Add(_plateBoard[1]->GetBoardSlots()[0]);
	_plateBoard[0]->GetBoardSlots()[1];

	for (ATC_LandCardSlot* LandCardSlot: _landCardSlots)
	{
		LandCardSlot->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		LandCardSlot->LandCardInit();
	}

	
}

