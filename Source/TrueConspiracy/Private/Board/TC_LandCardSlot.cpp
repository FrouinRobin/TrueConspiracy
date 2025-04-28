// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_LandCardSlot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TC_Player.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_Board.h"

ATC_LandCardSlot::ATC_LandCardSlot()
{
	PrimaryActorTick.bCanEverTick = false;
}

TArray<ATC_BoardSlot*>& ATC_LandCardSlot::GetLandCardBordSlot()
{
	return _landCardBoardSlots;
}

ATC_BoardSlot* ATC_LandCardSlot::GetLandCardBordSlotByPlayer(ATC_Player* PlayerReference)
{
	ATC_BoardSlot* PlayerBoardSlot = nullptr;
	for (ATC_BoardSlot* BoardSlot : _landCardBoardSlots)
	{
		if (BoardSlot->GetBoardSlotBoard()->GetBoardPlayer() == PlayerReference)
		{
			PlayerBoardSlot = BoardSlot;
		}
		else 
		{
			PlayerBoardSlot = nullptr;
		}
	}
	return PlayerBoardSlot;
}

void ATC_LandCardSlot::SetLandCard(ATC_LandCard* InCard)
{
	_landSlot = InCard;
}

void ATC_LandCardSlot::SetLandPlate(ATC_Plate* InPlate)
{
	_landPlate = InPlate;
}

ATC_Plate* ATC_LandCardSlot::GetLandPlate()
{
	return _landPlate;
}

void ATC_LandCardSlot::LandCardInit()
{
	_landCardBoardSlots[0]->SetBoardSlotOppositeBoard(_landCardBoardSlots[1]);
	_landCardBoardSlots[1]->SetBoardSlotOppositeBoard(_landCardBoardSlots[0]);
}
