// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cards/TC_CardType.h"
#include "Board/TC_Board.h"
#include "Board/TC_LandCardSlot.h"
#include "TC_Plate.generated.h"

UCLASS()
class TRUECONSPIRACY_API ATC_Plate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATC_Plate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "SceneRoot"/*, Replicated*/)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh"/*, Replicated*/)
	UStaticMeshComponent* PlateMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardPlayerOneAnchor"/*, Replicated*/)
	USceneComponent* BoardPlayerOneAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardPlayerOneAnchor"/*, Replicated*/)
	USceneComponent* BoardPlayerTwoAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoardPlayerOneAnchor"/*, Replicated*/)
	USceneComponent* LandCardSlotOneAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandCardSlotTwoAnchor"/*, Replicated*/)
	USceneComponent* LandCardSlotTwoAnchor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandCardSlotThreeAnchor"/*, Replicated*/)
	USceneComponent* LandCardSlotThreeAnchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandCardSlotThreeAnchor"/*, Replicated*/)
	TSubclassOf<ATC_Board> BoardBluePrint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandCardSlotThreeAnchor"/*, Replicated*/)
	TSubclassOf<ATC_LandCardSlot> LandCardSlotBluePrint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_Player* _playerOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	ATC_Player* _playerTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	TArray<ATC_Board*> _plateBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlateMesh", meta = (AllowPrivateAccess = true), Replicated)
	TArray<ATC_LandCardSlot*> _landCardSlots;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Player* GetPlayerOne();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Player* GetPlayerTwo();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_Board* GetBoardByPlayer(ATC_Player* PlayerRef);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_LandCardSlot*> GetLandCardSlots();
	UFUNCTION(BlueprintCallable, Category = "Getters")
	ATC_LandCardSlot* GetLandCardSlotAtIndex(int index);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	TArray<ATC_Board*> GetPlateBoard();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetPlayerOne(ATC_Player* newPlayerOne);
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetPlayerTwo(ATC_Player* newPlayerTwo);

	UFUNCTION(BlueprintCallable, Category = "Init")
	void Init();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	
};
