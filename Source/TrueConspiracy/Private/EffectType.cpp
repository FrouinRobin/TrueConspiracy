// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectType.h"

void UEffectType::DoEffect()
{
	for(UCardEffect* effect : EffectList)
	{
		effect->Activate();
	}
}
