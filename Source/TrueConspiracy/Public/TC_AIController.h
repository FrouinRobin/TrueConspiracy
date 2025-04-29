#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TC_AIController.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ATC_AIController();

protected:
	virtual void BeginPlay() override;
public:
	void ResetRandomDifficulty();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AIDifficulty = 0.5f;
};
