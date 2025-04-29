// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_EffectType.h"
#include "../TC_CardAttribute.h"
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
	TArray<ETC_CardAttribute>& GetFaceAttribute();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTexture2D* GetFaceIllustration();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UTexture2D* GetFaceBackground();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	FString GetFaceName();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	FString GetFaceDescription();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetFaceMana();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	float GetFaceScore();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetFaceTypeList(TArray<ETC_CardAttribute>& newFaceAttribute);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetFaceIllustration(UTexture2D* newImage);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetFaceBackground(UTexture2D* newImage);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetFaceDescription(FString newDescription);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetFaceMana(float newMana);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetFaceScore(float newScore);

	/* CUSTOM EVENT */

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

	/* OTHER FUNCTION */

	UFUNCTION(BlueprintCallable)
	UTC_EffectType* FindEffectOfType(TArray<UTC_EffectType*> FaceEffectList, TSubclassOf<UTC_EffectType> EffectTypeToFind);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Type")
	TArray<ETC_CardAttribute> FaceAttribute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Illustration")
	UTexture2D* FaceIllustration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Background")
	UTexture2D* FaceBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Name")
	FString FaceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Description")
	FString FaceDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Mana")
	float FaceMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Face Score")
	float FaceScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Face Effects")
	TArray<UTC_EffectType*> FaceEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Effects")
	bool _keepTarget;
};
