// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETC_PlayerStateChangeReason : uint8
{
	Unspecified = 0    UMETA(DisplayName = "Unspecified"),
	PlayCard           UMETA(DisplayName = "PlayCard"),
	SelectTargetEffect UMETA(DisplayName = "SelectTargetEffect"),
};
