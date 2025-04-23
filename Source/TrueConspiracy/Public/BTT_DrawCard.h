#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_DrawCard.generated.h"

UCLASS()
class TRUECONSPIRACY_API UBTT_DrawCard : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_DrawCard();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
