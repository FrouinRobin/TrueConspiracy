// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_CardEffect.h"
#include "TC_EffectType.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class TRUECONSPIRACY_API UTC_EffectType : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTC_CardEffect*> EffectList;

	UFUNCTION(BlueprintCallable)
	void DoEffect();
};
