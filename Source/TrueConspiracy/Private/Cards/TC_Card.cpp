// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/TC_Card.h"
#include "TC_Player.h"
#include <UObject/UnrealTypePrivate.h>

ATC_Card::ATC_Card()
{
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
	
	//switch (_cardPlayer->GetPlayerPhaseState())
	//{
	//	case(ETC_PhaseState::Attack):
	//	{
	//		SetCardCurrentFace(CardDefendFace);
	//		break;
	//	}
	//	case(ETC_PhaseState::Defense):
	//	{
	//		SetCardCurrentFace(CardAttackFace);
	//		break;
	//	}
	//default:
	//	break;
	//}
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

TArray<UTC_Face*>& ATC_Card::GetCardFaceList()
{
	return _cardFaceList;
}

ETC_CardType ATC_Card::GetCardType()
{
	return _cardType;
}

TArray<ETC_CardAttribute>& ATC_Card::GetCardAttribute()
{
	return _cardAttribute;
}

ETC_CardID ATC_Card::GetCardID()
{
	return _cardId;
}

FString ATC_Card::GetCardName()
{
	return _cardName;
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
	_cardCurrentFace = newCurrentFace; // Met � jour d'abord !

	SetCardMaxMana(_cardCurrentFace->GetCardMana());
	SetCardCurrentMana(_cardCurrentFace->FaceMana); // Reset complet sur les nouvelles valeurs
	SetCardMaxScore(_cardCurrentFace->FaceScore);
	SetCardCurrentScore(_cardCurrentFace->FaceScore);

	GetCardAttribute().Empty();
	SetCardAttributeList(newCurrentFace->FaceAttribute);
	SetCardDescription(newCurrentFace->FaceDescription);
	OnChangeStats();
}

void ATC_Card::SetCardAttackFace(UTC_AttackFace* newAttackFace)
{
	CardAttackFace = newAttackFace;
}

void ATC_Card::SetCardDefendFace(UTC_DefendFace* newDefendFace)
{
	CardDefendFace = newDefendFace;
}

void ATC_Card::SetCardFaceList(TArray<UTC_Face*>& newFaceList)
{
	_cardFaceList = newFaceList;
}

void ATC_Card::SetCardType(ETC_CardType newType)
{
	_cardType = newType;
	OnChangeStats();
}

void ATC_Card::SetCardAttributeList(TArray<ETC_CardAttribute>& newAttributeList)
{
	_cardAttribute = newAttributeList;
	OnChangeStats();
}

void ATC_Card::SetCardID(ETC_CardID newID)
{
	_cardId = newID;
}

void ATC_Card::SetCardName(FString newName)
{
	_cardName = newName;
	OnChangeStats();
}

void ATC_Card::SetCardIllustration(UTexture2D* newImage)
{
	_cardIllustration = newImage;
	OnChangeStats();
}

void ATC_Card::SetCardBackground(UTexture2D* newImage)
{
	_cardBackground = newImage;
	OnChangeStats();
}

void ATC_Card::SetCardDescription(FString newDescription)
{
	_cardDescription = newDescription;
	OnChangeStats();
}

void ATC_Card::SetCardMaxMana(float newMana)
{
	_cardMaxMana = newMana;
}

void ATC_Card::SetCardCurrentMana(float newMana)
{
	_cardCurrentMana = newMana;
	OnChangeStats();
}

void ATC_Card::SetCardMaxScore(float newScore)
{
	_cardMaxScore = newScore;
}

void ATC_Card::SetCardCurrentScore(float newScore)
{
	_cardCurrentScore = newScore;
	OnChangeStats();
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
		break;
	case(ETC_PhaseState::Defense):
		SetCardCurrentFace(GetCardDefendFace());
		break;
	}
}

void ATC_Card::AssignCardMaterialsAndTextures(
	UMaterialInterface* InAttackMaterial, FName InAttackTextureParam, UTexture2D* InAttackTexture,
	UMaterialInterface* InDefenseMaterial, FName InDefenseTextureParam, UTexture2D* InDefenseTexture)
{
	UMaterialInstanceDynamic* LocalAttackMaterialInstance = UMaterialInstanceDynamic::Create(InAttackMaterial, this);
	UMaterialInstanceDynamic* LocalDefenseMaterialInstance = UMaterialInstanceDynamic::Create(InDefenseMaterial, this);

	if (LocalAttackMaterialInstance && InAttackTexture)
	{
		LocalAttackMaterialInstance->SetTextureParameterValue(InAttackTextureParam, InAttackTexture);
		CardMesh->SetMaterial(0, LocalAttackMaterialInstance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack texture is not valid."));
	}

	if (LocalDefenseMaterialInstance && InDefenseTexture)
	{
		LocalDefenseMaterialInstance->SetTextureParameterValue(InDefenseTextureParam, InDefenseTexture);
		CardMesh->SetMaterial(2, LocalDefenseMaterialInstance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Defense texture is not valid."));
	}
}

void ATC_Card::SetTexture()
{
	OnCardSetTexture();
}

void ATC_Card::UpdateCardUIFunc(FTC_CardDataStruct CardData, UTC_CardIfoGameWiget* widget)
{
	widget->OnUpdateCardData(CardData);
}

// In any world, those two functions would be a bad idea
// But we're out of time, I'm not redoing half the targetting logic
UTC_EffectType* ATC_Card::GetWaitingEffectFromBlueprint()
{
	FProperty* prop = GetClass()->FindPropertyByName(TEXT("WaitingEffect"));
	if (!prop)
		prop = GetClass()->FindPropertyByName(TEXT("Waiting Effect"));

	if (!prop) return nullptr;

	FClassProperty* ClassProp = CastField<FClassProperty>(prop);
	if (!ClassProp) return nullptr;

	UClass* WaitingEffectClass = Cast<UClass>(ClassProp->GetPropertyValue_InContainer(this));
	if (!WaitingEffectClass) return nullptr;

	return WaitingEffectClass->GetDefaultObject<UTC_EffectType>();
}
void ATC_Card::ResetWaitingEffectInBlueprint()
{
	FProperty* prop = GetClass()->FindPropertyByName(TEXT("WaitingEffect"));
	if (!prop)
		prop = GetClass()->FindPropertyByName(TEXT("Waiting Effect"));

	if (!prop) return;

	if (FClassProperty* ClassProp = CastField<FClassProperty>(prop))
	{
		ClassProp->SetPropertyValue_InContainer(this, nullptr);
	}
}
