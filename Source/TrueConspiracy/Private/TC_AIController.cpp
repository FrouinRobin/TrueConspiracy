#include "TC_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

ATC_AIController::ATC_AIController()
{
	bWantsPlayerState = true;
}

void ATC_AIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (BlackboardData)
	{
		if (UseBlackboard(BlackboardData, BlackboardComponent))
		{
			ResetRandomDifficulty();
			//float RandomDifficulty = FMath::FRand();
			//Blackboard->SetValueAsFloat(TEXT("RandomDifficulty"), RandomDifficulty);
		}
	}

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ATC_AIController::ResetRandomDifficulty()
{
	if (Blackboard)
	{
		float RandomDifficulty = FMath::FRand();
		Blackboard->SetValueAsFloat(TEXT("RandomDifficulty"), RandomDifficulty);

		//UE_LOG(LogTemp, Warning, TEXT("ResetRandomDifficulty: New random difficulty set to: %f"), RandomDifficulty);
	}
}
