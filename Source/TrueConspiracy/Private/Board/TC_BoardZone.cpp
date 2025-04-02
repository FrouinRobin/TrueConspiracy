// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardZone.h"

ATC_BoardZone::ATC_BoardZone()
{
	PrimaryActorTick.bCanEverTick = false;

	BoardZoneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BoardZoneRoot"));
	RootComponent = BoardZoneRoot;
}
