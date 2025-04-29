// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Faces/TC_Face.h"

TArray<ETC_CardAttribute>& UTC_Face::GetFaceAttribute()
{
	return FaceAttribute;
}

UTexture2D* UTC_Face::GetFaceIllustration()
{
	return FaceIllustration;
}

UTexture2D* UTC_Face::GetFaceBackground()
{
	return FaceBackground;
}

FString UTC_Face::GetFaceName()
{
	return FaceName;
}

FString UTC_Face::GetFaceDescription()
{
	return FaceDescription;
}

float UTC_Face::GetFaceMana()
{
	return FaceMana;
}

float UTC_Face::GetFaceScore()
{
	return FaceScore;
}

/*----------------------------------------------------------------------------------*/

/*SETTER*/

void UTC_Face::SetFaceTypeList(TArray<ETC_CardAttribute>& newFaceAttribute)
{
	FaceAttribute = newFaceAttribute;
}
void UTC_Face::SetFaceIllustration(UTexture2D* newImage)
{
	FaceIllustration = newImage;
}

void UTC_Face::SetFaceBackground(UTexture2D* newImage)
{
	FaceBackground = newImage;
}

void UTC_Face::SetFaceDescription(FString newDescription)
{
	FaceDescription = newDescription;
}

void UTC_Face::SetFaceMana(float newMana)
{
	FaceMana = newMana;
}

void UTC_Face::SetFaceScore(float newScore)
{
	FaceScore = newScore;
}

/*----------------------------------------------------------------------------------*/

/* OTHER FUNCTION */

UTC_EffectType* UTC_Face::FindEffectOfType(TArray<UTC_EffectType*> FaceEffectList, TSubclassOf<UTC_EffectType> EffectTypeToFind)
{
	for (UTC_EffectType* EffectType : FaceEffectList)
	{
		if (EffectType != nullptr && EffectType->IsA(EffectTypeToFind))
		{
			return EffectType;
		}
	}

	return NULL;
}
