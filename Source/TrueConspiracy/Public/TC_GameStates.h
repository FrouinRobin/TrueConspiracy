#pragma once

#include "CoreMinimal.h"

class ATC_Card;
struct FAIActions;

UENUM(BlueprintType)
enum class EGameModeFormat : uint8
{
	BO3,
	BO5,
	BO7,
	BO9
};

struct FGameFormat
{
	//Default values
	int32 MaxRounds = 7;
	int32 PointsToWin;

	// --- Constructor(s) ---
	FGameFormat();
	FGameFormat(int32 InMaxRounds);
	FGameFormat(int32 InMaxRounds, int32 InPointsToWin);
};

class TRUECONSPIRACY_API TC_GameStates
{
public:
	FGameFormat GameFormat;
	EGameModeFormat FormatType = EGameModeFormat::BO7;

	TArray<ATC_Card*> Player1Hand;
	TArray<ATC_Card*> Player2Hand;
	
	TArray<ATC_Card*> Player1BoardCard;
	TArray<ATC_Card*> Player2BoardCard;

	int32 CurrentTurn = 0;
	int32 Player1Score = 0;
	int32 Player2Score = 0;

	int32 Player1Mana = 0;
	int32 Player2Mana = 0;

	bool bIsPlayer1Turn = true;

	// --- Constructor(s) ---
	TC_GameStates(); //Default constructor
	TC_GameStates(EGameModeFormat InGameModeFormat);
	TC_GameStates(const FGameFormat& InFormat);
	~TC_GameStates();

	// --- Initiator(s) ---
	void Init();
	void Init(const FGameFormat& InFormat);

	bool IsGameRunning() const;
	int32 GetWinner() const; // 1 = P1, 2 = P2, 0 = égalité, -1 = en cours

	// --- Generating Futur State(s) ---
	TArray<TC_GameStates> GetNextStates() const;
	void ApplyAction(const FAIActions& InAction);

	// --- Tool(s) Function(s) ---
	TC_GameStates Clone() const;
};
