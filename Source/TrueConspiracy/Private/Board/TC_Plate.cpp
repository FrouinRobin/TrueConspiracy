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

TArray<ATC_LandCardSlot*> ATC_Plate::GetLandCardSlots()
{
	return _landCardSlots;
}

ATC_LandCardSlot* ATC_Plate::GetLandCardSlotAtIndex(int index)
{
	return _landCardSlots[index];
}

TArray<ATC_Board*> ATC_Plate::GetPlateBoard()
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
	
	_plateBoard[0]->SetBoardPlayer(_playerOne);
	_playerOne->SetPlayerBoard(_plateBoard[0]);

	_plateBoard[1]->SetBoardPlayer(_playerTwo);
	_playerTwo->SetPlayerBoard(_plateBoard[1]);

	_plateBoard[0]->Init();
	_plateBoard[1]->Init();

	//GetLandCardSlots()[0]->GetLandCardBordSlot().Add(GetBoardByPlayer(_playerOne)->GetBoardSlots()[0]);
	//GetLandCardSlots()[0]->GetLandCardBordSlot().Add(GetBoardByPlayer(_playerTwo)->GetBoardSlots()[2]);
	//GetLandCardSlots()[1]->GetLandCardBordSlot().Add(GetBoardByPlayer(_playerOne)->GetBoardSlots()[1]);
	//GetLandCardSlots()[1]->GetLandCardBordSlot().Add(GetBoardByPlayer(_playerTwo)->GetBoardSlots()[1]);
	//GetLandCardSlots()[2]->GetLandCardBordSlot().Add(GetBoardByPlayer(_playerOne)->GetBoardSlots()[2]);
	//GetLandCardSlots()[2]->GetLandCardBordSlot().Add(GetBoardByPlayer(_playerTwo)->GetBoardSlots()[0]);

	for (ATC_LandCardSlot* LandCardSlot: _landCardSlots)
	{
		LandCardSlot->Init();
	}

	
}

