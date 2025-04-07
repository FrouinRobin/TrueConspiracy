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

void TC_ActionsSystem::PlayCard(TC_GameStates& InGameState, ATC_Card* InCard, ATC_Slot* InSlot)
{
	InGameState.GetActivePlayer()->SetPlayerMana(InGameState.GetActivePlayer()->GetPlayerMana() - InCard->GetCardCurrentMana());

	UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(InSlot);
	ATC_Card* NewCard = GameInstance->GetWorld()->SpawnActor<ATC_Card>(InSlot->GetActorLocation(), InSlot->GetActorRotation());
	//NewCard->InitCard()
	NewCard->SetCardAttackFace(InCard->GetCardAttackFace());
	NewCard->SetCardDefendFace(InCard->GetCardDefendFace());
	NewCard->SetCardType(InCard->GetCardType());
	//Fin NewCard->InitCard()
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
	//ActivePlayer->GetHand()[InAction.CardIndex];
	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Main contient %d cartes."), ActivePlayerHand.Num());
	for (ATC_Card* Card : ActivePlayerHand)
	{
		if (Card)
		{
			UE_LOG(LogTemp, Warning, TEXT(" - Carte dans main : %s (%p)"), *Card->GetName(), Card);
		}
	}
	
	ATC_Card* SelectedCard = ActivePlayer->GetHand()[InAction.CardIndex];

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
	
	ATC_Board* BoardOne = Plate->GetBoardPlayerOne();
	ATC_Board* BoardTwo = Plate->GetBoardPlayerTwo();
	
	if (!BoardOne || !BoardTwo)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayCard: Un des plateaux est nul. BoardOne=%p | BoardTwo=%p"), BoardOne, BoardTwo);
		return;
	}
	
	ATC_Board* CurrentBoard = nullptr;
	if (BoardOne->GetBoardPlayer() == ActivePlayer)
	{
		CurrentBoard = BoardOne;
	}
	else if (BoardTwo->GetBoardPlayer() == ActivePlayer)
	{
		CurrentBoard = BoardTwo;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayCard: Aucun plateau associé au joueur actif."));
		return;
	}
	
	// Trouver l'index de la slot
	int SlotIndex = 0;
	int BoardSlotIndex = 0;
	
	for (ATC_BoardSlot* BoardSlot : CurrentBoard->GetBoardSlots())
	{
		if (BoardSlot->GetBoardSlotSlots().Contains(InAction.PlayingSlot))
		{
			SlotIndex = BoardSlot->GetBoardSlotSlots().Find(InAction.PlayingSlot);
			BoardSlotIndex = CurrentBoard->GetBoardSlots().Find(BoardSlot);
			break;
		}
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
	
	//ActivePlayer->GetPlayerBoard

	ATC_Card* SpawnedCard = GameInstance->GetWorld()->SpawnActor<ATC_Card>(
		InAction.PlayingSlot->GetActorLocation(),
		InAction.PlayingSlot->GetActorRotation());
	
	if (!SpawnedCard)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayCard: Échec du spawn de la carte."));
		return;
	}
	
	// Copier les infos de la carte jouée
	SpawnedCard->SetCardAttackFace(InAction.CardInHand->GetCardAttackFace());
	SpawnedCard->SetCardDefendFace(InAction.CardInHand->GetCardDefendFace());
	SpawnedCard->SetCardType(InAction.CardInHand->GetCardType());
	
	UE_LOG(LogTemp, Log, TEXT("PlayCard: Carte %s jouée avec succès."), *SpawnedCard->GetName());








	// TODO : OnCardPlayed / ajout dans le plateau

	//UE_LOG(LogTemp, Warning, TEXT("Player1: %s | Player2: %s | IsPlayer1Turn: %s"),
	//	*GetNameSafe(InGameState.GetPlayer1()),
	//	*GetNameSafe(InGameState.GetPlayer2()),
	//	InGameState.GetIsPlayer1Turn() ? TEXT("true") : TEXT("false"));
	////Récupération du joueur actif
	//ATC_Player* ActivePlayer = InGameState.GetActivePlayer();
	////Vérification de la récupération du joueur
	//if (!ActivePlayer)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Aucun joueur actif."));
	//	return;
	//}
	////Récupération de la main du joueur actif
	//TArray<ATC_Card*> ActivePlayerHand = ActivePlayer->GetHand();
	////Vérification que la carte sélectionnée est dans la main du joueur
	//if (!ActivePlayerHand.Contains(InAction.CardInHand))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Index de carte invalide dans la main."));
	//	return;
	//}
	////Récupération de la carte à jouer 
	//ATC_Card* CardToPlay = InAction.CardInHand;
	////Vérification de la carte à jouer
	//if (!CardToPlay)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayCard: La carte est nulle."));
	//	return;
	//}
	////Récupération du mana du joueur
	//int32 CurrentMana = ActivePlayer->GetPlayerMana();
	////Vérification de la possibilité de jouer la carte par rapport à son coût de mana
	//if (CardToPlay->GetCardCurrentMana() > CurrentMana)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Mana insuffisant."));
	//	return;
	//}
	//
	////A retravailler avec les fonctions de Robin dans Board
	//int SlotIndex = 0;
	//int BoardSlotIndex = 0;
	//ATC_Board* currentBoard;
	////Check si le joueur 1 est le joueur actif
	//if (InGameState.GetGamePlate()->GetBoardPlayerOne()->GetBoardPlayer() == ActivePlayer)
	//{
	//	currentBoard = InGameState.GetGamePlate()->GetBoardPlayerOne();
	//	for (ATC_BoardSlot* BoardSlot : currentBoard->GetBoardSlots())
	//	{
	//		if (BoardSlot->GetBoardSlotSlots().Contains(InAction.PlayingSlot))
	//		{
	//			SlotIndex = BoardSlot->GetBoardSlotSlots().Find(InAction.PlayingSlot);
	//			BoardSlotIndex = currentBoard->GetBoardSlots().Find(BoardSlot);
	//			break;
	//		}
	//		else continue;
	//	}
	//}
	////Check si le joueur 2 est le joueur actif
	//if (InGameState.GetGamePlate()->GetBoardPlayerTwo()->GetBoardPlayer() == ActivePlayer)
	//{
	//	currentBoard = InGameState.GetGamePlate()->GetBoardPlayerTwo();
	//	for (ATC_BoardSlot* BoardSlot : currentBoard->GetBoardSlots())
	//	{
	//		if (BoardSlot->GetBoardSlotSlots().Contains(InAction.PlayingSlot))
	//		{
	//			SlotIndex = BoardSlot->GetBoardSlotSlots().Find(InAction.PlayingSlot);
	//			BoardSlotIndex = currentBoard->GetBoardSlots().Find(BoardSlot);
	//			break;
	//		}
	//		else continue;
	//	}
	//}
	//
	//ActivePlayer->GetHand().Remove(CardToPlay);
	//
	//// Dépenser le mana
	//ActivePlayer->SetPlayerMana(CurrentMana - CardToPlay->GetCardCurrentMana());
	//
	//// Spawner la carte sur la slot
	//UTC_GameInstance* GameInstance = UTC_GameInstance::GetInstance(InAction.PlayingSlot);
	//if (!GameInstance)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayCard: GameInstance introuvable."));
	//	return;
	//}
	//
	//ATC_Card* SpawnedCard = GameInstance->GetWorld()->SpawnActor<ATC_Card>(InAction.PlayingSlot->GetActorLocation(), InAction.PlayingSlot->GetActorRotation());
	//if (!SpawnedCard)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayCard: Échec du spawn de la carte."));
	//	return;
	//}
	//
	//// Copier les infos de la carte jouée
	//SpawnedCard->SetCardAttackFace(CardToPlay->GetCardAttackFace());
	//SpawnedCard->SetCardDefendFace(CardToPlay->GetCardDefendFace());
	//SpawnedCard->SetCardType(CardToPlay->GetCardType());
	
	// Appeler le OnCardPlayed() sur le board ou la slot si besoin
}

void TC_ActionsSystem::DrawCard(TC_GameStates& GameState, ATC_Player* InCurrentPlayer)
{

	if (!InCurrentPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Joueur invalide."));
		return;
	}

	ATC_Plate* Plate = GameState.GetGamePlate();
	if (!Plate)
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : GamePlate est nul."));
		return;
	}

	ATC_Board* BoardOne = Plate->GetBoardPlayerOne();
	ATC_Board* BoardTwo = Plate->GetBoardPlayerTwo();

	ATC_Board* CurrentPlayerBoard = nullptr;

	if (BoardOne && BoardOne->GetBoardPlayer() == InCurrentPlayer)
	{
		CurrentPlayerBoard = BoardOne;
	}
	else if (BoardTwo && BoardTwo->GetBoardPlayer() == InCurrentPlayer)
	{
		CurrentPlayerBoard = BoardTwo;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : Aucun plateau associé au joueur actuel."));
		return;
	}

	if (!CurrentPlayerBoard->GetBoardDraw())
	{
		UE_LOG(LogTemp, Error, TEXT("DrawCard : BoardDraw est nul."));
		return;
	}

	TArray<ATC_Card*> BoardPlayerDrawDeck = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeck();
	TArray<ATC_Card*> Hand = InCurrentPlayer->GetHand();

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
	bool isCardAdded = InCurrentPlayer->AddCardToHand(DrawnCard->GetClass());

	if (isCardAdded)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte %s ajoutée à la main."), *DrawnCard->GetName());
		CurrentPlayerBoard->OnDrawCard(DrawnCard);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Échec lors de l'ajout à la main. %s"), *DrawnCard->GetName());
	}

	InCurrentPlayer->ShowHandOnCamera();

	//// /!\ N'utilise pas une copie de deck, manipule les cartes dans le deck
	//if (!InCurrentPlayer)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("DrawCard : Joueur invalide."));
	//	return;
	//}
	//ATC_Board* CurrentPlayerBoard;
	//if (GameState.GetGamePlate() && GameState.GetGamePlate()->GetBoardPlayerOne()->GetBoardPlayer() == InCurrentPlayer) {
	//	CurrentPlayerBoard = GameState.GetGamePlate()->GetBoardPlayerOne();
	//}
	//else
	//{
	//	CurrentPlayerBoard = GameState.GetGamePlate()->GetBoardPlayerTwo();
	//}
	//
	//TArray<ATC_Card*> BoardPlayerDrawDeck = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeck();
	//TArray<ATC_Card*> Hand = InCurrentPlayer->GetHand();
	//
	//if (BoardPlayerDrawDeck.Num() == 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("DrawCard : Deck vide, pioche impossible."));
	//	return;
	//}
	//
	////DrawCard from last index on the list
	//ATC_Card* DrawnCard = CurrentPlayerBoard->GetBoardDraw()->GetDrawDeckGameFirstCard();
	//
	//if (!DrawnCard)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte invalide."));
	//	return;
	//}
	//
	////Adding card to hand
	//bool isCardAdded = InCurrentPlayer->AddCardToHand(DrawnCard->GetClass());
	//
	//if (isCardAdded)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte %s ajoutee a la main."), *DrawnCard->GetName());
	//	CurrentPlayerBoard->OnDrawCard(DrawnCard);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("DrawCard : Echec lors de l'ajout a la main. %s"), *DrawnCard->GetName());
	//}
	//InCurrentPlayer->ShowHandOnCamera();
}

void TC_ActionsSystem::MoveCard(TC_GameStates& GameState, const FAIActions& Action, ATC_Player* InCurrentPlayer)
{
	//board = joueurActif == P1 ? Player1BoardCard : Player2BoardCard
	//
	//	// Vérifier que l’index de la carte est valide
	//	si Action.BoardCardIndex est invalide :
	//return
	//
	//	// Récupérer la carte
	//	carte = board[Action.BoardCardIndex]
	//
	//	// Vérifier si la destination est valide
	//	si Action.DestinationTerrainIndex est invalide :
	//return
	//
	//	// Appliquer le déplacement
	//	-retirer la carte de sa position actuelle
	//	- l’ajouter à la destination correspondante
}

void TC_ActionsSystem::EndTurn(TC_GameStates& GameState, ATC_Player* InCurrentPlayer)
{
	if (!GameState.GetIsPlayer1Turn())
	{
		GameState.SetCurrentTurn(GameState.GetCurrentTurn() +1);
	}
	GameState.SetIsPlayer1Turn(!GameState.GetIsPlayer1Turn());
}

void TC_ActionsSystem::ApplyAction(TC_GameStates& InGameState, const FAIActions& InAction, ATC_Player* InCurrentPlayer)
{
	switch (InAction.Type)
	{
	case EActionType::PlayCard :
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
		DrawCard(InGameState, InCurrentPlayer);
		break;
	}
	case EActionType::MoveCard:
	{
		MoveCard(InGameState, InAction, InCurrentPlayer);
		break;
	}
	case EActionType::EndTurn:
	{
		EndTurn(InGameState, InCurrentPlayer);
		break;
	}
	default:
		break;
	}
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
	//case EActionType::DrawCard:
	//{
	//	// si la pioche du joueur n’est pas vide
	//	// -> retirer la première carte de la pioche
	//	// -> ajouter à la main
	//	DrawCard(InGameState);
	//	break;
	//}
	//case EActionType::MoveCard:
	//{
	//	MoveCard(InGameState, InAction);
	//	break;
	//}
	//case EActionType::EndTurn:
	//{
	//	EndTurn(InGameState);
	//	break;
	//}
	default:
		break;
	}
}