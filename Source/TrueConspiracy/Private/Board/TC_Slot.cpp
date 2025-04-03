// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Slot.h"
#include "Cards/TC_Card.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ATC_Slot::ATC_Slot()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	UStaticMeshComponent* SlotVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlotVisual"));
	SlotVisual->SetupAttachment(Root);
}

void ATC_Slot::SetCard(ATC_Card* Card)
{
	OccupyingCard = Card;
}

