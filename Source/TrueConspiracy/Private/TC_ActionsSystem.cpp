#include "TC_ActionsSystem.h"
#include "TC_GameStates.h"
#include "TC_AIActions.h"

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

void TC_ActionsSystem::PlayCard(TC_GameStates& GameState, const FAIActions& Action)
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

void TC_ActionsSystem::DrawCard(TC_GameStates& GameState)
{
	//deck = joueurActif == P1 ? Player1Deck : Player2Deck
	//	hand = joueurActif == P1 ? Player1Hand : Player2Hand
	//
	//	// Vérifier si la pioche est vide
	//	si deck est vide :
	//return
	//
	//	// Piocher la première carte
	//	carte = deck[0]
	//
	//	// Ajouter la carte à la main
	//	hand.Add(carte)
	//
	//	// Retirer la carte du deck
	//	deck.RemoveAt(0)
}

void TC_ActionsSystem::MoveCard(TC_GameStates& GameState, const FAIActions& Action)
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

void TC_ActionsSystem::EndTurn(TC_GameStates& GameState)
{
	if (!GameState.GetIsPlayer1Turn())
	{
		GameState.SetCurrentTurn(GameState.GetCurrentTurn() +1);
	}
	GameState.SetIsPlayer1Turn(!GameState.GetIsPlayer1Turn());
}

void TC_ActionsSystem::ApplyAction(TC_GameStates& InGameState, const FAIActions& InAction)
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
		DrawCard(InGameState);
		break;
	}
	case EActionType::MoveCard:
	{
		MoveCard(InGameState, InAction);
		break;
	}
	case EActionType::EndTurn:
	{
		EndTurn(InGameState); 
		break;
	}
	default:
		break;
	}
}