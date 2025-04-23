#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TC_BTT_EndTurn.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_BTT_EndTurn : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTC_BTT_EndTurn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
