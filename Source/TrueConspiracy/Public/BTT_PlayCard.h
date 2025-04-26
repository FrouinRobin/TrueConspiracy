#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_PlayCard.generated.h"

UCLASS()
class TRUECONSPIRACY_API UBTT_PlayCard : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_PlayCard();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
