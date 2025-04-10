// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETC_PlayerState : uint8
{
	SELECTHAND  UMETA(DisplayName = "Idle"),
	SELECTSLOT  UMETA(DisplayName = "Selecting Slot"),
	//WAITTURN  UMETA(DisplayName = "Waiting For Turn"),
};
