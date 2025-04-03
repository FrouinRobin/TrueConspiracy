// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Board.h"
#include "TC_Card.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"


ATC_Board::ATC_Board()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATC_Board::BeginPlay()
{
	Super::BeginPlay();
}

void ATC_Board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATC_Board::InitializeBoard()
{

}

bool ATC_Board::PlaceCard(ATC_Card* Card, ATC_Slot* Slot)
{
	return false;
}

//bool ATC_Board::TryPlaceCard(APlayerController* Player, ATC_Card* Card, ATC_Slot* Slot)
//{
//
//	return false;
//}


