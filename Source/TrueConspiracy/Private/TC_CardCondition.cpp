// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_CardCondition.h"
#include "Board/TC_Slot.h"
#include "Cards/TC_Card.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_Board.h"
#include "TC_Player.h"


bool UTC_CardCondition::IsValidForCard_Implementation(ATC_Card* Card, ATC_Slot* Slot)
{
	if (!IsSlotEmpty(Slot)) return false;
	if (!IsSlotAcceptingCard(Slot, Card)) return false;
	if (!IsCardType(Card, Slot->GetSlotCardType())) return false;
	if (!IsSlotPlayer(Slot, Card)) return false;
	if (!HasEnoughMana(Card)) return false;

	return true;
}

bool UTC_CardCondition::IsSlotEmpty(ATC_Slot* Slot) const
{
	return Slot && !Slot->HasCard();
}

bool UTC_CardCondition::IsCardType(ATC_Card* Card, ETC_CardType Type) const
{
	return Card && Card->GetCardType() == Type;
}

bool UTC_CardCondition::IsSlotAcceptingCard(ATC_Slot* Slot, ATC_Card* Card) const
{
	return Slot && Card && Slot->GetSlotCardType() == Card->GetCardType();
}

bool UTC_CardCondition::IsSlotPlayer(ATC_Slot* Slot, ATC_Card* Card)
{
	return Slot && Card && Slot->GetSlotBoardSlot()->GetBoardSlotBoard()->GetBoardPlayer() == Card->GetPlayer();
}

bool UTC_CardCondition::HasEnoughMana(ATC_Card* Card)
{
	return Card && Card->GetPlayer()->GetPlayerCurrentMana() >= Card->GetCardCurrentMana();
}