#include "TC_ActionsSystem.h"
#include "TC_GameStates.h"
#include "TC_AIActions.h"
#include "TC_Player.h"
#include "Board/TC_Plate.h"

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

void TC_ActionsSystem::PlayCard(TC_GameStates& GameState, const FAIActions& Action, ATC_Player* InCurrentPlayer)
{
	// Récupérer le joueur actif
	//hand = joueurActif == P1 ? Player1Hand : Player2Hand
	//	board = joueurActif == P1 ? Player1BoardCard : Player2BoardCard
	//	mana = joueurActif == P1 ? Player1Mana : Player2Mana
	//
	//	// Vérifier si l’index de la carte en main est valide
	//	si Action.CardIndexInHand est invalide :
	//return
	//
	//	// Récupérer la carte à jouer
	//	carte = hand[Action.CardIndexInHand]
	//
	//	// Vérifier si le joueur a assez de mana
	//	si carte.ManaCost > mana :
	//return
	//
	//	// Vérifier si le plateau a moins de 12 cartes
	//	si board contient déjà 12 cartes :
	//	return
	//
	//	// Appliquer l’action :
	//	-retirer la carte de la main
	//	- soustraire le coût en mana
	//	- ajouter la carte au plateau
}

void TC_ActionsSystem::DrawCard(TC_GameStates& GameState, ATC_Player* InCurrentPlayer)
{
	// /!\ N'utilise pas une copie de deck, manipule les cartes dans le deck
	if (!InCurrentPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Joueur invalide."));
		return;
	}
	ATC_Board* CurrentPlayerBoard;
	if (GameState.GetGamePlate() && GameState.GetGamePlate()->GetBoardPlayerOne()->GetBoardPlayer() == InCurrentPlayer) {
		CurrentPlayerBoard = GameState.GetGamePlate()->GetBoardPlayerOne();
	}
	else if (GameState.GetGamePlate() && GameState.GetGamePlate()->GetBoardPlayerTwo()->GetBoardPlayer() == InCurrentPlayer)
	{
		CurrentPlayerBoard = GameState.GetGamePlate()->GetBoardPlayerTwo();
	}

	TArray<ATC_Card*> BoardPlayerDrawDeck = CurrentPlayerBoard->GetBoardDraw();
	TArray<ATC_Card*> Hand = InCurrentPlayer->GetHand();

	if (BoardPlayerDrawDeck.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Deck vide, pioche impossible."));
		return;
	}

	//DrawCard from last index on the list
	ATC_Card* DrawnCard = CurrentPlayerBoard->GetBoardDrawGameFirstCard();

	if (!DrawnCard)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte invalide."));
		return;
	}

	//Adding card to hand
	bool isCardAdded = InCurrentPlayer->AddCardToHand(DrawnCard);

	if (isCardAdded)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte %s ajoutee a la main."), DrawnCard->GetName());
		CurrentPlayerBoard->OnDrawCard(DrawnCard);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Echec lors de l'ajout a la main."), DrawnCard->GetName());
	}
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
		PlayCard(InGameState, InAction, InCurrentPlayer);
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