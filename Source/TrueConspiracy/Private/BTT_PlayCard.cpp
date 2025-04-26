#include "BTT_PlayCard.h"
#include "TC_Player.h"
#include "AIController.h"
#include "TC_GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "TC_AIActions.h"
#include "Board/TC_Plate.h"

UBTT_PlayCard::UBTT_PlayCard()
{
	NodeName = "PlayCard";
}

EBTNodeResult::Type UBTT_PlayCard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	//	//UE_LOG(LogTemp, Error, TEXT("BTTask_PlayCard: GameManager (GameMode) not found."));
	//	return EBTNodeResult::Failed;
	//}

	//Working only with GameManager as Actor
	//Getting GameManager as Actor from Scene
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		//UE_LOG(LogTemp, Error, TEXT("BTTask_PlayCard: GameManager (Actor) not found."));
		return EBTNodeResult::Failed;
	}

	if (GameManager->GetCurrentGameState().GetActivePlayer() != AIPlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BTTask_PlayCard: %s isn't the right player."), *AIPlayer->GetName());
		return EBTNodeResult::Failed;
	}

	TArray<ATC_Card*> AIPlyableCards;
	int CurrentMana = AIPlayer->GetPlayerCurrentMana();
	TArray<ATC_Card*> AIHandCards = AIPlayer->GetHand();

	for (ATC_Card* AICard : AIHandCards)
	{
		if (!AICard || AICard->GetCardCurrentMana() <= CurrentMana)
		{
			AIPlyableCards.Add(AICard);
		}
	}

	if (AIPlyableCards.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	ATC_Card* SelectedCard = AIPlyableCards[FMath::RandRange(0, AIPlyableCards.Num() - 1)];

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
	ATC_Slot* SelectedSlot = AIAvailableSlots[FMath::RandRange(0, AIAvailableSlots.Num() - 1)];

	FAIActions PlayCard(EActionType::PlayCard);
	PlayCard.CardInHand = SelectedCard;
	PlayCard.PlayingSlot = SelectedSlot;
	PlayCard.CardinHandIndex = AIHandCards.Find(SelectedCard);
	PlayCard.BoardSlotIndex = AIBoard->GetBoardSlots().Find(SelectedSlot->GetSlotBoardSlot());
	PlayCard.BoardSlotCardIndex = SelectedSlot->GetSlotBoardSlot()->GetBoardSlotSlots().Find(SelectedSlot);

	GameManager->GetCurrentGameState().ApplyAction(PlayCard);
	UE_LOG(LogTemp, Log, TEXT("BTTask_PlayCard: AI player %s 's has spawned %s card."), *AIPlayer->GetName(), *SelectedCard->GetName());
	return EBTNodeResult::Succeeded;
}
