// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_FightZone.h"

ATC_FightZone::ATC_FightZone()
{
	PrimaryActorTick.bCanEverTick = false;

	FightZoneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FightZoneRoot"));
	RootComponent = FightZoneRoot;
}