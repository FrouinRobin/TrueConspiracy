// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)  // Makes it visible in Blueprints
enum class ETC_CardEffectID : uint8
{
    None                        UMETA(DisplayName = "None"),
    PlusOneManaCost             UMETA(DisplayName = "PlusOneManaCost"),
    Mana                        UMETA(DisplayName = "Mana")
};

