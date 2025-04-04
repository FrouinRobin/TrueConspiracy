// Fill out your copyright notice in the Description page of Project Settings.

#include "Board/TC_Board.h"
#include "TC_Player.h"
#include "Board/TC_Plate.h"
#include "Board/TC_BoardSlot.h"


ATC_Board::ATC_Board()
{
	PrimaryActorTick.bCanEverTick = false;
    
    BoardSlotOneAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotOneAnchor"));
    BoardSlotTwoAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotTwoAnchor"));
    BoardSlotThreeAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotThreeAnchor"));
    BoardDrawAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardDrawAnchor"));
    BoardDiscardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("BoardDiscardAnchor"));
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

TArray<ATC_Card*> ATC_Board::GetBoardDraw()
{
    return _boardDraw;
}

ATC_Card* ATC_Board::GetBoardDrawDataFirstCard()
{
    if (_boardDraw.Num() > 0)
    {
        return _boardDraw[0];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDrawDataCardAtIndex(int index)
{
    if (index >= 0 && index < _boardDraw.Num())
    {
        return _boardDraw[index];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDrawDataLastCard()
{
    if (_boardDraw.Num() > 0)
    {
        return _boardDraw[_boardDraw.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDrawGameFirstCard()
{
    if (_boardDraw.Num() > 0)
    {
        return _boardDraw[_boardDraw.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDrawGameCardAtIndex(int index)
{
    if (index >= 0 && index < _boardDraw.Num())
    {
        return _boardDraw[_boardDraw.Num() - index - 1];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDrawGameCardLastCard()
{
    if (_boardDraw.Num() > 0)
    {
        return _boardDraw[0];
    }
    return nullptr;
}

TArray<ATC_Card*> ATC_Board::GetBoardDiscard()
{
    return _boardDiscard;
}

ATC_Card* ATC_Board::GetBoardDiscardDataFirstCard()
{
    if (_boardDiscard.Num() > 0)
    {
        return _boardDiscard[0];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDiscardDataCardAtIndex(int index)
{
    if (index >= 0 && index < _boardDiscard.Num())
    {
        return _boardDiscard[index];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDiscardDataLastCard()
{
    if (_boardDiscard.Num() > 0)
    {
        return _boardDiscard[_boardDiscard.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDiscardGameFirstCard()
{
    if (_boardDiscard.Num() > 0)
    {
        return _boardDiscard[_boardDiscard.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDiscardGameCardAtIndex(int index)
{
    if (index >= 0 && index < _boardDiscard.Num())
    {
        return _boardDiscard[_boardDiscard.Num() - index - 1];
    }
    return nullptr;
}

ATC_Card* ATC_Board::GetBoardDiscardGameCardLastCard()
{
    if (_boardDiscard.Num() > 0)
    {
        return _boardDiscard[0];
    }
    return nullptr;
}




void ATC_Board::SetBoardPlater(ATC_Plate* newBoardPlate)
{
    _boardPlate = newBoardPlate;
}

// Setters
void ATC_Board::SetBoardPlayer(ATC_Player* newPlayer)
{
    _boardPlayer = newPlayer;
}

void ATC_Board::SetBoardSlots(const TArray<ATC_BoardSlot*> newBoardSlots)
{
    _boardSlots = newBoardSlots;
}

void ATC_Board::SetBoardDraw(const TArray<ATC_Card*> newDraw)
{
    _boardDraw = newDraw;
}

void ATC_Board::SetBoardDrawDataFirstCard(ATC_Card* newCard)
{
    if (_boardDraw.Num() > 0)
    {
        _boardDraw[0] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawDataFirstCard: Attempted to set the first card, but the board is empty."));
    }
}

void ATC_Board::SetBoardDrawDataCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _boardDraw.Num())
    {
        _boardDraw[newIndex] = newCard;
    }
    else if (newIndex == _boardDraw.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawDataCardAtIndex: Index is out of bounds. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _boardDraw.Num());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawDataCardAtIndex: Invalid index. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _boardDraw.Num());
    }
}

void ATC_Board::SetBoardDrawDataLastCard(ATC_Card* newCard)
{
    if (_boardDraw.Num() > 0)
    {
        _boardDraw[_boardDraw.Num() - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawDataLastCard: Attempted to set the last card, but the board is empty."));
    }
}

void ATC_Board::SetBoardDrawGameFirstCard(ATC_Card* newCard)
{
    if (_boardDraw.Num() > 0)
    {
        _boardDraw[_boardDraw.Num() - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawGameFirstCard: Attempted to set the first card in game mode, but the board is empty."));
    }
}

void ATC_Board::SetBoardDrawGameCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _boardDraw.Num())
    {
        _boardDraw[_boardDraw.Num() - newIndex - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawGameCardAtIndex: Invalid index in game mode. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _boardDraw.Num());
    }
}

void ATC_Board::SetBoardDrawGameCardLastCard(ATC_Card* newCard)
{
    if (_boardDraw.Num() > 0)
    {
        _boardDraw[0] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetBoardDrawGameCardLastCard: Attempted to set the last card in game mode, but the board is empty."));
    }
}

void ATC_Board::SetBoardDiscard(const TArray<ATC_Card*> newDiscard)
{
    _boardDiscard = newDiscard;
}

void ATC_Board::SetBoardDiscardDataFirstCard(ATC_Card* newCard)
{
    if (_boardDiscard.Num() > 0)
    {
        _boardDiscard[0] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to set the first card in an empty _boardDiscard array."));
    }
}

void ATC_Board::SetBoardDiscardDataCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _boardDiscard.Num())
    {
        _boardDiscard[newIndex] = newCard;
    }
    else if (newIndex == _boardDiscard.Num())
    {
        _boardDiscard.Add(newCard);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Index out of bounds in SetBoardDiscardDataCardAtIndex. Index: %d, Array Size: %d"), newIndex, _boardDiscard.Num());
    }
}

void ATC_Board::SetBoardDiscardDataLastCard(ATC_Card* newCard)
{
    if (_boardDiscard.Num() > 0)
    {
        _boardDiscard[_boardDiscard.Num() - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to set the last card in an empty _boardDiscard array."));
    }
}

void ATC_Board::SetBoardDiscardGameFirstCard(ATC_Card* newCard)
{
    if (_boardDiscard.Num() > 0)
    {
        _boardDiscard[_boardDiscard.Num() - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to set the first game card in an empty _boardDiscard array."));
    }
}

void ATC_Board::SetBoardDiscardGameCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _boardDiscard.Num())
    {
        _boardDiscard[_boardDiscard.Num() - newIndex - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Index out of bounds in SetBoardDiscardGameCardAtIndex. Index: %d, Array Size: %d"), newIndex, _boardDiscard.Num());
    }
}

void ATC_Board::SetBoardDiscardGameCardLastCard(ATC_Card* newCard)
{
    if (_boardDiscard.Num() > 0)
    {
        _boardDiscard[0] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to set the last game card in an empty _boardDiscard array."));
    }
}

TArray<ATC_Card*> ATC_Board::ShuffleCard(TArray<ATC_Card*> PlayerDeckToShuffle)
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
    SetBoardDraw(ShuffleCard(GetBoardPlayer()->GetDeck()));
    int i = 0;
    for (ATC_Card* Card : GetBoardDraw())
    {
        ATC_Card* NewCard = GetWorld()->SpawnActor<ATC_Card>(Card->GetClass(), FVector(BoardDrawAnchor->GetComponentLocation().X, BoardDrawAnchor->GetComponentLocation().Y + i, BoardDrawAnchor->GetComponentLocation().Z), BoardDrawAnchor->GetComponentRotation());
        NewCard->SetCardAttackFace(Card->GetCardAttackFace());
        NewCard->SetCardDefendFace(Card->GetCardDefendFace());
        NewCard->SetCardID(Card->GetCardID());
        NewCard->SetCardType(Card->GetCardType());
        i += 0.5f;
    }
    for (int j = 0; j < 3; j++) {
        _boardSlots.Add(GetWorld()->SpawnActor<ATC_BoardSlot>(BoardSlotOneAnchor->GetComponentLocation(), GetActorRotation()));
        _boardSlots[j]->SetBoardSlotBoard(this);
        _boardSlots[j]->Init()
        
    }
}
