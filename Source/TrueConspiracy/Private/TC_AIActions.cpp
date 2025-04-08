// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_AIActions.h"

FAIActions::FAIActions(EActionType InType)
{
	Type = InType;
	CardInHand = nullptr;
	PlayingSlot = nullptr;
	CardIndex = 0;
	PlayingSlotIndex = 0;
	BoardSlotIndex = 0;
	TerrainIndex = 0;
	BoardCardIndex = 0;
	DestinationTerrainIndex = 0;
}
