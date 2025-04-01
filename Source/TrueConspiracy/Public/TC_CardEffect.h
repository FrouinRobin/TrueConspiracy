// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_CardType.h"
#include "TC_TargetType.h"
#include "TC_DataType.h"
#include "TC_CardEffect.generated.h"

class ATC_Card;

UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class TRUECONSPIRACY_API UTC_CardEffect : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ETC_CardType> TargetCardType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ETC_TargetType> TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ETC_DataType> DataType;
public:

	UFUNCTION(BlueprintImplementableEvent)
	void Activate(ATC_Card* Caster);
};
