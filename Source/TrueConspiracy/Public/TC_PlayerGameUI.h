// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TC_PlayerGameUI.generated.h"


class UTextBlock;
class UButton;
class UTC_LeaveGamePopup;
class ATC_Player;
/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UTC_PlayerGameUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUpdate();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ATC_Player* GetWidgetPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATC_Player* Widgetplayer;




protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTC_LeaveGamePopup> LeaveGamePopupClass;


private:
	UPROPERTY()
	UTC_LeaveGamePopup* LeaveGamePopup;
};
