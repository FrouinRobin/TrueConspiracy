// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BoardSlotWidget.generated.h"

class ATC_BoardSlot;

UCLASS()
class TRUECONSPIRACY_API UBoardSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	ATC_BoardSlot* GetWidgetBoardSlot();

	UFUNCTION(BlueprintCallable)
	void SetWidgetBoardSlot(ATC_BoardSlot* newBoardSlot);

	

private:
	ATC_BoardSlot* _widgetBoardSlot;
};
