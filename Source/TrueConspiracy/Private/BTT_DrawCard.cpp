#include "BTT_DrawCard.h"
#include "TC_Player.h"
#include "AIController.h"
#include "TC_GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "TC_AIActions.h"

UBTT_DrawCard::UBTT_DrawCard()
{
	NodeName = "DrawCard";
}

EBTNodeResult::Type UBTT_DrawCard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Getting AIController from BehaviorTree sent in params
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_DrawCard: AIController not found."));
		return EBTNodeResult::Failed;
	}
	//Getting AIPawn from AIController
	ATC_Player* AIPlayer = Cast<ATC_Player>(AIController->GetPawn());
	if (!AIPlayer) 
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_DrawCard: AIPawn not found."));
		return EBTNodeResult::Failed;
	}

	//Working only with GameManager as Gamemode
	//Getting GameManager as GameMode from AIPawn
	//ATC_GameManager* GameManager = Cast<ATC_GameManager>(AIPlayer->GetWorld()->GetAuthGameMode());
	//if (!GameManager)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("BTTask_DrawCard: GameManager (GameMode) not found."));
	//	return EBTNodeResult::Failed;
	//}

	//Working only with GameManager as Actor
	//Getting GameManager as Actor from Scene
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_DrawCard: GameManager (Actor) not found."));
		return EBTNodeResult::Failed;
	}

	if (GameManager->GetCurrentGameState().GetActivePlayer() != AIPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTTask_DrawCard: %s isn't the right player."), *AIPlayer->GetName());
		return EBTNodeResult::Failed;
	}

	//Not needed due to current player is already the AIPlayer but in case it's needed for debug purposes.
	//Setting CurrentPlayer to AIPlayer
	//GameManager->GetCurrentGameState().SetActivePlayer(AIPlayer);
	
	//Applying the drawing action (DrawCard)
	GameManager->GetCurrentGameState().ApplyAction(FAIActions(EActionType::DrawCard));
	UE_LOG(LogTemp, Log, TEXT("BTTask_DrawCard: AI %s 's player has drawn a card."), *AIPlayer->GetName());
	return EBTNodeResult::Succeeded;
}
