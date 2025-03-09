// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)  // Makes it visible in Blueprints
enum class ETC_CardType : uint8
{
    None            UMETA(DisplayName = "None"),
    Monster         UMETA(DisplayName = "Monster"),
    Human           UMETA(DisplayName = "Human"),
    Robot           UMETA(DisplayName = "Robot"),
    Organisation    UMETA(DisplayName = "Organisation")
};

