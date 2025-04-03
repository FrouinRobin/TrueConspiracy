#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_GameStates.h"

#include "TC_GameManager.generated.h"

struct FAIActions;

UCLASS()
class TRUECONSPIRACY_API ATC_GameManager : public AActor
{
	GENERATED_BODY()
private:
	TC_GameStates _CurrentGameState;

protected:
	virtual void BeginPlay() override;

public:	
	ATC_GameManager();

	virtual void Tick(float DeltaTime) override;

	// === GAME CONTROL ===
	void Init();
	void CoinFlip();
	void StartGame();
	void StartTurn();
	void PlayAction(const FAIActions& InActionToPlay);
	void EndTurn();
	void EndGame();

	// --- Setter(s) / Getter(s) ---
	void SetCurrentGameState(TC_GameStates InCurrentGameState);
	TC_GameStates GetCurrentGameState();                  // pour modification / version modifiable
};
