// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cards/Faces/TC_Face.h"
#include "Cards/Faces/TC_AttackFace.h"
#include "Cards/Faces/TC_DefendFace.h"
#include "TC_CardType.h"
#include "TC_CardAttribute.h"
#include "TC_CardID.h"
#include "TC_Card.generated.h"

class ATC_Player;

UCLASS()
class TRUECONSPIRACY_API ATC_Card : public AActor
{
	GENERATED_BODY()

public:

	ATC_Card();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Mesh")
	USceneComponent* MainAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Mesh")
	USceneComponent* CardAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Mesh")
	UStaticMeshComponent* CardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Faces")
	UTC_AttackFace* CardAttackFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Faces")
	UTC_DefendFace* CardDefendFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Properties")
	ETC_CardType _cardType;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/*GETTER*/

	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTC_Face* GetCardCurrentFace();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTC_AttackFace* GetCardAttackFace();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTC_DefendFace* GetCardDefendFace();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<UTC_Face*> GetCardFaceList();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ETC_CardType GetCardType();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ETC_CardAttribute> GetCardAttribute();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ETC_CardID GetCardID();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTexture2D* GetCardIllustration();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTexture2D* GetCardBackground();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	FString GetCardDescription();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetCardMaxMana();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetCardCurrentMana();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetCardMaxScore();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetCardCurrentScore();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Player* GetPlayer();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Slot* GetSlot();


	/*SETTER*/

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardCurrentFace(UTC_Face* newCurrentFace);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardAttackFace(UTC_AttackFace* newAttackFace);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardDefendFace(UTC_DefendFace* newDefendFace);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardFaceList(TArray<UTC_Face*> newFaceList);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardType(ETC_CardType newType);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardAttributeList(TArray<ETC_CardAttribute> newTypeList);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardID(ETC_CardID newID);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardIllustration(UTexture2D* newImage);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardBackground(UTexture2D* newImage);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardDescription(FString newDescription);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardMaxMana(float newMana);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardCurrentMana(float newMana);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardMaxScore(float newScore);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardCurrentScore(float newScore);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetPlayer(ATC_Player* newPlayer);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetSlot(ATC_Slot* newSlot);


	/*CUSTOM EVENT*/

	UFUNCTION(BlueprintImplementableEvent)
	void OnCardPlace();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCardEachTurn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCardStartPhase();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCardEndPhase();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCardStartTurn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCardEndTurn();


	/*OTHER FUNCTION*/

	UFUNCTION(BlueprintCallable)
	void SwitchFace();

	UFUNCTION(BlueprintCallable)
	void SwitchPhase();

	UFUNCTION(BlueprintCallable)
	bool CanDoEffect();

	UFUNCTION(BlueprintCallable)
	void DeactivateEffects();

	UFUNCTION(BlueprintCallable)
	void ActivateEffects();

	UFUNCTION(BlueprintCallable)
	void Init();
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	UTC_Face* _cardCurrentFace;
	TArray<UTC_Face*> _cardFaceList;

	bool _isEffectActive = true;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	ETC_CardType _cardType;*/
	TArray<ETC_CardAttribute> _cardAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	ETC_CardID _cardId;

	UTexture2D* _cardIllustration;
	UTexture2D* _cardBackground;
	FString _cardDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	uint8 _cardMaxMana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	uint8 _cardCurrentMana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	uint8 _cardMaxScore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	uint8 _cardCurrentScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	ATC_Player* _cardPlayer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card Properties", meta = (AllowPrivateAccess = true))
	ATC_Slot* _cardSlot;

};