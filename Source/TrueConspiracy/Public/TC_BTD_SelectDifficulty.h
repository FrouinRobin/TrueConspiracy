#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TC_BTD_SelectDifficulty.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_BTD_SelectDifficulty : public UBTDecorator
{
	GENERATED_BODY()
public:
	UTC_BTD_SelectDifficulty();

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector RandomDifficultyKey;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
