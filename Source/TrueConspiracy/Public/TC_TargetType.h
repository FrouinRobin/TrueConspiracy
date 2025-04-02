// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)  // Makes it visible in Blueprints
enum class ETC_TargetType : uint8
{
    None            UMETA(DisplayName = "None"),
    Self            UMETA(DisplayName = "Self"),
    Ally            UMETA(DisplayName = "Ally"),
    Enemy           UMETA(DisplayName = "Enemy"),
    AllExceptSelf   UMETA(DisplayName = "All Except Self"),
    All             UMETA(DisplayName = "All")
};