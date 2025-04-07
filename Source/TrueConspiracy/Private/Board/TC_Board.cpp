// Fill out your copyright notice in the Description page of Project Settings.

#include "Board/TC_Board.h"
#include "TC_Player.h"
#include "Board/TC_Plate.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_DrawDeck.h"
#include "Board/TC_DiscardDeck.h"


ATC_Board::ATC_Board()
{
	PrimaryActorTick.bCanEverTick = false;


    MainAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("MainAnchor"));
    RootComponent = MainAnchor;
    
    BoardSlotOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotOneAnchor"));
    BoardSlotOneAnchor->SetupAttachment(MainAnchor);

    BoardSlotTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotTwoAnchor"));
    BoardSlotTwoAnchor->SetupAttachment(MainAnchor);


    BoardSlotThreeAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotThreeAnchor"));
    BoardSlotThreeAnchor->SetupAttachment(MainAnchor);


    BoardDrawAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardDrawAnchor"));
    BoardDrawAnchor->SetupAttachment(MainAnchor);


    BoardDiscardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardDiscardAnchor"));
    BoardDiscardAnchor->SetupAttachment(MainAnchor);


}

void ATC_Board::BeginPlay()
{
	Super::BeginPlay();
}

ATC_Plate* ATC_Board::GetBoardPlate()
{
    return _boardPlate;
}

ATC_Player* ATC_Board::GetBoardPlayer()
{
	return _boardPlayer;
}

TArray<ATC_BoardSlot*> ATC_Board::GetBoardSlots()
{
	return _boardSlots;
}

ATC_DrawDeck* ATC_Board::GetBoardDraw()
{
    return _boardDraw;
}

ATC_DiscardDeck* ATC_Board::GetBoardDiscard()
{
    return _boardDiscard;
}




void ATC_Board::SetBoardPlater(ATC_Plate* newBoardPlate)
{
    _boardPlate = newBoardPlate;
}

void ATC_Board::SetBoardPlayer(ATC_Player* newPlayer)
{
    _boardPlayer = newPlayer;
}

void ATC_Board::SetBoardSlots(TArray<ATC_BoardSlot*> newBoardSlots)
{
    _boardSlots = newBoardSlots;
}

void ATC_Board::SetBoardDraw(ATC_DrawDeck* newDraw)
{
    _boardDraw = newDraw;
}



void ATC_Board::SetBoardDiscard(ATC_DiscardDeck* newDiscard)
{
    _boardDiscard = newDiscard;
}


TArray<TSubclassOf<ATC_Card>> ATC_Board::ShuffleCard(TArray<TSubclassOf<ATC_Card>> PlayerDeckToShuffle)
{
    int32 DeckSize = PlayerDeckToShuffle.Num();
    if (DeckSize <= 1) return PlayerDeckToShuffle;

    for (int32 i = DeckSize - 1; i > 0; --i)
    {
        int32 RandomIndex = FMath::RandRange(0, i);

        PlayerDeckToShuffle.Swap(i, RandomIndex);
    }
    return PlayerDeckToShuffle;
}

void ATC_Board::Init()
{
    _boardDraw = GetWorld()->SpawnActor<ATC_DrawDeck>(DrawDeckBluePrint, BoardDrawAnchor->GetComponentLocation(), BoardDrawAnchor->GetComponentRotation());
    _boardDraw->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
    _boardDraw->SetDrawDeckBoard(this);
    _boardDraw->Init(GetBoardPlayer()->GetDeck());
    _boardDiscard = GetWorld()->SpawnActor<ATC_DiscardDeck>(DiscardDeckBluePrint, BoardDiscardAnchor->GetComponentLocation(), BoardDiscardAnchor->GetComponentRotation());
    _boardDiscard->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
    _boardDiscard->SetDiscardDeckBoard(this);
    _boardSlots.Add(GetWorld()->SpawnActor<ATC_BoardSlot>(BoardSlotBluePrint, BoardSlotOneAnchor->GetComponentLocation(), BoardSlotOneAnchor->GetComponentRotation()));
    _boardSlots.Add(GetWorld()->SpawnActor<ATC_BoardSlot>(BoardSlotBluePrint, BoardSlotTwoAnchor->GetComponentLocation(), BoardSlotTwoAnchor->GetComponentRotation()));
    _boardSlots.Add(GetWorld()->SpawnActor<ATC_BoardSlot>(BoardSlotBluePrint, BoardSlotThreeAnchor->GetComponentLocation(), BoardSlotThreeAnchor->GetComponentRotation()));

    for (ATC_BoardSlot* BoardSlot : _boardSlots)
    {
        BoardSlot->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        BoardSlot->SetBoardSlotBoard(this);
        BoardSlot->Init();
    }
    
}
