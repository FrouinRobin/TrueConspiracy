// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardEffect.generated.h"

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UCardEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Activate();
};
