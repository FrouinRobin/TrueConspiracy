// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)  // Makes it visible in Blueprints
enum class ETC_EffectLocalisation : uint8
{
    Target          UMETA(DisplayName = "Target"),
    Land            UMETA(DisplayName = "Land"),
    Board           UMETA(DisplayName = "Board"),
    BoardSlot       UMETA(DisplayName = "BoardSlot"),
    Plate           UMETA(DisplayName = "Plate"),
    PlayerHand      UMETA(DisplayName = "Player Hand"),
    Player          UMETA(DisplayName = "Player")

};
