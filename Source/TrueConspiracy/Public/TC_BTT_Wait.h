#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TC_BTT_Wait.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_BTT_Wait : public UBTTaskNode
{
	GENERATED_BODY()
private:
	float ElapsedTime;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wait")
	float WaitingTime = 1.0f;
public:
	UTC_BTT_Wait();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
