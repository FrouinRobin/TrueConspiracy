// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Faces/TC_Face.h"
#include <Net/UnrealNetwork.h>


TArray<ETC_CardAttribute> UTC_Face::GetFaceAttribute()
{
	return FaceAttribute;
}

UTexture2D* UTC_Face::GetCardIllustration()
{
	return FaceIllustration;
}

UTexture2D* UTC_Face::GetCardBackground()
{
	return FaceBackground;
}

FString UTC_Face::GetCardDescription()
{
	return FaceDescription;
}

float UTC_Face::GetCardMana()
{
	return FaceMana;
}

float UTC_Face::GetCardScore()
{
	return FaceScore;
}

/*----------------------------------------------------------------------------------*/

/*SETTER*/

void UTC_Face::SetCardTypeList(TArray<ETC_CardAttribute> newFaceAttribute)
{
	FaceAttribute = newFaceAttribute;
}
void UTC_Face::SetCardIllustration(UTexture2D* newImage)
{
	FaceIllustration = newImage;
}

void UTC_Face::SetCardBackground(UTexture2D* newImage)
{
	FaceBackground = newImage;
}

void UTC_Face::SetCardDescription(FString newDescription)
{
	FaceDescription = newDescription;
}

void UTC_Face::SetCardMana(float newMana)
{
	FaceMana = newMana;
}

void UTC_Face::SetCardScore(float newScore)
{
	FaceScore = newScore;
}

/*----------------------------------------------------------------------------------*/

/* OTHER FUNCTION */

UTC_EffectType* UTC_Face::FindEffectOfType(TArray<UTC_EffectType*> FaceEffectList, TSubclassOf<UTC_EffectType> EffectTypeToFind)
{
	for (UTC_EffectType* EffectType : FaceEffectList)
	{
		if (EffectType->IsA(EffectTypeToFind))
		{
			return EffectType;
		}
	}

	return NULL;
}

void UTC_Face::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTC_Face, FaceAttribute);
	DOREPLIFETIME(UTC_Face, FaceIllustration);
	DOREPLIFETIME(UTC_Face, FaceBackground);
	DOREPLIFETIME(UTC_Face, FaceDescription);
	DOREPLIFETIME(UTC_Face, FaceMana);
	DOREPLIFETIME(UTC_Face, FaceScore);
	DOREPLIFETIME(UTC_Face, FaceEffect);
	DOREPLIFETIME(UTC_Face, _keepTarget);
}
