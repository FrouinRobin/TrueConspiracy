// TC_CardDataStruct.h
#pragma once

#include "CoreMinimal.h"
#include "TC_CardAttribute.h"
#include "TC_CardDataStruct.generated.h"


USTRUCT(BlueprintType)
struct FTC_CardDataStruct 
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETC_CardAttribute Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score;

	FTC_CardDataStruct();

};