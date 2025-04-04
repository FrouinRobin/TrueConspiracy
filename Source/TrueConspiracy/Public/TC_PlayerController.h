// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "TC_Player.h"
#include "TC_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API ATC_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATC_PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

protected:
	void SetupInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInputStart();
	UFUNCTION(BlueprintImplementableEvent)
	void OnTouchTriggered();
	UFUNCTION(BlueprintImplementableEvent)
	void OnTouchReleased();

	UFUNCTION(BlueprintPure, meta = (ReturnDisplayName = "TC Player", ToolTip = "Return the True Conspiracy Player Pawn"))
	ATC_Player* GetMyPawn();

private:
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/* Touch Input Action */
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TouchAction;
	
};
