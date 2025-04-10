#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TC_GameStates.h"

#include "TC_GameManager.generated.h"

class ATC_Plate;

struct FAIActions;

UCLASS()
class TRUECONSPIRACY_API ATC_GameManager : public AGameMode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATC_Plate* Plate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATC_Player*> Players;
private:
	TC_GameStates _CurrentGameState;

protected:
	virtual void BeginPlay() override;

public:
	ATC_GameManager();

	virtual void Tick(float DeltaTime) override;

	// === GAME CONTROL ===
	void InitGame();
	void CoinFlip();
	UFUNCTION(BlueprintCallable)
	void StartGame(EGameModeFormat InFormat, TArray<ATC_Player*> InPlayers);
	void StartTurn();
	void StartPhase();
	void EndPhase();
	void SwitchPhase();
	void PlayAction(const FAIActions& InActionToPlay);
	void EndTurn();
	void EndGame();

	// --- Setter(s) / Getter(s) ---
	void SetCurrentGameState(TC_GameStates InCurrentGameState);
	TC_GameStates& GetCurrentGameState();
};