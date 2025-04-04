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

void ATC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Started, this, &ATC_PlayerController::OnInputStart);
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Triggered, this, &ATC_PlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Completed, this, &ATC_PlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(TouchAction, ETriggerEvent::Canceled, this, &ATC_PlayerController::OnTouchReleased);
	}
}

ATC_Player* ATC_PlayerController::GetMyPawn()
{
	APawn* pawn = GetPawn();
	return Cast<ATC_Player>(pawn);
}
