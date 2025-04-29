// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/TC_ZoomCardUI.h"

ATC_Player* UTC_ZoomCardUI::GetWidgetPlayer()
{
	return _PlayerWidget;
}

void UTC_ZoomCardUI::SetWidgetPlayer(ATC_Player* newPlayer)
{
	_PlayerWidget = newPlayer;
}