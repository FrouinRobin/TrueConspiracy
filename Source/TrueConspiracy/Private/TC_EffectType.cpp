// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_EffectType.h"

void UTC_EffectType::DoEffect()
{
	for (UTC_CardEffect* effect : EffectList)
	{
		effect->Activate();
	}
}