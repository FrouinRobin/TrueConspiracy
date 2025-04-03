#include "TC_GameManager.h"
#include "TC_GameInstance.h"
#include "TC_GameStates.h"

ATC_GameManager::ATC_GameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATC_GameManager::BeginPlay()
{
	Super::BeginPlay();
}

void ATC_GameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATC_GameManager::Init()
{
}

void ATC_GameManager::CoinFlip()
{
	GetCurrentGameState().SetIsPlayer1Turn(FMath::RandBool());
}

void ATC_GameManager::StartGame()
{
	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(this);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance introuvable dans StartGame()."));
		return;
	}
	GetCurrentGameState() = TC_GameStates(GameInstance->GetSelectedFormat());
}

void ATC_GameManager::StartTurn()
{
	int32 CurrentPlayer;
	if (GetCurrentGameState().GetIsPlayer1Turn()) // = true
	{
		CurrentPlayer = 1;
	}
	else // = false
	{
		CurrentPlayer = 2;
	}
}

void ATC_GameManager::PlayAction(const FAIActions& InActionToPlay)
{
}

void ATC_GameManager::EndTurn()
{
}

void ATC_GameManager::EndGame()
{
}

void ATC_GameManager::SetCurrentGameState(TC_GameStates InCurrentGameState)
{
	_CurrentGameState = InCurrentGameState;
}

TC_GameStates ATC_GameManager::GetCurrentGameState()
{
	return _CurrentGameState;
}