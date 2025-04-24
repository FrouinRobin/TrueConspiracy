#include "TC_BTD_IsCurrentPlayer.h"
#include "TC_Player.h"
#include "AIController.h"
#include "TC_GameManager.h"
#include "Kismet/GameplayStatics.h"

UTC_BTD_IsCurrentPlayer::UTC_BTD_IsCurrentPlayer()
{
	NodeName = "IsCurrentPlayer";
}

bool UTC_BTD_IsCurrentPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//Getting AIController from BehaviorTree sent in params
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("UTC_BTD_IsCurrentPlayer: AIController not found."));
		return false;
	}
	//Getting AIPawn from AIController
	ATC_Player* AIPlayer = Cast<ATC_Player>(AIController->GetPawn());
	if (!AIPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("UTC_BTD_IsCurrentPlayer: AIPawn not found."));
		return false;
	}

	//Working only with GameManager as Gamemode
	//Getting GameManager as GameMode from AIPawn
	//ATC_GameManager* GameManager = Cast<ATC_GameManager>(AIPlayer->GetWorld()->GetAuthGameMode());
	//if (!GameManager)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("UTC_BTD_IsCurrentPlayer: GameManager (GameMode) not found."));
	//	return false;
	//}

	//Working only with GameManager as Actor
	//Getting GameManager as Actor from Scene
	AActor* GameManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATC_GameManager::StaticClass());
	ATC_GameManager* GameManager = Cast<ATC_GameManager>(GameManagerActor);
	if (!GameManager)
	{
		UE_LOG(LogTemp, Error, TEXT("UTC_BTD_IsCurrentPlayer: GameManager (Actor) not found."));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("IsCurrentPlayer Decorator -> AI: %s | Active: %s"),
		*GetNameSafe(AIPlayer),
		*GetNameSafe(GameManager->GetCurrentGameState().GetActivePlayer()));

	return (GameManager->GetCurrentGameState().GetActivePlayer() == AIPlayer);
}
