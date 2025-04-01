// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardSlot.h"

ATC_BoardSlot::ATC_BoardSlot()
{
	PrimaryActorTick.bCanEverTick = false;

	BoardSlotRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BoardSlotRoot"));
	RootComponent = BoardSlotRoot;

	OnActorBeginOverlap.AddDynamic(this, &ATC_BoardSlot::OnBoardSlotOverlap);
}

TArray<ATC_Slot*> ATC_BoardSlot::GetSlots()
{
	return Slots;
}

void ATC_BoardSlot::OnBoardSlotOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	
}
