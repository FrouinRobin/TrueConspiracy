// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_DeckZone.h"

void UTC_DeckZone::AddCard(ATC_Card*)
{

}

void UTC_DeckZone::RemoveCard(ATC_Card*)
{

}

ATC_Card* UTC_DeckZone::GetCard(float index)
{
	if (!_hand.IsValidIndex(index))
		return _hand[index];

	return nullptr;
}

ATC_Card* UTC_DeckZone::GetCard(ATC_Card CardIn)
{
	/*
	for (ATC_Card* Card : _hand)
	{
		if (*Card == CardIn)
			return Card;
	}*/
	return nullptr;
}
