// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <TC_Card.h>
#include "TC_Player.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATC_Player();

	UFUNCTION(BlueprintCallable)
	ATC_Card* GetCardFromDeckByName(FString name, bool checkAllFaces);

	UFUNCTION(BlueprintCallable)
	// To know: how IDs would work for cards
	// Would a card have an ID for both faces or would each faces have their unique IDs?
	ATC_Card* GetCardFromDeckById(FString id);

	//ATC_Card* GetCardFromDeckByCondition();

	//TArray<ATC_Card*> GetDeck();

	UFUNCTION(BlueprintCallable)
	bool AddCardToDeck(ATC_Card* card);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<ATC_Card*> _playerDeck;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _playerCamera;
	class USceneComponent* _cardAnchor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
