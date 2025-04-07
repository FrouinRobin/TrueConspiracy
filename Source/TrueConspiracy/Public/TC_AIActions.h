// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ATC_Card;
class ATC_Slot;

// AIActions = Une commande dans un resto : "Plat 3, Table 4"
// AIActionsSystem = Le serveur ou la cuisine qui sait comment préparer ce plat et vérifier la commande

UENUM(BlueprintType)
enum class EActionType : uint8 //-> le type d’action
{
    PlayCard,
    DrawCard,
    MoveCard,
    EndTurn,
};

struct FAIActions //-> represente une seule action
{
    static constexpr int32 INVALID_INDEX = -1;

    EActionType Type;
    ATC_Card* CardInHand;
    ATC_Slot* PlayingSlot;

    int CardIndex;
    int PlayingSlotIndex;
    int BoardSlotIndex;

    uint32 TerrainIndex = INVALID_INDEX;
    uint32 BoardCardIndex = INVALID_INDEX;
    uint32 DestinationTerrainIndex = INVALID_INDEX;


    FAIActions() {}
    FAIActions(EActionType InType) : Type(InType) {}

    // C’est une donnée simple, ce que représente une action dans le jeu
    // Stocker une décision possible dans le MCTS
    // Appliquer une action à un GameState
    // Simuler une séquence d’actions
};