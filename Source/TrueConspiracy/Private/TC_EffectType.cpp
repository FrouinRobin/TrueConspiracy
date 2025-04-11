// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_EffectType.h"

void UTC_EffectType::DoEffect(ATC_Card* Caster)
{
	for (UTC_CardEffect* effect : EffectList)
	{
		effect->Activate(Caster);
	}
}

bool UTC_EffectType::DoesEffectRequireTarget()
{
	for (UTC_CardEffect* effect : EffectList)
	{
		if (effect->EffectLocalisation == ETC_EffectLocalisation::Target)
			return true;
	}
	return false;
}
