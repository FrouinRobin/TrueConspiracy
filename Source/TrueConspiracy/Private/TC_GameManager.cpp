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
	}
	GetCurrentGameState().SetActivePlayer(GetCurrentGameState().GetPlayer1());
	//Do a CoinFlip
	/*CoinFlip();*/
	//Give the max mana to each player
	GetCurrentGameState().GetPlayer1()->SetPlayerMaxMana(30);
	GetCurrentGameState().GetPlayer1()->SetPlayerCurrentMana(30);
	GetCurrentGameState().GetPlayer2()->SetPlayerMaxMana(30);
	GetCurrentGameState().GetPlayer2()->SetPlayerCurrentMana(30);
	//Start the first round
	StartTurn();
}

void ATC_GameManager::CoinFlip()
{
	//GetCurrentGameState().SetIsPlayer1Turn(FMath::RandBool());

	ATC_Player* ChosenPlayer = FMath::RandBool() ? GetCurrentGameState().GetPlayer1() : GetCurrentGameState().GetPlayer2();
	GetCurrentGameState().SetActivePlayer(ChosenPlayer);
}

void ATC_GameManager::StartGame(EGameModeFormat InFormat, TArray<ATC_Player*> Players) //Bouton de lancement de mode de jeu (BO3/BO5/BO7/BO9)
{
	UE_LOG(LogTemp, Error, TEXT("StartGame called."));

	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(this);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance introuvable dans StartGame()."));
		return;
	}

	GameInstance->SetSelectedFormat(InFormat);
	SetCurrentGameState(TC_GameStates(GameInstance->GetSelectedFormat()));
	
	GetCurrentGameState().SetGamePlate(Plate);
	
	GetCurrentGameState().SetPlayer1(Players[0]);
	GetCurrentGameState().SetPlayer2(Players[1]);

	GetCurrentGameState().GetGamePlate()->SetPlayerOne(GetCurrentGameState().GetPlayer1());
	GetCurrentGameState().GetGamePlate()->SetPlayerTwo(GetCurrentGameState().GetPlayer2());
	GetCurrentGameState().GetGamePlate()->Init();
	
	GetCurrentGameState().SetActivePlayer(GetCurrentGameState().GetPlayer1());
	GetCurrentGameState().GetActivePlayer()->SetPlayerPhaseState(ETC_PhaseState::Attack);
	GetCurrentGameState().GetGamePlate()->GetPlayerTwo()->SetPlayerPhaseState(ETC_PhaseState::Defense);

	InitGame();
}

void ATC_GameManager::StartTurn()
{
	if (GetCurrentGameState().GetCurrentTurn() > 1) 
	{
		//Switch att/def players (cards)
		SwitchPhase();
		//Reset ManaMax
		GetCurrentGameState().GetPlayer1()->SetPlayerCurrentMana(GetCurrentGameState().GetPlayer1()->GetPlayerMaxMana() + 1);
		GetCurrentGameState().GetPlayer2()->SetPlayerCurrentMana(GetCurrentGameState().GetPlayer2()->GetPlayerMaxMana() + 1);
		//Switch priority playing players
		GetCurrentGameState().SetIsPlayer1Turn(!GetCurrentGameState().GetIsPlayer1Turn());
		//Invoke card OnStartTurn
		//for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardByPlayer(GetCurrentGameState().GetPlayer1())->GetBoardSlots())
		//{
		//	for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		//	{
		//		Slot->GetSlotCard()->OnCardStartTurn();
		//	}
		//}
		//for (ATC_BoardSlot* BoardSlot : GetCurrentGameState().GetGamePlate()->GetBoardByPlayer(GetCurrentGameState().GetPlayer2())->GetBoardSlots())
		//{
		//
		//	for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
		//	{
		//		Slot->GetSlotCard()->OnCardStartTurn();
		//	}
		//}
	}
	StartPhase();
}

void ATC_GameManager::StartPhase()
{
	ATC_Player* CurrentPlayer = GetCurrentGameState().GetActivePlayer();

	GetCurrentGameState().ApplyAction(FAIActions(EActionType::DrawCard));

	// Sécuriser les accès à BoardPlayerOne
	Plate = GetCurrentGameState().GetGamePlate();
	if (!Plate)
	{
		UE_LOG(LogTemp, Error, TEXT("StartPhase: Plate est null."));
		return;
	}

	//for (ATC_Board* Board : Plate->GetPlateBoard())
	//{
	//	for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
	//	{
	//
	//		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
	//		{
	//
	//			ATC_Card* Card = Slot->GetSlotCard();
	//			//if (Card)
	//			//{
	//			//	Card->OnCardStartPhase();
	//			//}
	//
	//			if (IsValid(Card) && !Card->IsPendingKillPending())
	//			{
	//				static const FName FuncName = FName(TEXT("OnCardStartPhase"));
	//				UFunction* Func = Card->FindFunction(FuncName);
	//
	//				if (Func && Func->GetOuter() != ATC_Card::StaticClass())
	//				{
	//					Card->ProcessEvent(Func, nullptr);
	//				}
	//			}
	//		}
	//	}
	//}

	FTimerHandle TimerHandle_EndPhase;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(TimerHandle_EndPhase);
	UE_LOG(LogTemp, Error, TEXT("StartPhase: Démarrage du timer de 30s. Joueur : %s"), *CurrentPlayer->GetName());
	TimerManager.SetTimer(TimerHandle_EndPhase, this, &ATC_GameManager::EndPhase, 10.0f, false);

	//Generer toutes les actions valides par mon joueur
	//lorsqu'aucune action est valide on appelle EndPhase
	//GenerateAllValidActions()
	//EndPhase();
}

void ATC_GameManager::EndPhase()
{
	//for (ATC_Board* Board : GetCurrentGameState().GetGamePlate()->GetPlateBoard())
	//{
	//	for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
	//	{
	//		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
	//		{
	//			ATC_Card* Card = Slot->GetSlotCard();
	//			//if (Card)
	//			if (IsValid(Card) && !Card->IsPendingKillPending())
	//			{
	//				static const FName FuncName = FName(TEXT("OnCardEndPhase"));
	//				UFunction* Func = Card->FindFunction(FuncName);
	//
	//				if (Func && Func->GetOuter() != ATC_Card::StaticClass())
	//				{
	//					Card->ProcessEvent(Func, nullptr);
	//				}
	//				//Card->OnCardEndPhase();
	//			}
	//		}
	//	}
	//}
	
	ATC_Player* ActivePlayer = GetCurrentGameState().GetActivePlayer();
	FString PhaseStateName = StaticEnum<ETC_PhaseState>()->GetNameStringByValue((int64)ActivePlayer->GetPlayerPhaseState());
	
	UE_LOG(LogTemp, Error, TEXT("ActivePlayer: %s, PhaseState: %s"),*ActivePlayer->GetName(), *PhaseStateName);
	if (GetCurrentGameState().GetActivePlayer()->GetPlayerPhaseState() == ETC_PhaseState::Defense)
	{
		UE_LOG(LogTemp, Error, TEXT("EndPhase: Appel de EndTurn."));
		EndTurn();
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("EndPhase: Appel de StartPhase pour joueur 2."));
		if (ActivePlayer == GetCurrentGameState().GetPlayer1())
		{
			ActivePlayer = GetCurrentGameState().GetPlayer2();
			GetCurrentGameState().SetActivePlayer(ActivePlayer);
		}
		else
		{
			ActivePlayer = GetCurrentGameState().GetPlayer1();
			GetCurrentGameState().SetActivePlayer(ActivePlayer);
		}
		StartPhase();
	}

	//FAIActions EndPhaseAction(EActionType::EndPhase);
	//GetCurrentGameState().ApplyAction(EndPhaseAction);
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
	UE_LOG(LogTemp, Error, TEXT("EndTurn: Lancement de EndTurn."));

	//for (ATC_Board* Board : GetCurrentGameState().GetGamePlate()->GetPlateBoard())
	//{
	//	for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
	//	{
	//
	//		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
	//		{
	//
	//			ATC_Card* Card = Slot->GetSlotCard();
	//			//if (Card)
	//			//{
	//			//	Card->OnCardEndTurn();
	//			//}
	//
	//			if (IsValid(Card) && !Card->IsPendingKillPending())
	//			{
	//				static const FName FuncName = FName(TEXT("OnCardEndTurn"));
	//				UFunction* Func = Card->FindFunction(FuncName);
	//
	//				if (Func && Func->GetOuter() != ATC_Card::StaticClass())
	//				{
	//					Card->ProcessEvent(Func, nullptr);
	//				}
	//			}
	//		}
	//	}
	//}
	
	// Inverser les rôles d’attaque / défense
	if (GetCurrentGameState().GetPlayer1()->GetPlayerPhaseState() == ETC_PhaseState::Attack)
	{
		GetCurrentGameState().GetPlayer1()->SetPlayerPhaseState(ETC_PhaseState::Defense);
		GetCurrentGameState().GetPlayer2()->SetPlayerPhaseState(ETC_PhaseState::Attack);
		GetCurrentGameState().SetActivePlayer(GetCurrentGameState().GetPlayer2());
	}
	else
	{
		GetCurrentGameState().GetPlayer1()->SetPlayerPhaseState(ETC_PhaseState::Attack);
		GetCurrentGameState().GetPlayer2()->SetPlayerPhaseState(ETC_PhaseState::Defense);
		GetCurrentGameState().SetActivePlayer(GetCurrentGameState().GetPlayer1());
	}

	StartTurn();
}

void ATC_GameManager::EndGame()
{

}

void ATC_GameManager::CalculateScore()
{
	int ActivePlayerScore = 0;
	ATC_Player* CurrentPlayer = GetCurrentGameState().GetActivePlayer();
	ATC_Player* OppositePlayer = GetCurrentGameState().GetActivePlayer()->GetPlayerBoard()->GetBoardSlots()[0]->GetBoardSlotOppositeBoard()->GetBoardSlotBoard()->GetBoardPlayer();
	for (ATC_Card* Card : CurrentPlayer->GetAllPlayerCard(false))
	{
		ActivePlayerScore += Card->GetCardCurrentScore();
	}
	for (ATC_Card* Card : OppositePlayer->GetAllPlayerCard(false))
	{
		ActivePlayerScore += Card->GetCardCurrentScore();
	}

	if (ActivePlayerScore > 0)
	{
		CurrentPlayer->SetPlayerRoundWon(CurrentPlayer->GetPlayerRoundWon() + 1);
	}
	else if (ActivePlayerScore < 0)
	{
		OppositePlayer->SetPlayerRoundWon(OppositePlayer->GetPlayerRoundWon() + 1);
	}
	else
	{
		CurrentPlayer->SetPlayerRoundWon(CurrentPlayer->GetPlayerRoundWon() + 1);
		OppositePlayer->SetPlayerRoundWon(OppositePlayer->GetPlayerRoundWon() + 1);
	}
	CheckForWin();
}

void ATC_GameManager::CheckForWin()
{
	ATC_Player* PlayerOne = GetCurrentGameState().GetPlayer1();
	ATC_Player* PlayerTwo = GetCurrentGameState().GetPlayer2();

	int PlayerOneRounds = PlayerOne->GetPlayerRoundWon();
	int PlayerTwoRounds = PlayerTwo->GetPlayerRoundWon();

	int MaxRounds = GetCurrentGameState().GetGameFormat().MaxRounds;
	int PointsToWin = GetCurrentGameState().GetGameFormat().PointsToWin;

	int TotalRoundsPlayed = PlayerOneRounds + PlayerTwoRounds;

	// Différence max possible avec les rounds restants
	int RoundsLeft = MaxRounds - TotalRoundsPlayed;

	// Si un joueur atteint PointsToWin et l’autre ne peut plus le rattraper
	if (PlayerOneRounds >= PointsToWin && PlayerOneRounds > PlayerTwoRounds + RoundsLeft)
	{
		// PlayerOne wins
	}
	else if (PlayerTwoRounds >= PointsToWin && PlayerTwoRounds > PlayerOneRounds + RoundsLeft)
	{
		// PlayerTwo wins
	}
	// Sinon si plus aucun round possible, on compare les scores
	else if (TotalRoundsPlayed >= MaxRounds)
	{
		if (PlayerOneRounds > PlayerTwoRounds)
		{
			// PlayerOne wins
		}
		else if (PlayerTwoRounds > PlayerOneRounds)
		{
			// PlayerTwo wins
		}
		else
		{
			// It's a draw
		}
	}
	// Sinon, le match continue
}

void ATC_GameManager::RunBasicAI()
{
	ATC_Player* AIPlayer = GetCurrentGameState().GetActivePlayer();

	int CurrentMana = AIPlayer->GetPlayerCurrentMana();
	TArray<ATC_Card*> AIHandCards = AIPlayer->GetHand();

	for (ATC_Card* AICard : AIHandCards)
	{
		if (!AICard || AICard->GetCardCurrentMana() > CurrentMana)
			continue;

		ATC_Board* AIBoard = AIPlayer->GetPlayerBoard();
		if (!AIBoard)
			continue;

		for (ATC_BoardSlot* AIBoardSlots : AIBoard->GetBoardSlots())
		{
			for (ATC_Slot* AISlot : AIBoardSlots->GetBoardSlotSlots())
			{
				if (AISlot && !AISlot->GetSlotCard())
				{
					FAIActions PlayAction(EActionType::PlayCard);
					PlayAction.CardInHand = AICard;
					PlayAction.PlayingSlot = AISlot;
					PlayAction.CardinHandIndex = AIHandCards.Find(AICard);
					PlayAction.BoardSlotIndex = AIBoard->GetBoardSlots().Find(AIBoardSlots);
					PlayAction.BoardSlotCardIndex = AIBoardSlots->GetBoardSlotSlots().Find(AISlot);

					GetCurrentGameState().ApplyAction(PlayAction);

					UE_LOG(LogTemp, Log, TEXT("RunBasicAI: Card %s spawned by AI."),*AICard->GetName());
					return;
				}
			}
		}
	}
}

void ATC_GameManager::SetCurrentGameState(TC_GameStates InCurrentGameState)
{
	_CurrentGameState = InCurrentGameState;
}

TC_GameStates& ATC_GameManager::GetCurrentGameState()
{
	return _CurrentGameState;
}