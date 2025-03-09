// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_Face.h"
#include "TC_AttackFace.h"
#include "TC_DefendFace.h"
#include "TC_CardType.h"
#include "TC_Card.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_Card : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATC_Card();

	UPROPERTY(EditAnywhere, Category = "Card Mesh")
	UStaticMeshComponent* CardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Faces")
	UTC_AttackFace* CardAttackFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Faces")
	UTC_DefendFace* CardDefendFace;



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
	TArray<ETC_CardType> GetCardTypeList();

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
	void SetCardTypeList(TArray<ETC_CardType> newTypeList);

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

	UTC_Face* _cardCurrentFace;
	TArray<UTC_Face*> _cardFaceList;

	ETC_CardType _cardType;
	TArray<ETC_CardType> _cardTypeList;

	UTexture2D* _cardIllustration;
	UTexture2D* _cardBackground;
	FString _cardDescription;

	float _cardMana;
	float _cardScore;

};
