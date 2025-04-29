#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TC_BTT_PlayMaxCard.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_BTT_PlayMaxCard : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTC_BTT_PlayMaxCard();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
