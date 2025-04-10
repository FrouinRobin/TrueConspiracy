#include "TC_GameManager.h"
#include "TC_GameInstance.h"
#include "TC_GameStates.h"
#include "TC_Player.h"
#include "TC_ActionsSystem.h"
#include "TC_AIActions.h"
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
	//Draw 5 cards for each players
	for (int32 i = 0; i < 5; ++i)
	{
		GetCurrentGameState().SetActivePlayer(GetCurrentGameState().GetPlayer1());
		GetCurrentGameState().ApplyAction(FAIActions(EActionType::DrawCard));

		GetCurrentGameState().SetActivePlayer(GetCurrentGameState().GetPlayer2());
		GetCurrentGameState().ApplyAction(FAIActions(EActionType::DrawCard));

		//TC_ActionsSystem::DrawCard(GetCurrentGameState(), GetCurrentGameState().GetPlayer1());
		//TC_ActionsSystem::DrawCard(GetCurrentGameState(), GetCurrentGameState().GetPlayer2());
	}
	//Do a CoinFlip
	CoinFlip();
	//Give the max mana to each player
	GetCurrentGameState().GetPlayer1()->SetPlayerMana(3);
	GetCurrentGameState().GetPlayer2()->SetPlayerMana(3);
	//Start the first round
	StartTurn();
}

void ATC_GameManager::CoinFlip()
{
	//GetCurrentGameState().SetIsPlayer1Turn(FMath::RandBool());

	ATC_Player* ChosenPlayer = FMath::RandBool() ? GetCurrentGameState().GetPlayer1() : GetCurrentGameState().GetPlayer2();
	GetCurrentGameState().SetActivePlayer(ChosenPlayer);
}

void ATC_GameManager::StartGame(EGameModeFormat InFormat, TArray<ATC_Player*> InPlayers) //Bouton de lancement de mode de jeu (BO3/BO5/BO7/BO9)
{
	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(this);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance introuvable dans StartGame()."));
		return;
	}

	GameInstance->SetSelectedFormat(InFormat);
	//GetCurrentGameState() = TC_GameStates(GameInstance->GetSelectedFormat());
	SetCurrentGameState(TC_GameStates(GameInstance->GetSelectedFormat()));

	GetCurrentGameState().SetGamePlate(Plate);
	//GetCurrentGameState().SetPlayer1(FoundPlayers[0]->GetClass());

	if (InPlayers[0])
	{
		GetCurrentGameState().SetPlayer1(InPlayers[0]);
	}
	if (InPlayers[1])
	{
		GetCurrentGameState().SetPlayer2(InPlayers[1]);
	}
	GetCurrentGameState().GetGamePlate()->SetPlayerOne(GetCurrentGameState().GetPlayer1());
	GetCurrentGameState().GetGamePlate()->SetPlayerTwo(GetCurrentGameState().GetPlayer2());
	GetCurrentGameState().GetGamePlate()->Init();

	//for (AActor* Actor : FoundPlayers)
	//{
	//	ATC_Player* Player = Cast<ATC_Player>(Actor);
	//	if (!Player) continue;
	//
	//	if (Player->PlayerID == 1)
	//	{
	//		GetCurrentGameState().SetPlayer1(Player);
	//		//GetCurrentGameState().GetGamePlate()->SetPlayerOne(Player);
	//	}
	//	else if (Player->PlayerID == 2)
	//	{
	//		GetCurrentGameState().SetPlayer2(Player);
	//		//GetCurrentGameState().GetGamePlate()->SetPlayerTwo(Player);
	//	}
	//}
	InitGame();
}

void ATC_GameManager::StartTurn()
{
	if (GetCurrentGameState().GetCurrentTurn() > 1)
	{
		//Switch att/def players (cards)
		SwitchPhase();
		//Reset ManaMax
		GetCurrentGameState().GetPlayer1()->SetPlayerMana(GetCurrentGameState().GetPlayer1()->GetPlayerMaxMana() + 1);
		GetCurrentGameState().GetPlayer2()->SetPlayerMana(GetCurrentGameState().GetPlayer2()->GetPlayerMaxMana() + 1);
		//Switch priority playing players
		GetCurrentGameState().SetIsPlayer1Turn(!GetCurrentGameState().GetIsPlayer1Turn());
		//Invoke card OnStartTurn
		for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardByPlayer(GetCurrentGameState().GetPlayer1())->GetBoardSlots())
		{
			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{
				Slot->GetSlotCard()->OnCardStartTurn();
			}
		}
		for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardByPlayer(GetCurrentGameState().GetPlayer1())->GetBoardSlots())
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
	ATC_Player* CurrentPlayer = GetCurrentGameState().GetIsPlayer1Turn()
		? GetCurrentGameState().GetPlayer1()
		: GetCurrentGameState().GetPlayer2();

	//GetCurrentGameState().SetActivePlayer(CurrentPlayer);
	//TC_ActionsSystem::DrawCard(GetCurrentGameState(), CurrentPlayer);
	GetCurrentGameState().ApplyAction(FAIActions(EActionType::DrawCard));

	// Sécuriser les accès à BoardPlayerOne
	
	if (!Plate)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPhase: Plate est null."));
		return;
	}

	for (ATC_Board* Board : Plate->GetPlateBoard())
	{
		for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
		{

			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{

				ATC_Card* Card = Slot->GetSlotCard();
				if (Card)
				{
					Card->OnCardStartPhase();
				}
			}
		}
	}

	//ATC_Player* CurrentPlayer;
	//if (GetCurrentGameState().GetIsPlayer1Turn())
	//{
	//	CurrentPlayer = GetCurrentGameState().GetPlayer1();
	//}
	//else
	//{
	//	CurrentPlayer = GetCurrentGameState().GetPlayer2();
	//}
	//
	//GetCurrentGameState().SetActivePlayer(CurrentPlayer);
	//TC_ActionsSystem::DrawCard(GetCurrentGameState(), CurrentPlayer);
	//
	//for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerOne()->GetBoardSlots())
	//{
	//	for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
	//	{
	//		Slot->GetSlotCard()->OnCardStartPhase();
	//	}
	//}
	//for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardPlayerTwo()->GetBoardSlots())
	//{
	//	for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
	//	{
	//		Slot->GetSlotCard()->OnCardStartPhase();
	//	}
	//}

	//Generer toutes les actions valides par mon joueur
	// lorsqu'aucune action est valide on appelle EndPhase
	//GenerateAllValidActions()
	//EndPhase();
}

void ATC_GameManager::EndPhase()
{
	for (ATC_Board* Board : GetCurrentGameState().GetGamePlate()->GetPlateBoard())
	{
		for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
		{

			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{

				ATC_Card* Card = Slot->GetSlotCard();
				if (Card)
				{
					Card->OnCardEndPhase();
				}
			}
		}
	}
	if (GetCurrentGameState().GetActivePlayer()->GetPhaseState() == ETC_PhaseState::Defense)
	{
		EndTurn();
	}
	else
	{
		EndPhase();
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
	for (ATC_Board* Board : GetCurrentGameState().GetGamePlate()->GetPlateBoard())
	{
		for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
		{

			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{

				ATC_Card* Card = Slot->GetSlotCard();
				if (Card)
				{
					Card->SwitchPhase();
				}
			}
		}
	}
}

void ATC_GameManager::PlayAction(const FAIActions& InActionToPlay)
{
}

void ATC_GameManager::EndTurn()
{
	for (ATC_Board* Board : GetCurrentGameState().GetGamePlate()->GetPlateBoard())
	{
		for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
		{

			for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
			{

				ATC_Card* Card = Slot->GetSlotCard();
				if (Card)
				{
					Card->OnCardEndTurn();
				}
			}
		}
	}
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