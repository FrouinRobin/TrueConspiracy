#include "TC_BTT_Wait.h"

UTC_BTT_Wait::UTC_BTT_Wait()
{
	NodeName = "CustomWait";
	bNotifyTick = true;
	ElapsedTime = 0.0f;
}

EBTNodeResult::Type UTC_BTT_Wait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ElapsedTime = 0.0f;
	return EBTNodeResult::InProgress;
}

void UTC_BTT_Wait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ElapsedTime += DeltaSeconds;

	if (ElapsedTime >= WaitingTime)
	{
		//UE_LOG(LogTemp, Log, TEXT("BTTask_Wait: Finished waiting %.2f seconds."), WaitingTime);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
