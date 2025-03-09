// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_EffectType.h"
#include "TC_CardType.h"
#include "TC_Face.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class TRUECONSPIRACY_API UTC_Face : public UObject
{
	GENERATED_BODY()
public:

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


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFacePlace();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFaceEachTurn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFaceStartPhase();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFaceEndPhase();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFaceStartTurn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFaceEndTurn();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Type")
	ETC_CardType FaceType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Type")
	TArray<ETC_CardType> FaceTypeList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Illustration")
	UTexture2D* FaceIllustration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Background")
	UTexture2D* FaceBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Description")
	FString FaceDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Mana")
	float FaceMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Score")
	float FaceScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Effects")
	TArray<UTC_EffectType*> FaceEffect;
};
