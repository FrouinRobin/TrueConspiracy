// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_PlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>

ATC_PlayerController::ATC_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Triggered, this, &ATC_PlayerController::INTERNAL_OnTouchTriggered);
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Completed, this, &ATC_PlayerController::INTERNAL_OnTouchReleased);
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Canceled, this, &ATC_PlayerController::INTERNAL_OnTouchReleased);
		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Triggered, this, &ATC_PlayerController::INTERNAL_OnHoldTriggered);
		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Canceled, this, &ATC_PlayerController::INTERNAL_OnHoldCanceled);


		OnInputStart(EnhancedInputComponent);
	}

}

void ATC_PlayerController::INTERNAL_OnTouchTriggered(const FInputActionValue& Value)
{
	FHitResult hit;
	bool didHit = GetHitResultUnderFingerByChannel(ETouchIndex::Touch1, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_MAX), true, hit);

	if (!didHit)
		didHit = GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_MAX), true, hit);

	if (_isTouching)
		OnTouchHold(hit, didHit);
	else
		OnTouchTriggered(hit, didHit);

	_isTouching = true;
}

void ATC_PlayerController::INTERNAL_OnTouchReleased()
{
	_isTouching = false;
	OnTouchReleased();
}

void ATC_PlayerController::INTERNAL_OnHoldTriggered(const FInputActionValue& Value)
{
	_isHolding = true;
	FHitResult hit;
	bool didHit = GetHitResultUnderFingerByChannel(ETouchIndex::Touch1, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_MAX), true, hit);

	if (!didHit)
		didHit = GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_MAX), true, hit);
	OnHoldTriggered();
}

void ATC_PlayerController::INTERNAL_OnHoldCanceled()
{
	_isHolding = false;
	OnHoldReleased();
}

ATC_Player* ATC_PlayerController::GetMyPawn()
{
	APawn* pawn = GetPawn();
	return Cast<ATC_Player>(pawn);
}