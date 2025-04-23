#include "TC_AIController.h"

ATC_AIController::ATC_AIController()
{
	bWantsPlayerState = true;
}

void ATC_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
