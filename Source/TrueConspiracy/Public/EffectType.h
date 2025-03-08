// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardEffect.h"
#include "EffectType.generated.h"

/**
 * 
 */
UCLASS()
class TRUECONSPIRACY_API UEffectType : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCardEffect*> EffectList;

	UFUNCTION(BlueprintCallable)
	void DoEffect();
};
