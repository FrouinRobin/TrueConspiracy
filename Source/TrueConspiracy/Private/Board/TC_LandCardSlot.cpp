// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_LandCardSlot.h"

// Sets default values
ATC_LandCardSlot::ATC_LandCardSlot()
{
	PrimaryActorTick.bCanEverTick = false;

}

bool ATC_LandCardSlot::IsUsableBy(APlayerController* Player) const
{
	return false;
}

