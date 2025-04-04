// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)  // Makes it visible in Blueprints
enum class ETC_CardType : uint8
{
    ClassicCard            UMETA(DisplayName = "ClassicCard"),
    LandCard               UMETA(DisplayName = "LandCard"),
    SpellCard              UMETA(DisplayName = "SpellCard")
};

