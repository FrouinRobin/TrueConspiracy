// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_Player.h"
#include <TC_Face.h>

// Sets default values
ATC_Player::ATC_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ATC_Card* ATC_Player::GetCardFromDeckByName(FString name, bool checkAllFaces)
{
	for (ATC_Card* card : _playerDeck)
	{
		if (!checkAllFaces) {
			UTC_Face* cardFace = card->GetCardCurrentFace();

			if (/*cardFace->name == name */ false) // TODO: See how IDs and names will be implemented
				return card;
		}
		else
		{
			// Why is there a need for more than two faces I don't know but just in case
			TArray<UTC_Face*> cardFaces = card->GetCardFaceList();

			for (auto face : cardFaces)
			{
				if (/*face->name == name */ false) // TODO: Ditto
					return card;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
	return nullptr;
}

ATC_Card* ATC_Player::GetCardFromDeckById(FString id)
{
	for (ATC_Card* card : _playerDeck)
	{
		if (/*card->id == id*/ false) // TODO: See how IDs and names will be implemented
			return card;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetCardFromDeckById() did not return any card!"));
	return nullptr;
}

// Called when the game starts or when spawned
void ATC_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

