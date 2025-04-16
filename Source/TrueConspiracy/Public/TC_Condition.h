// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_Condition.generated.h"

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UTC_Condition : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Condition")
	bool IsValid();
	virtual bool IsValid_Implementation();
};
