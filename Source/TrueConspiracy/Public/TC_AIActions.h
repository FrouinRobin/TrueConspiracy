// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ATC_Card;
class ATC_Slot;
class ATC_LandCardSlot;
class ATC_LandCard;

// AIActions = Une commande dans un resto : "Plat 3, Table 4"
// AIActionsSystem = Le serveur ou la cuisine qui sait comment préparer ce plat et vérifier la commande

UENUM(BlueprintType)
enum class EActionType : uint8 //-> le type d’action
{
    PlayCard,
    DrawCard,
    MoveCard,
    EndPhase,
    EndTurn,
};

struct FAIActions //-> represente une seule action
{
    //static constexpr int32 INVALID_INDEX = -1;

    EActionType Type;
    ATC_Card* CardInHand;
    ATC_Slot* PlayingSlot;
    ATC_LandCardSlot* PlayingLandSlot;
    ATC_LandCard* LandCardInHand;

    int CardinHandIndex; //Index de la carte en main
    int BoardSlotIndex; //Index du BoardSlot (0, 1 ou 2)
    int BoardSlotCardIndex; //Index du slot de la carte dans le boardSlot (0,1,2 ou 3)

    int DestinationBoardSlotIndex; //Index du BoardSlot de destination (0, 1 ou 2)
    int DestinationBoardSlotCardIndex; //Index du slot de destination de la carte dans le boardSlot (0,1,2 ou 3)

    int LandSlotIndex;
    int LandCardInHandIndex;

    
    //int TerrainIndex;
    //int PlayingSlotIndex;


    FAIActions() {}
    //FAIActions(EActionType InType) : Type(InType) {}
    FAIActions(EActionType InType);

    // C’est une donnée simple, ce que représente une action dans le jeu
    // Stocker une décision possible dans le MCTS
    // Appliquer une action à un GameState
    // Simuler une séquence d’actions
};