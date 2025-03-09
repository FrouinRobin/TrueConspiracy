// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_Card.h"

// Sets default values
ATC_Card::ATC_Card()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>("Card Mesh", false);
	RootComponent = CardMesh;


}

// Called when the game starts or when spawned
void ATC_Card::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATC_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*GETTER*/

UTC_Face* ATC_Card::GetCardCurrentFace()
{
	return _cardCurrentFace;
}

UTC_AttackFace* ATC_Card::GetCardAttackFace()
{
	return CardAttackFace;
}

UTC_DefendFace* ATC_Card::GetCardDefendFace()
{
	return CardDefendFace;
}

TArray<UTC_Face*> ATC_Card::GetCardFaceList()
{
	return _cardFaceList;
}

ETC_CardType ATC_Card::GetCardType()
{
	return _cardType;
}

TArray<ETC_CardType> ATC_Card::GetCardTypeList()
{
	return _cardTypeList;
}

UTexture2D* ATC_Card::GetCardIllustration()
{
	return _cardIllustration;
}

UTexture2D* ATC_Card::GetCardBackground()
{
	return _cardBackground;
}

FString ATC_Card::GetCardDescription()
{
	return _cardDescription;
}

float ATC_Card::GetCardMana()
{
	return _cardMana;
}

float ATC_Card::GetCardScore()
{
	return _cardScore;
}

/*----------------------------------------------------------------------------------*/

/*SETTER*/

void ATC_Card::SetCardCurrentFace(UTC_Face* newCurrentFace)
{
	_cardCurrentFace = newCurrentFace;
}

void ATC_Card::SetCardAttackFace(UTC_AttackFace* newAttackFace)
{
	CardAttackFace = newAttackFace;
}

void ATC_Card::SetCardDefendFace(UTC_DefendFace* newDefendFace)
{
	CardDefendFace = newDefendFace;
}

void ATC_Card::SetCardFaceList(TArray<UTC_Face*> newFaceList)
{
	_cardFaceList = newFaceList;
}

void ATC_Card::SetCardType(ETC_CardType newType)
{
	_cardType = newType;
}

void ATC_Card::SetCardTypeList(TArray<ETC_CardType> newTypeList)
{
	_cardTypeList = newTypeList;
}

void ATC_Card::SetCardIllustration(UTexture2D* newImage)
{
	_cardIllustration = newImage;
}

void ATC_Card::SetCardBackground(UTexture2D* newImage)
{
	_cardBackground = newImage;
}

void ATC_Card::SetCardDescription(FString newDescription)
{
	_cardDescription = newDescription;
}

void ATC_Card::SetCardMana(float newMana)
{
	_cardMana = newMana;
}

void ATC_Card::SetCardScore(float newScore)
{
	_cardScore = newScore;
}


/*OTHER FUNCTION*/

void ATC_Card::SwitchFace()
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

void ATC_Card::SwitchPhase()
{
	OnCardEndPhase();
	SwitchFace();
	OnCardStartPhase();
}

