// Fill out your copyright notice in the Description page of Project Settings.


#include "Face.h"

/*GETTER*/

UTexture2D* UFace::GetCardIllustration()
{
	return FaceIllustration;
}

UTexture2D* UFace::GetCardBackground()
{
	return FaceBackground;
}

FString UFace::GetCardDescription()
{
	return FaceDescription;
}

float UFace::GetCardMana()
{
	return FaceMana;
}

float UFace::GetCardScore()
{
	return FaceScore;
}

/*----------------------------------------------------------------------------------*/

/*SETTER*/

void UFace::SetCardIllustration(UTexture2D* newImage)
{
	FaceIllustration = newImage;
}

void UFace::SetCardBackground(UTexture2D* newImage)
{
	FaceBackground = newImage;
}

void UFace::SetCardDescription(FString newDescription)
{
	FaceDescription = newDescription;
}

void UFace::SetCardMana(float newMana)
{
	FaceMana = newMana;
}

void UFace::SetCardScore(float newScore)
{
	FaceScore = newScore;
}