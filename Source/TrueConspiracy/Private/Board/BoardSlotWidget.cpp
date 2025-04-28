// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/BoardSlotWidget.h"
#include "Board/TC_BoardSlot.h"

ATC_BoardSlot* UBoardSlotWidget::GetWidgetBoardSlot()
{
	return _widgetBoardSlot;
}

void UBoardSlotWidget::SetWidgetBoardSlot(ATC_BoardSlot* newBoardSlot)
{
	_widgetBoardSlot = newBoardSlot;
}


