// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_LandCardSlot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ATC_LandCardSlot::ATC_LandCardSlot()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	UStaticMeshComponent* LandVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LandVisual"));
	LandVisual->SetupAttachment(Root);
}

bool ATC_LandCardSlot::IsUsableBy(APlayerController* Player) const
{
	return !LandCard || LandOwner == Player;
}
