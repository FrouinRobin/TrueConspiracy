// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/TC_CardIfoGameWiget.h"
#include "Cards/TC_Card.h"
#include "Cards/Faces/TC_Face.h"


ATC_Card* UTC_CardIfoGameWiget::GetPureWidgetCard()
{
	return _widgetCard;
}

ATC_Card* UTC_CardIfoGameWiget::GetWidgetCard()
{
	return _widgetCard;
}

void UTC_CardIfoGameWiget::SetWidgetCard(ATC_Card* newCard)
{
	_widgetCard = newCard;
}
