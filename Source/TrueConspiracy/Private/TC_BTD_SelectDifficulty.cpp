#include "TC_BTD_SelectDifficulty.h"
#include "TC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTC_BTD_SelectDifficulty::UTC_BTD_SelectDifficulty()
{
	NodeName = "SelectDifficulty";
	bNotifyBecomeRelevant = true;
}

bool UTC_BTD_SelectDifficulty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp)
	{
		return false;
	}
	float RandomDifficultyValue = BBComp->GetValueAsFloat(RandomDifficultyKey.SelectedKeyName);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ATC_AIController* MyAI = Cast<ATC_AIController>(AIController);
	if (!MyAI)
	{
		return false;
	}

	return RandomDifficultyValue <= MyAI->AIDifficulty;

	////Getting AIController from BehaviorTree sent in params
	//AAIController* AIController = OwnerComp.GetAIOwner();
	//if (!AIController)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("UTC_BTD_SelectDifficulty: AIController not found."));
	//	return false;
	//}
	//
	//ATC_AIController* MyAI = Cast<ATC_AIController>(AIController);
	//if (!MyAI)
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("UTC_BTD_SelectDifficulty: AIController not found."));
	//	return false;
	//}
	//
	//float RandomValue = FMath::FRand();
	//
	////if true -> BasicAI | False -> ImprovedAI
	//return RandomValue <= MyAI->AIDifficulty;
}
