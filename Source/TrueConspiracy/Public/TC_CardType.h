// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)  // Makes it visible in Blueprints
enum class ETC_CardType : uint8
{
    None            UMETA(DisplayName = "None"),
    Monstre         UMETA(DisplayName = "Monstre"),
    Humain           UMETA(DisplayName = "Humain"),
    Technologie      UMETA(DisplayName = "Technologie"),
    Gouvernement    UMETA(DisplayName = "Gouvernement"),
    Apparition      UMETA(DisplayName = "Apparition"),
    ForceOcculte    UMETA(DisplayName = "Force Occulte")
};

