// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API ATC_AIController : public AAIController
{
	GENERATED_BODY()
	

public:
	ATC_AIController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;
};
