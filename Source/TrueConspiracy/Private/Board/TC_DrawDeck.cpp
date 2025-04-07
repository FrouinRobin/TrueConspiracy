// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_DrawDeck.h"
#include "Board/TC_Board.h"
#include "Cards/TC_Card.h"

// Sets default values
ATC_DrawDeck::ATC_DrawDeck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MainAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("MainAnchor"));
    RootComponent = MainAnchor;

    CardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CardAnchor"));
    CardAnchor->SetupAttachment(MainAnchor);
}

// Called when the game starts or when spawned
void ATC_DrawDeck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATC_DrawDeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATC_Board* ATC_DrawDeck::GetDrawDeckBoard()
{
    return _drawDeckBoard;
}

TArray<ATC_Card*> ATC_DrawDeck::GetDrawDeck()
{
	return _drawDeck;
}

ATC_Card* ATC_DrawDeck::GetDrawDeckDataFirstCard()
{
    if (_drawDeck.Num() > 0)
    {
        return _drawDeck[0];
    }
    return nullptr;
}

ATC_Card* ATC_DrawDeck::GetDrawDeckDataCardAtIndex(int index)
{
    if (index >= 0 && index < _drawDeck.Num())
    {
        return _drawDeck[index];
    }
    return nullptr;
}

ATC_Card* ATC_DrawDeck::GetDrawDeckDataLastCard()
{
    if (_drawDeck.Num() > 0)
    {
        return _drawDeck[_drawDeck.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_DrawDeck::GetDrawDeckGameFirstCard()
{
    if (_drawDeck.Num() > 0)
    {
        return _drawDeck[_drawDeck.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_DrawDeck::GetDrawDeckGameCardAtIndex(int index)
{
    if (index >= 0 && index < _drawDeck.Num())
    {
        return _drawDeck[_drawDeck.Num() - index - 1];
    }
    return nullptr;
}

ATC_Card* ATC_DrawDeck::GetDrawDeckGameCardLastCard()
{
    if (_drawDeck.Num() > 0)
    {
        return _drawDeck[0];
    }
    return nullptr;
}

void ATC_DrawDeck::SetDrawDeckBoard(ATC_Board* newDrawDeckBoard)
{
    _drawDeckBoard = newDrawDeckBoard;
}

void ATC_DrawDeck::SetDrawDeck(TArray<ATC_Card*> newDrawDeck)
{
	_drawDeck = newDrawDeck;
}

void ATC_DrawDeck::SetDrawDeckDataFirstCard(ATC_Card* newCard)
{
    if (_drawDeck.Num() > 0)
    {
        _drawDeck[0] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckDataFirstCard: Attempted to set the first card, but the board is empty."));
    }
}

void ATC_DrawDeck::SetDrawDeckDataCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _drawDeck.Num())
    {
        _drawDeck[newIndex] = newCard;
    }
    else if (newIndex == _drawDeck.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckDataCardAtIndex: Index is out of bounds. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _drawDeck.Num());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckDataCardAtIndex: Invalid index. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _drawDeck.Num());
    }
}

void ATC_DrawDeck::SetDrawDeckDataLastCard(ATC_Card* newCard)
{
    if (_drawDeck.Num() > 0)
    {
        _drawDeck[_drawDeck.Num() - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckDataLastCard: Attempted to set the last card, but the board is empty."));
    }
}

void ATC_DrawDeck::SetDrawDeckGameFirstCard(ATC_Card* newCard)
{
    if (_drawDeck.Num() > 0)
    {
        _drawDeck[_drawDeck.Num() - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckGameFirstCard: Attempted to set the first card in game mode, but the board is empty."));
    }
}

void ATC_DrawDeck::SetDrawDeckGameCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _drawDeck.Num())
    {
        _drawDeck[_drawDeck.Num() - newIndex - 1] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckGameCardAtIndex: Invalid index in game mode. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _drawDeck.Num());
    }
}

void ATC_DrawDeck::SetDrawDeckGameCardLastCard(ATC_Card* newCard)
{
    if (_drawDeck.Num() > 0)
    {
        _drawDeck[0] = newCard;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDrawDeckGameCardLastCard: Attempted to set the last card in game mode, but the board is empty."));
    }
}

TArray<TSubclassOf<ATC_Card>> ATC_DrawDeck::ShuffleCard(TArray<TSubclassOf<ATC_Card>> PlayerDeckToShuffle)
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

void ATC_DrawDeck::Init(TArray<TSubclassOf<ATC_Card>> CardsToSpawn)
{
    for (TSubclassOf<ATC_Card> Card : ShuffleCard(CardsToSpawn))
    {
        ATC_Card* NewCard = GetWorld()->SpawnActor<ATC_Card>(Card, FVector(CardAnchor->GetComponentLocation().X, CardAnchor->GetComponentLocation().Y, CardAnchor->GetComponentLocation().Z + 2 * _drawDeck.Num()), CardAnchor->GetComponentRotation());
        NewCard->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        _drawDeck.Add(NewCard);
    }
}


