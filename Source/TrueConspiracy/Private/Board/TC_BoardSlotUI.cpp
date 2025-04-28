// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardSlotUI.h"
#include "Board/TC_BoardSlot.h"

ATC_BoardSlot* UTC_BoardSlotUI::GetWidgetBoardSlot()
{
	return _widgetBoardSlot;
}

void UTC_BoardSlotUI::SetWidgetBoardSlot(ATC_BoardSlot* newBoardSlot)
{
	_widgetBoardSlot = newBoardSlot;
}
