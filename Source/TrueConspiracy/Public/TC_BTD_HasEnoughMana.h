#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TC_BTD_HasEnoughMana.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_BTD_HasEnoughMana : public UBTDecorator
{
	GENERATED_BODY()
public:
	UTC_BTD_HasEnoughMana();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
