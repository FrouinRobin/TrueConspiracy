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
	void SetCardTypeList(TArray<ETC_CardAttribute>& newFaceAttribute);
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Type", Replicated)
	TArray<ETC_CardAttribute> FaceAttribute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Illustration", Replicated)
	UTexture2D* FaceIllustration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Background", Replicated)
	UTexture2D* FaceBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Description", Replicated)
	FString FaceDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Mana", Replicated)
	float FaceMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Face Score", Replicated)
	float FaceScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Card Effects", Replicated)
	TArray<UTC_EffectType*> FaceEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Effects", Replicated)
	bool _keepTarget;
};
