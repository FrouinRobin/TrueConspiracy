#include "TC_BTT_PlayMaxCard.h"
#include "TC_Player.h"
#include "AIController.h"
#include "TC_GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Board/TC_Plate.h"
#include "TC_AIActions.h"

UTC_BTT_PlayMaxCard::UTC_BTT_PlayMaxCard()
{
	NodeName = "PlayMaxCard";
}

EBTNodeResult::Type UTC_BTT_PlayMaxCard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Getting AIController from BehaviorTree sent in params
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		//UE_LOG(LogTemp, Error, TEXT("BTTask_PlayCard: AIController not found."));
		return EBTNodeResult::Failed;
	}
	//Getting AIPawn from AIController
	ATC_Player* AIPlayer = Cast<ATC_Player>(AIController->GetPawn());
	if (!AIPlayer)
	{
		//UE_LOG(LogTemp, Error, TEXT("BTTask_PlayCard: AIPawn not found."));
		return EBTNodeResult::Failed;
	}

	//Working only with GameManager as Gamemode
	//Getting GameManager as GameMode from AIPawn
	//ATC_GameManager* GameManager = Cast<ATC_GameManager>(AIPlayer->GetWorld()->GetAuthGameMode());
	//if (!GameManager)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("BTTask_DrawCard: GameManager (GameMode) not found."));
	//	return EBTNodeResult::Failed;
	//}

	//Working only with GameManager as Actor
	//Getting GameManager as Actor from Scene
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		//UE_LOG(LogTemp, Error, TEXT("BTTask_DrawCard: GameManager (Actor) not found."));
		return EBTNodeResult::Failed;
	}

	if (GameManager->GetCurrentGameState().GetActivePlayer() != AIPlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BTTask_PlayCard: %s isn't the right player."), *AIPlayer->GetName());
		return EBTNodeResult::Failed;
	}

	int CurrentMana = AIPlayer->GetPlayerCurrentMana();
	TArray<ATC_Card*> AIHandCards = AIPlayer->GetHand();

	TArray<ATC_Card*> AIPlayableCards;
	for (ATC_Card* AICard : AIHandCards)
	{
		if (!AICard || AICard->GetCardCurrentMana() <= CurrentMana)
		{
			AIPlayableCards.Add(AICard);
		}
	}

	if (AIPlayableCards.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	AIPlayableCards.Sort([](ATC_Card& A,ATC_Card& B)
		{
			return A.GetCardCurrentMana() < B.GetCardCurrentMana();
		});

	ATC_Board* AIBoard = AIPlayer->GetPlayerBoard();
	if (!AIBoard)
	{
		return EBTNodeResult::Failed;
	}

	TArray<ATC_Slot*> AIAvailableSlots;
	for (ATC_BoardSlot* AIBoardSlots : AIBoard->GetBoardSlots())
	{
		for (ATC_Slot* AISlot : AIBoardSlots->GetBoardSlotSlots())
		{
			if (AISlot && !AISlot->HasCard())
			{
				AIAvailableSlots.Add(AISlot);
			}
		}
	}

	if (AIAvailableSlots.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	for (ATC_Card* CardToPlay : AIPlayableCards)
	{
		if (CardToPlay->GetCardCurrentMana() <= CurrentMana)
		{
			ATC_Slot* Slot = AIAvailableSlots[FMath::RandRange(0, AIAvailableSlots.Num() - 1)];
			if (!Slot)
			{
				continue;
			}

			FAIActions PlayAction(EActionType::PlayCard);
			PlayAction.CardInHand = CardToPlay;
			PlayAction.PlayingSlot = Slot;
			PlayAction.CardinHandIndex = AIHandCards.Find(CardToPlay);
			PlayAction.BoardSlotIndex = AIBoard->GetBoardSlots().Find(Slot->GetSlotBoardSlot());
			PlayAction.BoardSlotCardIndex = Slot->GetSlotBoardSlot()->GetBoardSlotSlots().Find(Slot);

			GameManager->GetCurrentGameState().ApplyAction(PlayAction);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
