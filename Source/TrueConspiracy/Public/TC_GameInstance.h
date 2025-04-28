#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TC_GameStates.h"
#include "TC_GameInstance.generated.h"

UCLASS()
class TRUECONSPIRACY_API UTC_GameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	//static UTC_GameInstance* _Instance;
	UPROPERTY()
	EGameModeFormat _SelectedFormat;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<ATC_Card>> SelectedPlayerDeck;

	static UTC_GameInstance* GetInstance(UObject* InWorldContext);
	static UTC_GameInstance* GetInstanceFromWorld(UWorld* InWorld);

	UFUNCTION(BlueprintCallable)
	void SetSelectedFormat(EGameModeFormat InGameModeFormat);

	UFUNCTION(BlueprintCallable)
	EGameModeFormat GetSelectedFormat() const;
};
