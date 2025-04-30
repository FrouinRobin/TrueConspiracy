// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TC_BoardSlotUI.generated.h"

class ATC_BoardSlot;

UCLASS()
class TRUECONSPIRACY_API UTC_BoardSlotUI : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	ATC_BoardSlot* GetWidgetBoardSlot();

	UFUNCTION(BlueprintCallable)
	void SetWidgetBoardSlot(ATC_BoardSlot* newBoardSlot);

	UFUNCTION(BlueprintCallable)
	void SetMyText(const FString& NewText, UTextBlock* TextScore);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUpdate();

protected:

private:

	ATC_BoardSlot* _widgetBoardSlot;
};
