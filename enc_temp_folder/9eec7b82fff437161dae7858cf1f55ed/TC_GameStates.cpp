// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_GameStates.h"

bool TC_GameStates::IsGameRunning() const
{
	return false;
}

int32 TC_GameStates::GetWinner() const
{
	return int32();
}

TArray<TC_GameStates> TC_GameStates::GetNextStates() const
{
	return TArray<TC_GameStates>();
}

void TC_GameStates::ApplyAction(const FAIAction& Action)
{
}

TC_GameStates::TC_GameStates()
{
}

TC_GameStates::~TC_GameStates()
{
}
