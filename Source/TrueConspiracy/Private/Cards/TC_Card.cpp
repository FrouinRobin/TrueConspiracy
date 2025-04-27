// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/TC_Card.h"
#include "TC_Player.h"
#include <Net/UnrealNetwork.h>

ATC_Card::ATC_Card()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	MainAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("MainAnchor"));
	RootComponent = MainAnchor;
	CardAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("CardAnchor"));
	CardAnchor->SetupAttachment(MainAnchor);
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardMesh"));
	CardMesh->SetupAttachment(CardAnchor);


}


void ATC_Card::BeginPlay()
{
	Super::BeginPlay();

}

void ATC_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_cardPlayer)
	{
		switch (_cardPlayer->GetPlayerPhaseState())
		{
		case(ETC_PhaseState::Attack):
		{
			SetCardCurrentFace(CardDefendFace);
		}
		case(ETC_PhaseState::Defense):
		{
			SetCardCurrentFace(CardAttackFace);
		}
		default:
			break;
		}
	}
	
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

TArray<ETC_CardAttribute> ATC_Card::GetCardAttribute()
{
	return _cardAttribute;
}

ETC_CardID ATC_Card::GetCardID()
{
	return _cardId;
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

float ATC_Card::GetCardMaxMana()
{
	return _cardMaxMana;
}

float ATC_Card::GetCardCurrentMana()
{
	return _cardCurrentMana;
}

float ATC_Card::GetCardMaxScore()
{
	return _cardMaxScore;
}

float ATC_Card::GetCardCurrentScore()
{
	return _cardCurrentScore;
}

ATC_Player* ATC_Card::GetPlayer()
{
	return _cardPlayer;
}

ATC_Slot* ATC_Card::GetSlot()
{
	return _cardSlot;
}

USceneComponent* ATC_Card::GetCardAnchor()
{
	return CardAnchor;
}

FRotator ATC_Card::GetCardAnchorRotation()
{
	return CardAnchor->GetRelativeRotation();
}

/*----------------------------------------------------------------------------------*/

/*SETTER*/

void ATC_Card::SetCardCurrentFace(UTC_Face* newCurrentFace)
{
	if (newCurrentFace)
	{
		SetCardMaxMana(_cardCurrentFace->GetCardMana());
		SetCardCurrentMana(newCurrentFace->GetCardMana() - (GetCardMaxMana() - GetCardCurrentMana()));
		SetCardCurrentScore(newCurrentFace->GetCardScore() - (GetCardMaxScore() - GetCardCurrentScore()));
		GetCardAttribute().Empty();
		SetCardAttributeList(newCurrentFace->GetFaceAttribute());
		SetCardDescription(newCurrentFace->GetCardDescription());
		_cardCurrentFace = newCurrentFace;
	}
	
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

void ATC_Card::SetCardAttributeList(TArray<ETC_CardAttribute> newAttributeList)
{
	_cardAttribute = newAttributeList;
}

void ATC_Card::SetCardID(ETC_CardID newID)
{
	_cardId = newID;
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

void ATC_Card::SetCardMaxMana(float newMana)
{
	_cardMaxMana = newMana;
}

void ATC_Card::SetCardCurrentMana(float newMana)
{
	_cardCurrentMana = newMana;
}

void ATC_Card::SetCardMaxScore(float newScore)
{
	_cardMaxScore = newScore;
}

void ATC_Card::SetCardCurrentScore(float newScore)
{
	_cardCurrentScore = newScore;
}

void ATC_Card::SetPlayer(ATC_Player* newPlayer)
{
	_cardPlayer = newPlayer;
}

void ATC_Card::SetSlot(ATC_Slot* newSlot)
{
	_cardSlot = newSlot;
}

void ATC_Card::SetCardAnchorRotation(FRotator newRotation)
{
	CardAnchor->SetRelativeRotation(newRotation);
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
	SwitchFace();
}

bool ATC_Card::CanDoEffect()
{
	return _isEffectActive;
}

void ATC_Card::DeactivateEffects()
{
	_isEffectActive = false;
}

void ATC_Card::ActivateEffects()
{
	_isEffectActive = true;
}

void ATC_Card::Init()
{
	switch (GetPlayer()->GetPlayerPhaseState())
	{
	case(ETC_PhaseState::Attack):
		SetCardCurrentFace(GetCardAttackFace());
	case(ETC_PhaseState::Defense):
		SetCardCurrentFace(GetCardDefendFace());
	}
}

void ATC_Card::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ATC_Card, MainAnchor);
	//DOREPLIFETIME(ATC_Card, CardAnchor);
	DOREPLIFETIME(ATC_Card, CardMesh);
	DOREPLIFETIME(ATC_Card, CardAttackFace);
	DOREPLIFETIME(ATC_Card, CardDefendFace);
	DOREPLIFETIME(ATC_Card, _cardType);
	DOREPLIFETIME(ATC_Card, _cardCurrentFace);
	DOREPLIFETIME(ATC_Card, _cardFaceList);
	DOREPLIFETIME(ATC_Card, _isEffectActive);
	DOREPLIFETIME(ATC_Card, _cardAttribute);
	DOREPLIFETIME(ATC_Card, _cardId);
	DOREPLIFETIME(ATC_Card, _cardIllustration);
	DOREPLIFETIME(ATC_Card, _cardBackground);
	DOREPLIFETIME(ATC_Card, _cardDescription);
	DOREPLIFETIME(ATC_Card, _cardMaxMana);
	DOREPLIFETIME(ATC_Card, _cardCurrentMana);
	DOREPLIFETIME(ATC_Card, _cardMaxScore);
	DOREPLIFETIME(ATC_Card, _cardCurrentScore);
	DOREPLIFETIME(ATC_Card, _cardPlayer);
	DOREPLIFETIME(ATC_Card, _cardSlot);
}
