// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_PlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include "TC_GameInstance.h"
#include "TC_Player.h"
#include "Widgets/SWidget.h"

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

void ATC_PlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();

	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());
	UE_LOG(LogTemp, Warning, TEXT("Role: %d | RemoteRole: %d"), (int32)GetLocalRole(), (int32)GetRemoteRole());

	if (IsLocalController())
	{
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));
		UE_LOG(LogTemp, Warning, TEXT("BeginPlayingState called, setting timer to send deck."));

		// Schedule for next tick to ensure full replication ready
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ATC_PlayerController::SendDeckToServerDelayed);
	}
}

void ATC_PlayerController::SendDeckToServerDelayed()
{
	if (!IsLocalController())
	{
		return;
	}

	UTC_GameInstance* GameInstance = Cast<UTC_GameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));
		UE_LOG(LogTemp, Warning, TEXT("SendDeckToServerDelayed: Calling Server RPC"));

		for (const TSubclassOf<ATC_Card>& CardClass : GameInstance->SelectedPlayerDeck)
		{
			UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
			UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
			UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
			UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
			UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
		}
		// CALL the server function properly
		Server_SendDeckToServer(GameInstance->SelectedPlayerDeck);
	}
}

void ATC_PlayerController::Server_SendDeckToServer_Implementation(const TArray<TSubclassOf<ATC_Card>>& Deck)
{
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SendDeckToServer_Implementation called"));
	for (const TSubclassOf<ATC_Card>& CardClass : Deck)
	{
		UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
		UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
		UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
		UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
		UE_LOG(LogTemp, Warning, TEXT("CardClass: %s"), *CardClass->GetName());
	}
	if (ATC_Player* OwnPawn = Cast<ATC_Player>(GetPawn()))
	{
		OwnPawn->SetPlayerDeck(Deck);
	}
}

bool ATC_PlayerController::Server_SendDeckToServer_Validate(const TArray<TSubclassOf<ATC_Card>>& Deck)
{
	return true;
}