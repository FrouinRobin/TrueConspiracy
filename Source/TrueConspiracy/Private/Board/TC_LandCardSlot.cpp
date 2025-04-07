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

TArray<ATC_BoardSlot*> ATC_LandCardSlot::GetLandCardBordSlot()
{
	return TArray<ATC_BoardSlot*>();
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
