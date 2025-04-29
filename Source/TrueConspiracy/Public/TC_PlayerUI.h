// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TC_PlayerUI.generated.h"

class UTextBlock;
class UButton;
class UTC_LeaveGamePopup;

UCLASS()
class TRUECONSPIRACY_API UTC_PlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Fonctions pour mettre à jour l'UI

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUpdate();





protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTC_LeaveGamePopup> LeaveGamePopupClass;


private:
	UPROPERTY()
	UTC_LeaveGamePopup* LeaveGamePopup;

};
