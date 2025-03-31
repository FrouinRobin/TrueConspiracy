// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ATC_Card;

class TRUECONSPIRACY_API TC_GameStates
{
public:
	TArray<ATC_Card*> Player1Hand;
	TArray<ATC_Card*> Player2Hand;
	
	TArray<ATC_Card*> Player1BoardCard;
	TArray<ATC_Card*> Player2BoardCard;

	int32 Player1Mana = 0;
	int32 Player2Mana = 0;

	bool bIsPlayer1Turn = true;

	bool IsGameRunning() const; // La partie est-elle finie ?
	int32 GetWinner() const; // 1 = P1, 2 = P2, 0 = égalité, -1 = en cours

	// --- Génération d'états futurs ---
	TArray<TC_GameStates> GetNextStates() const;
	//void ApplyAction(const AIActions& Action);

	TC_GameStates();
	~TC_GameStates();
};
