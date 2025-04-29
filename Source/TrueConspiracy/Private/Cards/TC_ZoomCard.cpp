// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/TC_ZoomCard.h"
#include "TC_Player.h"

ATC_Player* UTC_ZoomCard::GetWidgetPlayer()
{
	return _playerWidget;
}

void UTC_ZoomCard::SetWidgetPlayer(ATC_Player* newPlayer)
{
	_playerWidget = newPlayer;
}
