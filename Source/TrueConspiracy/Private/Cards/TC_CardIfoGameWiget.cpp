// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/TC_CardIfoGameWiget.h"
#include "Cards/TC_Card.h"

void UTC_CardIfoGameWiget::NativeConstruct()
{

}
void UTC_CardIfoGameWiget::SetCardInstance(ATC_Card* Instance)
{

}
/*
void UTC_CardIfoGameWiget::SetCardInstance(UCardInstance* Instance)
{
    CardInstance = Instance;
    if (CardInstance && CardInstance->CardData)
    {
        CardNameText->SetText(CardInstance->CardData->CardName);
        ManaText->SetText(FText::AsNumber(CardInstance->CurrentMana));
    }
}
*/