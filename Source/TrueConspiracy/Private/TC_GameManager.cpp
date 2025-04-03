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

void ATC_GameManager::InitGame()
{
	//Do a CoinFlip
	CoinFlip();
	//Give the players the good sides
	//Draw 5 cards for each players
	for (int32 i = 0; i < 5; ++i)
	{
		//DrawCard for player1
		//DrawCard for player2
	}
	//Give the max mana to each player
	GetCurrentGameState().SetPlayer1Mana(3);
	GetCurrentGameState().SetPlayer2Mana(3);
	//Start the first round
	StartTurn();
}

void ATC_GameManager::CoinFlip()
{
	GetCurrentGameState().SetIsPlayer1Turn(FMath::RandBool());
}

void ATC_GameManager::StartGame(EGameModeFormat InFormat) //Bouton de lancement de mode de jeu (BO3/BO5/BO7/BO9)
{
	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(this);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance introuvable dans StartGame()."));
		return;
	}
	GameInstance->SetSelectedFormat(InFormat);
	GetCurrentGameState() = TC_GameStates(GameInstance->GetSelectedFormat());
	InitGame();
}

void ATC_GameManager::StartTurn()
{
	if (GetCurrentGameState().GetCurrentTurn() > 1) 
	{
		//Switch att/def players (cards)
		SwitchPhase();
		//Reset mana x2players +1
		GetCurrentGameState().SetPlayer1Mana(GetCurrentGameState().GetPlayer1Mana() + 1);
		GetCurrentGameState().SetPlayer2Mana(GetCurrentGameState().GetPlayer2Mana() + 1);
		//Switch priority playing players
		//Invoke card OnStartTurn
	}
	
	StartPhase();
}

void ATC_GameManager::StartPhase()
{
}

void ATC_GameManager::EndPhase()
{
}

void ATC_GameManager::SwitchPhase()
{
	//Get the player who plays the phase ?
	//Is this an attacking phase or a defenssing phase ?
	// 
	//Draw card
	//Add mana

	//for each player
	// TArray<ATC_Card*> PlayerCard = GetBoard->GetCard()
	// for each Card in PlayerCard
	//	Card->SwitchPhase()
}

void ATC_GameManager::PlayAction(const FAIActions& InActionToPlay)
{
}

void ATC_GameManager::EndTurn()
{
	//for each player
	// TArray<ATC_Card*> PlayerCard = GetBoard->GetCard()
	// for each Card in PlayerCard
	//	Card->OnEndTurn()
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