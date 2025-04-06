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

void TC_ActionsSystem::PlayCard(TC_GameStates& GameState, const FAIActions& Action, ATC_Player* InCurrentPlayer)
{

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
	else
	{
		CurrentPlayerBoard = GameState.GetGamePlate()->GetBoardPlayerTwo();
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
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Carte %s ajoutee a la main."), *DrawnCard->GetName());
		CurrentPlayerBoard->OnDrawCard(DrawnCard);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DrawCard : Echec lors de l'ajout a la main. %s"), *DrawnCard->GetName());
	}
	InCurrentPlayer->ShowHandOnCamera();
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