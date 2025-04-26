// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_DeckZone.h"
#include "Components/BoxComponent.h"

// Sets default values
ATC_DeckZone::ATC_DeckZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Overlaps Collider
	_DeckZoneCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DeckZoneCollider"));
	RootComponent = _DeckZoneCollider;

	
	_DeckZoneCollider->OnComponentBeginOverlap.AddDynamic(this, &ATC_DeckZone::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ATC_DeckZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATC_DeckZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Vérifie si l'acteur est une carte
	ATC_Card* Card = Cast<ATC_Card>(OtherActor);
	if (Card)
	{
		AddCard(Card);
	}
}

// Called every frame
void ATC_DeckZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATC_DeckZone::AddCard(ATC_Card* Card)
{
	if (Card && !_Hand.Contains(Card))
	{
		_Hand.Add(Card);
		UE_LOG(LogTemp, Warning, TEXT("Carte ajoutee a la main."));
	}
}

void ATC_DeckZone::RemoveCard(ATC_Card* Card)
{
	if (Card && _Hand.Contains(Card))
	{
		_Hand.Remove(Card);
		UE_LOG(LogTemp, Warning, TEXT("Carte retiree de la main."));
	}
}

ATC_Card* ATC_DeckZone::GetCard(float Index) const
{
	if (_Hand.IsValidIndex(static_cast<int32>(Index)))
	{
		return _Hand[static_cast<int32>(Index)];
	}
	return nullptr;
}

ATC_Card* ATC_DeckZone::GetCard(ATC_Card* CardRef) const
{
	if (_Hand.Contains(CardRef))
	{
		return CardRef;
	}
	return nullptr;
}

