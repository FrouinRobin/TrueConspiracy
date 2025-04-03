// === ATC_BoardZone.cpp ===
#include "Board/TC_BoardZone.h"
#include "Board/TC_BoardSlot.h"
#include "Board/TC_Slot.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

ATC_BoardZone::ATC_BoardZone()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ZoneVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZoneVisual"));
	ZoneVisual->SetupAttachment(Root);
}

void ATC_BoardZone::BeginPlay()
{
	Super::BeginPlay();
}

void ATC_BoardZone::InitializeBoardSlots(TSubclassOf<ATC_BoardSlot> BoardSlotClass, TSubclassOf<ATC_Slot> SlotClass)
{
	if (!BoardSlotClass || !SlotClass || !GetWorld()) return;

	const float BoardSlotSpacingX = 400.f;

	for (int32 ColIndex = 0; ColIndex < 3; ColIndex++)
	{
		FVector BoardSlotLocation = FVector(ColIndex * BoardSlotSpacingX, 0.f, 0.f);
		FActorSpawnParameters Params;

		ATC_BoardSlot* NewBoardSlot = GetWorld()->SpawnActor<ATC_BoardSlot>(BoardSlotClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		if (!NewBoardSlot) continue;

		NewBoardSlot->OwnerPlayerIndex = OwnerPlayerIndex;
		NewBoardSlot->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		NewBoardSlot->SetActorRelativeLocation(BoardSlotLocation);
		NewBoardSlot->SlotClass = SlotClass;
		NewBoardSlot->InitializeSlots();

		BoardSlots.Add(NewBoardSlot);
	}
}