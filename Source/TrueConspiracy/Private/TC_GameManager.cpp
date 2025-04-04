#include "TC_GameManager.h"
#include "TC_GameInstance.h"
#include "TC_GameStates.h"
#include "TC_Player.h"
#include "TC_ActionsSystem.h"
#include "Board/TC_Plate.h"
#include "Board/TC_BoardSlot.h"
#include "Kismet/GameplayStatics.h"

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
		TC_ActionsSystem::DrawCard(GetCurrentGameState(), GetCurrentGameState().GetPlayer1());
		TC_ActionsSystem::DrawCard(GetCurrentGameState(), GetCurrentGameState().GetPlayer2());
	}
	//Give the max mana to each player
	GetCurrentGameState().GetPlayer1()->SetPlayerMana(3);
	GetCurrentGameState().GetPlayer2()->SetPlayerMana(3);
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
	
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATC_Player::StaticClass(), FoundPlayers);
	for (AActor* Actor : FoundPlayers)
	{
		ATC_Player* Player = Cast<ATC_Player>(Actor);
		if (!Player) continue;

		if (Player->PlayerID == 1)
		{
			GetCurrentGameState().SetPlayer1(Player);
		}
		else if (Player->PlayerID == 2)
		{
			GetCurrentGameState().SetPlayer2(Player);
		}
	}
	GetCurrentGameState().SetGamePlate(GameInstance->GetWorld()->SpawnActor<ATC_Plate>(FVector::ZeroVector, FRotator::ZeroRotator));
	InitGame();
}

void ATC_GameManager::StartTurn()
{
	if (GetCurrentGameState().GetCurrentTurn() > 1) 
	{
		//Switch att/def players (cards)
		SwitchPhase();
		//Reset ManaMax
		GetCurrentGameState().GetPlayer1()->SetPlayerMana(GetCurrentGameState().GetPlayer1()->GetPlayerMana() + 1);
		GetCurrentGameState().GetPlayer2()->SetPlayerMana(GetCurrentGameState().GetPlayer2()->GetPlayerMana() + 1);
		//Switch priority playing players
		GetCurrentGameState().SetIsPlayer1Turn(!GetCurrentGameState().GetIsPlayer1Turn());
		//Invoke card OnStartTurn
		for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerOne()->GetBoardSlots())
		{
			
			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{
				Slot->GetSlotCard()->OnCardStartTurn();
			}
		}
		for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerTwo()->GetBoardSlots())
		{

			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{
				Slot->GetSlotCard()->OnCardStartTurn();
			}
		}
	}
	
	StartPhase();
}

void ATC_GameManager::StartPhase()
{
	ATC_Player* CurrentPlayer;
	if (GetCurrentGameState().GetIsPlayer1Turn())
	{
		CurrentPlayer = GetCurrentGameState().GetPlayer1();
	}
	else
	{
		CurrentPlayer = GetCurrentGameState().GetPlayer2();
	}

	GetCurrentGameState().SetActivePlayer(CurrentPlayer);
	TC_ActionsSystem::DrawCard(GetCurrentGameState(), CurrentPlayer);

	for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerOne()->GetBoardSlots())
	{
		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			Slot->GetSlotCard()->OnCardStartPhase();
		}
	}
	for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerTwo()->GetBoardSlots())
	{
		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			Slot->GetSlotCard()->OnCardStartPhase();
		}
	}

	//Generer toutes les actions valides par mon joueur
	// lorsqu'aucune action est valide on appelle EndPhase
	//GenerateAllValidActions()
	//EndPhase();
}

void ATC_GameManager::EndPhase()
{
	bool EndingTurn;
	for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerOne()->GetBoardSlots())
	{
		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			Slot->GetSlotCard()->OnCardEndPhase();
		}
	}
	for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerTwo()->GetBoardSlots())
	{
		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			Slot->GetSlotCard()->OnCardEndPhase();
		}
	}
	if (EndingTurn == false)
	{
		EndingTurn = true;
		StartPhase();
	}
	else 
	{
		EndingTurn = false;
		EndTurn();
	}
}

void ATC_GameManager::SwitchPhase()
{
	for (ATC_Card* Card : GetCurrentGameState().GetPlayer1()->GetHand())
	{
		Card->SwitchPhase();
	}
	for (ATC_Card* Card : GetCurrentGameState().GetPlayer2()->GetHand())
	{
		Card->SwitchPhase();
	}
	for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerOne()->GetBoardSlots())
	{

		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			Slot->GetSlotCard()->SwitchPhase();
		}
	}
	for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerTwo()->GetBoardSlots())
	{

		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		{
			Slot->GetSlotCard()->SwitchPhase();
		}
	}
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

TC_GameStates& ATC_GameManager::GetCurrentGameState()
{
	return _CurrentGameState;
}