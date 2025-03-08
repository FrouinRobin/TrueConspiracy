// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Image.h"
#include "Face.h"
#include "AttackFace.h"
#include "DefendFace.h"
#include "Card.generated.h"

UCLASS()
class TRUECONSPIRACY_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

	UPROPERTY(EditAnywhere, Category = "Card Mesh")
	UStaticMeshComponent* CardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Faces")
	UAttackFace* CardAttackFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Faces")
	UDefendFace* CardDefendFace;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/*GETTER*/

	UFUNCTION(BlueprintCallable, Category = "Getters")
	UFace* GetCardCurrentFace();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UAttackFace* GetCardAttackFace();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UDefendFace* GetCardDefendFace();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<UFace*> GetCardFaceList();
	/*UFUNCTION(BlueprintCallable, Category = "Getters")*/
	//UCardType* GetCardType();
	/*UFUNCTION(BlueprintCallable, Category = "Getters")*/
	//TArray<UCardType> GetCardTypeList();
	/*UFUNCTION(BlueprintCallable, Category = "Getters")*/
	//TArray<UCardEffect> GetCardEffectList();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTexture2D* GetCardIllustration();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTexture2D* GetCardBackground();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	FString GetCardDescription();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetCardMana();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetCardScore();


	/*SETTER*/

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardCurrentFace(UFace* newCurrentFace);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardAttackFace(UAttackFace* newAttackFace);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardDefendFace(UDefendFace* newDefendFace);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardFaceList(TArray<UFace*> newFaceList);
	/*UFUNCTION(BlueprintCallable, Category = "Setters")*/
	//UCardType* GetCardType();
	/*UFUNCTION(BlueprintCallable, Category = "Setters")*/
	//TArray<UCardType> GetCardTypeList();
	/*UFUNCTION(BlueprintCallable, Category = "Setters")*/
	//TArray<UCardEffect> GetCardEffectList();
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardIllustration(UTexture2D* newImage);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardBackground(UTexture2D* newImage);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardDescription(FString newDescription);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardMana(float newMana);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCardScore(float newScore);

	
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

private:

	UFace* _cardCurrentFace;
	TArray<UFace*> _cardFaceList;
	
	//UCardType* _cardType;
	//TArray<UCardType> _cardTypes;

	UTexture2D* _cardIllustration;
	UTexture2D* _cardBackground;
	FString _cardDescription;

	float _cardMana;
	float _cardScore;

};
