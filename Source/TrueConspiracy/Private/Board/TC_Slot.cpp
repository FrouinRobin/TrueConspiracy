// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Slot.h"

ATC_Card* UTC_Slot::GetCard()
{
	if (HasCard) return _card;
	return nullptr;
}

void UTC_Slot::SetCard(ATC_Card* Card)
{
	_card = Card;
}