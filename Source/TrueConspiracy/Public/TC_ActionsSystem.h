// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// AIActions = Une commande dans un resto : "Plat 3, Table 4"
// AIActionsSystem = Le serveur ou la cuisine qui sait comment préparer ce plat et vérifier la commande

struct FAIActions;
class TC_GameStates;

class TRUECONSPIRACY_API TC_ActionsSystem //-> contient la logique (fonctions utilitaires que l’IA peut utiliser)
{
public:
	TC_ActionsSystem();
	~TC_ActionsSystem();

	static TArray<FAIActions> GenerateAllValidActions(const TC_GameStates& InGameState);

	static void PlayCard(TC_GameStates& GameState, const FAIActions& Action);
	static void DrawCard(TC_GameStates& GameState);
	static void MoveCard(TC_GameStates& GameState, const FAIActions& Action);
	static void EndTurn(TC_GameStates& GameState);

	static void ApplyAction(TC_GameStates& InGameState, const FAIActions& InAction);
	//static bool IsActionValid(const TC_GameStates& InGameState, const FAIAction& InAction);
};
