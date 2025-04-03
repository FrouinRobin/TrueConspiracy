// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/TC_BoardSlot.h"
#include "Board/TC_Slot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ATC_BoardSlot::ATC_BoardSlot()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SlotVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlotVisual"));
	SlotVisual->SetupAttachment(Root);
}

void ATC_BoardSlot::InitializeSlots()
{
	if (!SlotClass || !GetWorld()) return;

	const float OffsetX = 100.f;
	const float OffsetY = 100.f;

	for (int32 Row = 0; Row < 2; Row++)
	{
		for (int32 Col = 0; Col < 2; Col++)
		{
			FVector LocalPos(Row * OffsetX, Col * OffsetY, 0.f);
			FActorSpawnParameters Params;

			ATC_Slot* NewSlot = GetWorld()->SpawnActor<ATC_Slot>(SlotClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
			if (!NewSlot) continue;

			NewSlot->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			NewSlot->SetActorRelativeLocation(LocalPos);

			Slots.Add(NewSlot);
		}
	}
}