// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "TC_Player.h"
#include "TC_PlayerController.generated.h"

class UEnhancedInputComponent;

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API ATC_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATC_PlayerController();

	void BeginPlay() override;

protected:
	void SetupInputComponent() override;

	void INTERNAL_OnTouchTriggered(const FInputActionValue& Value);
	void INTERNAL_OnTouchReleased();
	void INTERNAL_OnTouchHold();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInputStart(UEnhancedInputComponent* EnhancedInputComponent);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTouchTriggered(FHitResult hit, bool didHit);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTouchHold(FHitResult hit, bool didHit);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTouchReleased();

	UFUNCTION(BlueprintPure, meta = (ReturnDisplayName = "TC Player", ToolTip = "Return the True Conspiracy Player Pawn"))
	ATC_Player* GetMyPawn();

private:
	bool _isTouching;

	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/* Touch Input Action */
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TouchTapAction;

	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TouchHoldAction;
	
};
