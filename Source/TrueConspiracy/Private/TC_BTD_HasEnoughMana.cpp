#include "TC_BTD_HasEnoughMana.h"
#include "TC_Player.h"
#include "AIController.h"

UTC_BTD_HasEnoughMana::UTC_BTD_HasEnoughMana()
{
	NodeName = "HasEnoughManaToPlay";
}

bool UTC_BTD_HasEnoughMana::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//Getting AIController from BehaviorTree sent in params
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		//UE_LOG(LogTemp, Error, TEXT("UTC_BTD_HasEnoughMana: AIController not found."));
		return false;
	}
	//Getting AIPawn from AIController
	ATC_Player* AIPlayer = Cast<ATC_Player>(AIController->GetPawn());
	if (!AIPlayer)
	{
		//UE_LOG(LogTemp, Error, TEXT("UTC_BTD_HasEnoughMana: AIPawn not found."));
		return false;
	}

	int CurrentMana = AIPlayer->GetPlayerCurrentMana();
	TArray<ATC_Card*> Hand = AIPlayer->GetHand();

	for (ATC_Card* Card : Hand)
	{
		if (Card && Card->GetCardCurrentMana() <= CurrentMana)
		{
			return true;
		}
	}

	return false;
}
