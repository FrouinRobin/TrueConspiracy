// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_discardDeck.h"
#include "Board/TC_Board.h"
#include "Cards/TC_Card.h"

// Sets default values
ATC_DiscardDeck::ATC_DiscardDeck()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MainAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("MainAnchor"));
    RootComponent = MainAnchor;

    CardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CardAnchor"));
    CardAnchor->SetupAttachment(MainAnchor);

}

// Called when the game starts or when spawned
void ATC_DiscardDeck::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ATC_DiscardDeck::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

ATC_Board* ATC_DiscardDeck::GetDiscardDeckBoard()
{
    return _discardDeckBoard;
}

TArray<ATC_Card*> ATC_DiscardDeck::GetDiscardDeck()
{
    return _discardDeck;
}

ATC_Card* ATC_DiscardDeck::GetDiscardDeckDataFirstCard()
{
    if (_discardDeck.Num() > 0)
    {
        return _discardDeck[0];
    }
    return nullptr;
}

ATC_Card* ATC_DiscardDeck::GetDiscardDeckDataCardAtIndex(int index)
{
    if (index >= 0 && index < _discardDeck.Num())
    {
        return _discardDeck[index];
    }
    return nullptr;
}

ATC_Card* ATC_DiscardDeck::GetDiscardDeckDataLastCard()
{
    if (_discardDeck.Num() > 0)
    {
        return _discardDeck[_discardDeck.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_DiscardDeck::GetDiscardDeckGameFirstCard()
{
    if (_discardDeck.Num() > 0)
    {
        return _discardDeck[_discardDeck.Num() - 1];
    }
    return nullptr;
}

ATC_Card* ATC_DiscardDeck::GetDiscardDeckGameCardAtIndex(int index)
{
    if (index >= 0 && index < _discardDeck.Num())
    {
        return _discardDeck[_discardDeck.Num() - index - 1];
    }
    return nullptr;
}

ATC_Card* ATC_DiscardDeck::GetDiscardDeckGameCardLastCard()
{
    if (_discardDeck.Num() > 0)
    {
        return _discardDeck[0];
    }
    return nullptr;
}

void ATC_DiscardDeck::SetDiscardDeckBoard(ATC_Board* newDiscardDeckBoard)
{
    _discardDeckBoard = newDiscardDeckBoard;
}

void ATC_DiscardDeck::SetDiscardDeck(TArray<ATC_Card*> newDiscardDeck)
{
    _discardDeck = newDiscardDeck;
}

void ATC_DiscardDeck::SetDiscardDeckDataFirstCard(ATC_Card* newCard)
{
    if (_discardDeck.Num() > 0)
    {
        _discardDeck[0] = newCard;
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckDataFirstCard: Attempted to set the first card, but the board is empty."));
    }
}

void ATC_DiscardDeck::SetDiscardDeckDataCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _discardDeck.Num())
    {
        _discardDeck[newIndex] = newCard;
    }
    else if (newIndex == _discardDeck.Num())
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckDataCardAtIndex: Index is out of bounds. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _discardDeck.Num());
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckDataCardAtIndex: Invalid index. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _discardDeck.Num());
    }
}

void ATC_DiscardDeck::SetDiscardDeckDataLastCard(ATC_Card* newCard)
{
    if (_discardDeck.Num() > 0)
    {
        _discardDeck[_discardDeck.Num() - 1] = newCard;
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckDataLastCard: Attempted to set the last card, but the board is empty."));
    }
}

void ATC_DiscardDeck::SetDiscardDeckGameFirstCard(ATC_Card* newCard)
{
    if (_discardDeck.Num() > 0)
    {
        _discardDeck[_discardDeck.Num() - 1] = newCard;
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckGameFirstCard: Attempted to set the first card in game mode, but the board is empty."));
    }
}

void ATC_DiscardDeck::SetDiscardDeckGameCardAtIndex(int newIndex, ATC_Card* newCard)
{
    if (newIndex >= 0 && newIndex < _discardDeck.Num())
    {
        _discardDeck[_discardDeck.Num() - newIndex - 1] = newCard;
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckGameCardAtIndex: Invalid index in game mode. Attempted to set card at index %d, but the board only has %d cards."), newIndex, _discardDeck.Num());
    }
}

void ATC_DiscardDeck::SetDiscardDeckGameCardLastCard(ATC_Card* newCard)
{
    if (_discardDeck.Num() > 0)
    {
        _discardDeck[0] = newCard;
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("SetDiscardDeckGameCardLastCard: Attempted to set the last card in game mode, but the board is empty."));
    }
}

void ATC_DiscardDeck::AddToDiscard(ATC_Card* CardToDiscard)
{
    _discardDeck.Add(CardToDiscard);
    GetWorld()->SpawnActor<ATC_Card>(CardToDiscard->GetClass(), FVector(CardAnchor->GetComponentLocation().X, CardAnchor->GetComponentLocation().Y, CardAnchor->GetComponentLocation().Z + 2 * _discardDeck.Num()), CardAnchor->K2_GetComponentRotation());

}

