// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_LandCard.h"

ATC_LandCard::ATC_LandCard()
{
	PrimaryActorTick.bCanEverTick = false;

	LandCardRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LandCardRoot"));
	RootComponent = LandCardRoot;
}

void ATC_LandCard::ApplyBonus()
{
	//  bonus
}

void ATC_LandCard::ApplyMalus()
{
	//  malus
}
