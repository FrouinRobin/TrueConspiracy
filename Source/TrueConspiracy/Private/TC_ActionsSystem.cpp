#include "TC_ActionsSystem.h"
#include "TC_GameStates.h"
#include "TC_AIActions.h"
#include "TC_Player.h"
#include "Board/TC_Plate.h"
#include "TC_GameInstance.h"
#include "TC_GameManager.h"
#include "Kismet/GameplayStatics.h"

TC_ActionsSystem::TC_ActionsSystem()
{
}

TC_ActionsSystem::~TC_ActionsSystem()
{
}

TArray<FAIActions> TC_ActionsSystem::GenerateAllValidActions(const TC_GameStates& InGameState)
{
	TArray<FAIActions> ValidActions;

	const bool bIsPlayer1 = InGameState.GetIsPlayer1Turn();

	return TArray<FAIActions>();
}

void TC_ActionsSystem::PlayCard(TC_GameStates& InGameState, const FAIActions& InAction)
{
	////GPT DEBUG
	//UE_LOG(LogTemp, Warning, TEXT("Player1: %s | Player2: %s | IsPlayer1Turn: %s"),*GetNameSafe(InGameState.GetPlayer1()),*GetNameSafe(InGameState.GetPlayer2()),InGameState.GetIsPlayer1Turn() ? TEXT("true") : TEXT("false"));
	
	// Récupération du joueur actif
	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	if (!ActivePlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
		return;
	}
	
	// Vérification de la carte à jouer
	if (!InAction.CardInHand)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucune carte fournie dans l'action."));
		return;
	}
	
	// Vérification de la main du joueur
	TArray<ATC_Card*> ActivePlayerHand = ActivePlayer->GetHand();

	//UE_LOG(LogTemp, Warning, TEXT("PlayCard: Main contient %d cartes."), ActivePlayerHand.Num());
	for (ATC_Card* Card : ActivePlayerHand)
	{
		if (Card)
		{
			//UE_LOG(LogTemp, Warning, TEXT(" - Carte dans main : %s (%p)"), *Card->GetName(), Card);
		}
	}
	
	ATC_Card* SelectedCard = ActivePlayer->GetHand()[InAction.CardinHandIndex];

	// Vérification du coût en mana
	int32 CurrentMana = ActivePlayer->GetPlayerCurrentMana();
	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Current Mana : %i du joueur : %s"), ActivePlayer->GetPlayerCurrentMana(), *GetNameSafe(ActivePlayer));
	UE_LOG(LogTemp, Warning, TEXT("ACTION: Current Mana : %f du joueur : %s"), InAction.CardInHand->GetCardCurrentMana(), *GetNameSafe(ActivePlayer));
	if (InAction.CardInHand->GetCardCurrentMana() > CurrentMana)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Mana insuffisant pour le joueur : %s."), *GetNameSafe(ActivePlayer));
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Current Mana : %i du joueur : %s"), ActivePlayer->GetPlayerCurrentMana(), *GetNameSafe(ActivePlayer));
		return;
	}
	
	// Vérification du GamePlate et du plateau correspondant
	ATC_Plate* Plate = InGameState.GetGamePlate();
	if (!Plate)
	{
		//UE_LOG(LogTemp, Error, TEXT("PlayCard: GamePlate est nul."));
		return;
	}
	
	// Retirer la carte de la main
	TArray<ATC_Card*> Hand = ActivePlayer->GetHand();
	//ActivePlayer->GetHand().Remove(SelectedCard);
	ActivePlayer->RemoveCardFromHand(SelectedCard);
	
	// Dépenser le mana
	ActivePlayer->SetPlayerCurrentMana(CurrentMana - InAction.CardInHand->GetCardCurrentMana());
	UE_LOG(LogTemp, Warning, TEXT("NEW: Current Mana : %i du joueur : %s"), ActivePlayer->GetPlayerCurrentMana(), *GetNameSafe(ActivePlayer));

	// Spawn de la carte
	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(InAction.PlayingSlot);
	if (!GameInstance)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayCard: GameInstance introuvable."));
		return;
	}
	
	//ATC_Slot* SlotCard = ActivePlayer->GetPlayerBoard()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex];
	//ActivePlayer->GetPlayerBoard()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->SetSlotCard(InAction.CardInHand); //Attribution de la carte au slot
	//ActivePlayer->GetPlayerBoard()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->GetSlotCard()->SetSlot(InAction.PlayingSlot); //Attribution du slot à la carte

	ATC_Card* SpawnedCard = GameInstance->GetWorld()->SpawnActor<ATC_Card>(
		SelectedCard->GetClass(),
		ActivePlayer->GetPlayerBoard()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->GetActorLocation(),
		ActivePlayer->GetPlayerBoard()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->GetActorRotation());
	SpawnedCard->SetPlayer(ActivePlayer);
	SpawnedCard->Init();
	if (!SpawnedCard)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayCard: Échec du spawn de la carte."));
		return;
	}

	InAction.PlayingSlot->SetSlotCard(SpawnedCard);
	InAction.CardInHand->SetSlot(InAction.PlayingSlot);
	UTC_BoardSlotUI* BoardSlotWidget = Cast<UTC_BoardSlotUI>(InAction.PlayingSlot->GetSlotBoardSlot()->Widget->GetWidget());
	if (BoardSlotWidget)
	{
		BoardSlotWidget->OnUpdate();
	}

	//UE_LOG(LogTemp, Log, TEXT("PlayCard: Carte %s jouée avec succès."), *SpawnedCard->GetName());

	if (SelectedCard->Destroy()) 
	{
		//UE_LOG(LogTemp, Log, TEXT("PlayCard: SelectedCard Destroyed."));
	}

	SpawnedCard->OnCardPlace();
}

void TC_ActionsSystem::DrawCard(TC_GameStates& InGameState, const FAIActions& InAction)
{
	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	if (!ActivePlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
		return;
	}

	ATC_Plate* Plate = InGameState.GetGamePlate();
	if (!Plate)
	{
		//UE_LOG(LogTemp, Error, TEXT("DrawCard : GamePlate est nul."));
		return;
	}

	ATC_Board* CurrentPlayerBoard = nullptr;

	if (!ActivePlayer->GetPlayerBoard())
	{
		//UE_LOG(LogTemp, Error, TEXT("DrawCard : BoardDraw est nul."));
		return;
	}
	else
	{
		CurrentPlayerBoard = ActivePlayer->GetPlayerBoard();
	}

	TArray<ATC_Card*> BoardPlayerDrawDeck = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeck();
	//TArray<ATC_Card*> Hand = ActivePlayer->GetHand();

	if (BoardPlayerDrawDeck.Num() == 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("DrawCard : Deck vide, pioche impossible."));
		return;
	}

	//DrawCard from last index on the list
	ATC_Card* DrawnCard = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeckGameFirstCard();

	if (!DrawnCard || !DrawnCard->GetClass())
	{
		//UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte invalide."));
		return;
	}

	//Adding card to hand
	//UWorld* World = DrawnCard->GetWorld();
	//if (!World)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("DrawCard : World est nul."));
	//	return;
	//}
	//
	//ATC_Card* NewCard = World->SpawnActor<ATC_Card>(DrawnCard->GetClass());
	//if (!NewCard)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("DrawCard : Échec du SpawnActor de la carte."));
	//	return;
	//}
	//
	//bool isCardAdded = ActivePlayer->AddCardToHand(NewCard);

	bool isCardAdded = ActivePlayer->AddCardToHand(DrawnCard->GetClass());

	if (isCardAdded)
	{
		//UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte %s ajoutée à la main."), *DrawnCard->GetName());
		CurrentPlayerBoard->OnDrawCard(DrawnCard);
		//UE_LOG(LogTemp, Log, TEXT("DrawCard : Il reste %d cartes dans le deck."), CurrentPlayerBoard->GetBoardDraw()->GetDrawDeck().Num());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("DrawCard : Échec lors de l'ajout à la main. %s"), *DrawnCard->GetName());
	}

	ActivePlayer->ShowHandOnCamera();
}

void TC_ActionsSystem::MoveCard(TC_GameStates& InGameState, const FAIActions& InAction)
{
	//Récupération du joueur actif
	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	if (!ActivePlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MoveCard: Aucun joueur actif."));
		return;
	}
	//Récupération du plateau de jeu
	ATC_Plate* Plate = InGameState.GetGamePlate();
	if (!Plate)
	{
		//UE_LOG(LogTemp, Error, TEXT("MoveCard : GamePlate est nul."));
		return;
	}
	//Récupération du board du joueur actif
	ATC_Board* PlayerBoard = ActivePlayer->GetPlayerBoard();
	if (!PlayerBoard)
	{
		//UE_LOG(LogTemp, Error, TEXT("MoveCard : BoardDraw est nul."));
		return;
	}

	//Récupération des BoardSlots du joueur actif
	TArray<ATC_BoardSlot*> BoardSlots = PlayerBoard->GetBoardSlots();
	//Vérification de la validité de l'index
	if (!BoardSlots.IsValidIndex(InAction.BoardSlotIndex))
	{
		//UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardSlotIndex %d invalide."), InAction.BoardSlotIndex);
		return;
	}
	//Récupération du BoardSlot origine de la carte à déplacer
	ATC_BoardSlot* FromBoardSlot = BoardSlots[InAction.BoardSlotIndex];
	TArray<ATC_Slot*> SlotsInBoard = FromBoardSlot->GetBoardSlotSlots();
	//Vérification de la validité de l'index
	if (!SlotsInBoard.IsValidIndex(InAction.BoardSlotCardIndex))
	{
		//UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardCardIndex %d invalide."), InAction.BoardSlotCardIndex);
		return;
	}

	ATC_Slot* CurrentSlot = SlotsInBoard[InAction.BoardSlotCardIndex];
	ATC_Card* CardToMove = CurrentSlot->GetSlotCard();

	if (!CardToMove)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MoveCard: Aucune carte trouvée à la position spécifiée."));
		return;
	}

	if (!BoardSlots.IsValidIndex(InAction.DestinationBoardSlotIndex))
	{
		//UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationTerrainIndex %d invalide."), InAction.DestinationBoardSlotIndex);
		return;
	}

	ATC_BoardSlot* DestinationBoardSlot = BoardSlots[InAction.DestinationBoardSlotCardIndex];
	TArray<ATC_Slot*> DestinationSlots = DestinationBoardSlot->GetBoardSlotSlots();

	if (!DestinationSlots.IsValidIndex(InAction.DestinationBoardSlotCardIndex))
	{
		//UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationSlotIndex %d invalide."), InAction.DestinationBoardSlotCardIndex);
		return;
	}

	ATC_Slot* DestinationSlot = DestinationSlots[InAction.DestinationBoardSlotCardIndex];

	// Retrait de l’ancienne slot
	// 
	// Déplacement de la carte
	DestinationSlot->SetSlotCard(CardToMove);
	CardToMove->SetActorLocation(DestinationSlot->GetActorLocation());
	CardToMove->SetActorRotation(DestinationSlot->GetActorRotation());
}

void TC_ActionsSystem::EndPhase(TC_GameStates& InGameState, const FAIActions& InAction)
{
	//ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	//if (!ActivePlayer)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("EndPhase: Aucun joueur actif."));
	//	return;
	//}
	//
	//ATC_Plate* Plate = InGameState.GetGamePlate();
	//if (!Plate)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("EndPhase : GamePlate est nul."));
	//	return;
	//}
	//
	//for (ATC_Board* Board : Plate->GetPlateBoard())
	//{
	//	for (ATC_BoardSlot* BoardSlot : Board->GetBoardSlots())
	//	{
	//		for (ATC_Slot* Slot : BoardSlot->GetBoardSlotSlots())
	//		{
	//			ATC_Card* Card = Slot->GetSlotCard();
	//			if (IsValid(Card) && !Card->IsPendingKillPending())
	//			{
	//				static const FName FuncName = FName(TEXT("OnCardEndPhase"));
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
	//
	//FString PhaseStateName = StaticEnum<ETC_PhaseState>()->GetNameStringByValue((int64)ActivePlayer->GetPlayerPhaseState());
	////UE_LOG(LogTemp, Error, TEXT("ActivePlayer: %s, PhaseState: %s"), *GetNameSafe(ActivePlayer), *PhaseStateName);
	//
	//if (ActivePlayer->GetPlayerPhaseState() == ETC_PhaseState::Defense)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("EndPhase: Appel de EndTurn."));
	//	FAIActions EndTurnAction(EActionType::EndTurn);
	//	InGameState.ApplyAction(EndTurnAction);
	//}
	//else
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("EndPhase: Appel de StartPhase pour joueur suivant."));
	//	ATC_Player* NextPlayer = (ActivePlayer == InGameState.GetPlayer1()) ? InGameState.GetPlayer2() : InGameState.GetPlayer1();
	//	InGameState.SetActivePlayer(NextPlayer);
	//}
}

//void TC_ActionsSystem::MoveCard(TC_GameStates& InGameState, const FAIActions& InAction)
//{
//	//Récupération du joueur actif
//	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
//	if (!ActivePlayer)
//	{
//		//UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
//		return;
//	}
//	//Récupération du plateau de jeu
//	ATC_Plate* Plate = InGameState.GetGamePlate();
//	if (!Plate)
//	{
//		//UE_LOG(LogTemp, Error, TEXT("DrawCard : GamePlate est nul."));
//		return;
//	}
//	//Récupération du board du joueur actif
//	ATC_Board* PlayerBoard = ActivePlayer->GetPlayerBoard();
//	if (!PlayerBoard)
//	{
//		//UE_LOG(LogTemp, Error, TEXT("DrawCard : BoardDraw est nul."));
//		return;
//	}
//
//	//Récupération des BoardSlots du joueur actif
//	TArray<ATC_BoardSlot*> BoardSlots = PlayerBoard->GetBoardSlots();
//	//Vérification de la validité de l'index
//	if (!BoardSlots.IsValidIndex(InAction.BoardSlotIndex))
//	{
//		//UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardSlotIndex %d invalide."), InAction.BoardSlotIndex);
//		return;
//	}
//	//Récupération du BoardSlot origine de la carte à déplacer
//	ATC_BoardSlot* FromBoardSlot = BoardSlots[InAction.BoardSlotIndex];
//	TArray<ATC_Slot*> SlotsInBoard = FromBoardSlot->GetBoardSlotSlots();
//	//Vérification de la validité de l'index
//	if (!SlotsInBoard.IsValidIndex(InAction.BoardSlotCardIndex))
//	{
//		//UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardCardIndex %d invalide."), InAction.BoardSlotCardIndex);
//		return;
//	}
//
//	ATC_Slot* CurrentSlot = SlotsInBoard[InAction.BoardSlotCardIndex];
//	ATC_Card* CardToMove = CurrentSlot->GetSlotCard();
//
//	if (!CardToMove)
//	{
//		//UE_LOG(LogTemp, Warning, TEXT("MoveCard: Aucune carte trouvée à la position spécifiée."));
//		return;
//	}
//
//	if (!BoardSlots.IsValidIndex(InAction.DestinationBoardSlotIndex))
//	{
//		//UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationTerrainIndex %d invalide."), InAction.DestinationBoardSlotIndex);
//		return;
//	}
//
//	ATC_BoardSlot* DestinationBoardSlot = BoardSlots[InAction.DestinationBoardSlotCardIndex];
//	TArray<ATC_Slot*> DestinationSlots = DestinationBoardSlot->GetBoardSlotSlots();
//
//	if (!DestinationSlots.IsValidIndex(InAction.DestinationBoardSlotCardIndex))
//	{
//		//UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationSlotIndex %d invalide."), InAction.DestinationBoardSlotCardIndex);
//		return;
//	}
//
//	ATC_Slot* DestinationSlot = DestinationSlots[InAction.DestinationBoardSlotCardIndex];
//
//	// Retrait de l’ancienne slot
//	// 
//	// Déplacement de la carte
//	DestinationSlot->SetSlotCard(CardToMove);
//	CardToMove->SetActorLocation(DestinationSlot->GetActorLocation());
//	CardToMove->SetActorRotation(DestinationSlot->GetActorRotation());
//}

void TC_ActionsSystem::EndTurn(TC_GameStates& InGameState, const FAIActions& InAction)
{
	InGameState.SetCurrentTurn(InGameState.GetCurrentTurn() + 1);

	InGameState.SetActivePlayer(InGameState.GetActivePlayer() == InGameState.GetPlayer1() ? InGameState.GetPlayer2() : InGameState.GetPlayer1());
}

void TC_ActionsSystem::ApplyAction(TC_GameStates& InGameState, const FAIActions& InAction)
{
	switch (InAction.Type)
	{
	case EActionType::PlayCard:
	{
		// si le joueur a assez de mana
		// si l'index de carte dans la main est valide
		// si le board n’a pas atteint 12 cartes
		// -> retirer la carte de la main
		// -> ajouter au plateau
		// -> retirer le coût en mana
		PlayCard(InGameState, InAction);
		break;
	}
	case EActionType::DrawCard:
	{
		// si la pioche du joueur n’est pas vide
		// -> retirer la première carte de la pioche
		// -> ajouter à la main
		DrawCard(InGameState, InAction);
		break;
	}
	case EActionType::MoveCard:
	{
		MoveCard(InGameState, InAction);
		break;
	}
	case EActionType::EndPhase:
	{
		EndPhase(InGameState, InAction);
		break;
	}
	case EActionType::EndTurn:
	{
		EndTurn(InGameState, InAction);
		break;
	}
	default:
		break;
	}
}

//void TC_ActionsSystem::EndTurn(TC_GameStates& GameState, ATC_Player* InCurrentPlayer)
//{
//	if (!GameState.GetIsPlayer1Turn())
//	{
//		GameState.SetCurrentTurn(GameState.GetCurrentTurn() + 1);
//	}
//	GameState.SetIsPlayer1Turn(!GameState.GetIsPlayer1Turn());
//}
