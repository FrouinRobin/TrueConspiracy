// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_Board.h"

// Sets default values
ATC_Board::ATC_Board()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATC_Board::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATC_Board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

