#include "TC_BTT_EndTurn.h"
#include "TC_Player.h"
#include "AIController.h"
#include "TC_GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "TC_AIActions.h"

UTC_BTT_EndTurn::UTC_BTT_EndTurn()
{
	NodeName = "EndTurn";
}

EBTNodeResult::Type UTC_BTT_EndTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Getting AIController from BehaviorTree sent in params
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("UTC_BTT_EndTurn: AIController not found."));
		return EBTNodeResult::Failed;
	}
	//Getting AIPawn from AIController
	ATC_Player* AIPlayer = Cast<ATC_Player>(AIController->GetPawn());
	if (!AIPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("UTC_BTT_EndTurn: AIPawn not found."));
		return EBTNodeResult::Failed;
	}

	//Working only with GameManager as Gamemode
	//Getting GameManager as GameMode from AIPawn
	//ATC_GameManager* GameManager = Cast<ATC_GameManager>(AIPlayer->GetWorld()->GetAuthGameMode());
	//if (!GameManager)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("UTC_BTT_EndTurn: GameManager (GameMode) not found."));
	//	return EBTNodeResult::Failed;
	//}

	//Working only with GameManager as Actor
	//Getting GameManager as Actor from Scene
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		UE_LOG(LogTemp, Error, TEXT("UTC_BTT_EndTurn: GameManager (Actor) not found."));
		return EBTNodeResult::Failed;
	}
	
	if (GameManager->GetCurrentGameState().GetActivePlayer() != AIPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTC_BTT_EndTurn: %s isn't the right player."), *AIPlayer->GetName());
		return EBTNodeResult::Failed;
	}

	GameManager->EndPhase();

	//GameManager->GetCurrentGameState().ApplyAction(FAIActions(EActionType::EndTurn));

	UE_LOG(LogTemp, Log, TEXT("UTC_BTT_EndTurn: AI %s 's player ended his turn."), *AIPlayer->GetName());
	return EBTNodeResult::Succeeded;
}
