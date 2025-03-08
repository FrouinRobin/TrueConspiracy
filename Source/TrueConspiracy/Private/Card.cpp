// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>("Card Mesh", false);
	RootComponent = CardMesh;
	
	
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

/*GETTER*/

UFace* ACard::GetCardCurrentFace()
{
	return _cardCurrentFace;
}

UAttackFace* ACard::GetCardAttackFace()
{
	return CardAttackFace;
}

UDefendFace* ACard::GetCardDefendFace()
{
	return CardDefendFace;
}

TArray<UFace*> ACard::GetCardFaceList()
{
	return _cardFaceList;
}

UTexture2D* ACard::GetCardIllustration()
{
	return _cardIllustration;
}

UTexture2D* ACard::GetCardBackground()
{
	return _cardBackground;
}

FString ACard::GetCardDescription()
{
	return _cardDescription;
}

float ACard::GetCardMana()
{
	return _cardMana;
}

float ACard::GetCardScore()
{
	return _cardScore;
}

/*----------------------------------------------------------------------------------*/

/*SETTER*/

void ACard::SetCardCurrentFace(UFace* newCurrentFace)
{
	_cardCurrentFace = newCurrentFace;
}

void ACard::SetCardAttackFace(UAttackFace* newAttackFace)
{
	CardAttackFace = newAttackFace;
}

void ACard::SetCardDefendFace(UDefendFace* newDefendFace)
{
	CardDefendFace = newDefendFace;
}

void ACard::SetCardFaceList(TArray<UFace*> newFaceList)
{
	_cardFaceList = newFaceList;
}

void ACard::SetCardIllustration(UTexture2D* newImage)
{
	_cardIllustration = newImage;
}

void ACard::SetCardBackground(UTexture2D* newImage)
{
	_cardBackground = newImage;
}

void ACard::SetCardDescription(FString newDescription)
{
	_cardDescription = newDescription;
}

void ACard::SetCardMana(float newMana)
{
	_cardMana = newMana;
}

void ACard::SetCardScore(float newScore)
{
	_cardScore = newScore;
}


/*OTHER FUNCTION*/

void ACard::SwitchFace()
{
	if (_cardCurrentFace == GetCardAttackFace())
	{
		SetCardCurrentFace(GetCardDefendFace());
	}
	else if (_cardCurrentFace == GetCardDefendFace())
	{
		SetCardCurrentFace(GetCardAttackFace());
	}
}

void ACard::SwitchPhase()
{
	OnCardEndPhase();
	SwitchFace();
	OnCardStartPhase();
}
