// TC_DataTypeStruct.h
#pragma once

#include "CoreMinimal.h"
#include "TC_DataType.h"
#include "TC_DataTypeStruct.generated.h"

USTRUCT(BlueprintType)
struct FTC_DataTypeStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETC_DataType DataType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 StatValue;

    FTC_DataTypeStruct();
};