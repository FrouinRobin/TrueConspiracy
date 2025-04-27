#include "TC_BTT_SetDifficultyRandom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UTC_BTT_SetDifficultyRandom::UTC_BTT_SetDifficultyRandom()
{
	NodeName = "SetAIDifficulty";
}

EBTNodeResult::Type UTC_BTT_SetDifficultyRandom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float RandomValue = FMath::FRand();

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(RandomDifficultyKey.SelectedKeyName, RandomValue);

	return EBTNodeResult::Succeeded;
}
