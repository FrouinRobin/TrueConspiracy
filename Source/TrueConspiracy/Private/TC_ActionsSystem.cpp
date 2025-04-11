#include "TC_ActionsSystem.h"
#include "TC_GameStates.h"
#include "TC_AIActions.h"
#include "TC_Player.h"
#include "Board/TC_Plate.h"
#include "TC_GameInstance.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Player1: %s | Player2: %s | IsPlayer1Turn: %s"),
		*GetNameSafe(InGameState.GetPlayer1()),
		*GetNameSafe(InGameState.GetPlayer2()),
		InGameState.GetIsPlayer1Turn() ? TEXT("true") : TEXT("false"));
	
	// Récupération du joueur actif
	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	if (!ActivePlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
		return;
	}
	
	// Vérification de la carte à jouer
	if (!InAction.CardInHand)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucune carte fournie dans l'action."));
		return;
	}
	
	// Vérification de la main du joueur
	TArray<ATC_Card*> ActivePlayerHand = ActivePlayer->GetHand();

	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Main contient %d cartes."), ActivePlayerHand.Num());
	for (ATC_Card* Card : ActivePlayerHand)
	{
		if (Card)
		{
			UE_LOG(LogTemp, Warning, TEXT(" - Carte dans main : %s (%p)"), *Card->GetName(), Card);
		}
	}
	
	ATC_Card* SelectedCard = ActivePlayer->GetHand()[InAction.CardinHandIndex];

	// Vérification du coût en mana
	int32 CurrentMana = ActivePlayer->GetPlayerMana();
	if (InAction.CardInHand->GetCardCurrentMana() > CurrentMana)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Mana insuffisant."));
		return;
	}
	
	// Vérification du GamePlate et du plateau correspondant
	ATC_Plate* Plate = InGameState.GetGamePlate();
	if (!Plate)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayCard: GamePlate est nul."));
		return;
	}
	
	// Retirer la carte de la main
	ActivePlayer->GetHand().Remove(SelectedCard);
	
	// Dépenser le mana
	ActivePlayer->SetPlayerMana(CurrentMana - InAction.CardInHand->GetCardCurrentMana());
	
	// Spawn de la carte
	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(InAction.PlayingSlot);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: GameInstance introuvable."));
		return;
	}
	
	//ATC_Slot* SlotCard = ActivePlayer->GetPlayerBaord()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex];
	//ActivePlayer->GetPlayerBaord()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->SetSlotCard(InAction.CardInHand); //Attribution de la carte au slot
	//ActivePlayer->GetPlayerBaord()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->GetSlotCard()->SetSlot(InAction.PlayingSlot); //Attribution du slot à la carte

	ATC_Card* SpawnedCard = GameInstance->GetWorld()->SpawnActor<ATC_Card>(
		SelectedCard->GetClass(),
		ActivePlayer->GetPlayerBaord()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->GetActorLocation(),
		ActivePlayer->GetPlayerBaord()->GetBoardSlots()[InAction.BoardSlotIndex]->GetBoardSlotSlots()[InAction.BoardSlotCardIndex]->GetActorRotation());
	
	if (!SpawnedCard)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Échec du spawn de la carte."));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("PlayCard: Carte %s jouée avec succès."), *SpawnedCard->GetName());

	if (SelectedCard->Destroy()) 
	{
		UE_LOG(LogTemp, Log, TEXT("PlayCard: SelectedCard Destroyed."));
	}

	SpawnedCard->OnCardPlace();
}

void TC_ActionsSystem::DrawCard(TC_GameStates& InGameState, const FAIActions& InAction)
{
	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	if (!ActivePlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
		return;
	}

	ATC_Plate* Plate = InGameState.GetGamePlate();
	if (!Plate)
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : GamePlate est nul."));
		return;
	}

	ATC_Board* CurrentPlayerBoard = nullptr;

	if (!ActivePlayer->GetPlayerBaord())
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : BoardDraw est nul."));
		return;
	}
	else
	{
		CurrentPlayerBoard = ActivePlayer->GetPlayerBaord();
	}

	TArray<ATC_Card*> BoardPlayerDrawDeck = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeck();
	TArray<ATC_Card*> Hand = ActivePlayer->GetHand();

	if (BoardPlayerDrawDeck.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Deck vide, pioche impossible."));
		return;
	}

	//DrawCard from last index on the list
	ATC_Card* DrawnCard = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeckGameFirstCard();

	if (!DrawnCard)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte invalide."));
		return;
	}

	//Adding card to hand
	bool isCardAdded = ActivePlayer->AddCardToHand(DrawnCard->GetClass());

	if (isCardAdded)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte %s ajoutée à la main."), *DrawnCard->GetName());
		CurrentPlayerBoard->OnDrawCard(DrawnCard);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Échec lors de l'ajout à la main. %s"), *DrawnCard->GetName());
	}

	ActivePlayer->ShowHandOnCamera();
}

void TC_ActionsSystem::MoveCard(TC_GameStates& InGameState, const FAIActions& InAction)
{
	//Récupération du joueur actif
	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	if (!ActivePlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
		return;
	}
	//Récupération du plateau de jeu
	ATC_Plate* Plate = InGameState.GetGamePlate();
	if (!Plate)
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : GamePlate est nul."));
		return;
	}
	//Récupération du board du joueur actif
	ATC_Board* PlayerBoard = ActivePlayer->GetPlayerBaord();
	if (!PlayerBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : BoardDraw est nul."));
		return;
	}

	//Récupération des BoardSlots du joueur actif
	TArray<ATC_BoardSlot*> BoardSlots = PlayerBoard->GetBoardSlots();
	//Vérification de la validité de l'index
	if (!BoardSlots.IsValidIndex(InAction.BoardSlotIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardSlotIndex %d invalide."), InAction.BoardSlotIndex);
		return;
	}
	//Récupération du BoardSlot origine de la carte à déplacer
	ATC_BoardSlot* FromBoardSlot = BoardSlots[InAction.BoardSlotIndex];
	TArray<ATC_Slot*> SlotsInBoard = FromBoardSlot->GetBoardSlotSlots();
	//Vérification de la validité de l'index
	if (!SlotsInBoard.IsValidIndex(InAction.BoardSlotCardIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardCardIndex %d invalide."), InAction.BoardSlotCardIndex);
		return;
	}

	ATC_Slot* CurrentSlot = SlotsInBoard[InAction.BoardSlotCardIndex];
	ATC_Card* CardToMove = CurrentSlot->GetSlotCard();

	if (!CardToMove)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveCard: Aucune carte trouvée à la position spécifiée."));
		return;
	}

	if (!BoardSlots.IsValidIndex(InAction.DestinationBoardSlotIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationTerrainIndex %d invalide."), InAction.DestinationBoardSlotIndex);
		return;
	}

	ATC_BoardSlot* DestinationBoardSlot = BoardSlots[InAction.DestinationBoardSlotCardIndex];
	TArray<ATC_Slot*> DestinationSlots = DestinationBoardSlot->GetBoardSlotSlots();

	if (!DestinationSlots.IsValidIndex(InAction.DestinationBoardSlotCardIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationSlotIndex %d invalide."), InAction.DestinationBoardSlotCardIndex);
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

//void TC_ActionsSystem::MoveCard(TC_GameStates& InGameState, const FAIActions& InAction)
//{
//	//Récupération du joueur actif
//	ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
//	if (!ActivePlayer)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
//		return;
//	}
//	//Récupération du plateau de jeu
//	ATC_Plate* Plate = InGameState.GetGamePlate();
//	if (!Plate)
//	{
//		UE_LOG(LogTemp, Error, TEXT("DrawCard : GamePlate est nul."));
//		return;
//	}
//	//Récupération du board du joueur actif
//	ATC_Board* PlayerBoard = ActivePlayer->GetPlayerBaord();
//	if (!PlayerBoard)
//	{
//		UE_LOG(LogTemp, Error, TEXT("DrawCard : BoardDraw est nul."));
//		return;
//	}
//
//	//Récupération des BoardSlots du joueur actif
//	TArray<ATC_BoardSlot*> BoardSlots = PlayerBoard->GetBoardSlots();
//	//Vérification de la validité de l'index
//	if (!BoardSlots.IsValidIndex(InAction.BoardSlotIndex))
//	{
//		UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardSlotIndex %d invalide."), InAction.BoardSlotIndex);
//		return;
//	}
//	//Récupération du BoardSlot origine de la carte à déplacer
//	ATC_BoardSlot* FromBoardSlot = BoardSlots[InAction.BoardSlotIndex];
//	TArray<ATC_Slot*> SlotsInBoard = FromBoardSlot->GetBoardSlotSlots();
//	//Vérification de la validité de l'index
//	if (!SlotsInBoard.IsValidIndex(InAction.BoardSlotCardIndex))
//	{
//		UE_LOG(LogTemp, Error, TEXT("MoveCard: BoardCardIndex %d invalide."), InAction.BoardSlotCardIndex);
//		return;
//	}
//
//	ATC_Slot* CurrentSlot = SlotsInBoard[InAction.BoardSlotCardIndex];
//	ATC_Card* CardToMove = CurrentSlot->GetSlotCard();
//
//	if (!CardToMove)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("MoveCard: Aucune carte trouvée à la position spécifiée."));
//		return;
//	}
//
//	if (!BoardSlots.IsValidIndex(InAction.DestinationBoardSlotIndex))
//	{
//		UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationTerrainIndex %d invalide."), InAction.DestinationBoardSlotIndex);
//		return;
//	}
//
//	ATC_BoardSlot* DestinationBoardSlot = BoardSlots[InAction.DestinationBoardSlotCardIndex];
//	TArray<ATC_Slot*> DestinationSlots = DestinationBoardSlot->GetBoardSlotSlots();
//
//	if (!DestinationSlots.IsValidIndex(InAction.DestinationBoardSlotCardIndex))
//	{
//		UE_LOG(LogTemp, Error, TEXT("MoveCard: DestinationSlotIndex %d invalide."), InAction.DestinationBoardSlotCardIndex);
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
