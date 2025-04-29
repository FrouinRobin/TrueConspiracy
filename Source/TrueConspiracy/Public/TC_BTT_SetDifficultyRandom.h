#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TC_BTT_SetDifficultyRandom.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_BTT_SetDifficultyRandom : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTC_BTT_SetDifficultyRandom();

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector RandomDifficultyKey;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
