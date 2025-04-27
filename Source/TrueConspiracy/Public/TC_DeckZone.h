// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Cards/TC_Card.h"
#include "TC_DeckZone.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_DeckZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATC_DeckZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	int32 _PlayerID;

	UPROPERTY()
	TArray<ATC_Card*> _Hand;

	UPROPERTY(VisibleAnywhere, Category = "DeckZone")
	UBoxComponent* _DeckZoneCollider;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<ATC_Card*> GetHand() const { return _Hand; }

	void AddCard(ATC_Card* Card);

	void RemoveCard(ATC_Card* Card);

	ATC_Card* GetCard(float Index) const;

	ATC_Card* GetCard(ATC_Card* CardRef) const;


};
