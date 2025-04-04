#pragma once

#include "CoreMinimal.h"

class ATC_Card;
struct FAIActions;
class ATC_Player;

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
private :
	FGameFormat _GameFormat;
	EGameModeFormat _FormatType = EGameModeFormat::BO7;

	//POSSEDE PAR LE PLAYER
	//TArray<ATC_Card*> _Player1Hand;
	//TArray<ATC_Card*> _Player2Hand;
	//
	////POSSEDE PAR LE PLAYER
	//TArray<ATC_Card*> _Player1BoardCard;
	//TArray<ATC_Card*> _Player2BoardCard;

	int32 _CurrentTurn = 0;
	//NOMBRE DE ROUND GAGNÉS
	int32 _Player1Score = 0;
	int32 _Player2Score = 0;

	////A clear
	//int32 _Player1Mana = 0;
	//int32 _Player2Mana = 0;

	bool _IsPlayer1Turn;

public:

	UPROPERTY()
	ATC_Player* Player1;

	UPROPERTY()
	ATC_Player* Player2;

	// --- Constructor(s) ---
	TC_GameStates(); //Default constructor
	TC_GameStates(EGameModeFormat InGameModeFormat); 
	TC_GameStates(const FGameFormat& InFormat, EGameModeFormat InFormatType);
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

	// --- Setter(s) / Getter(s) ---
	void SetGameFormat(FGameFormat InGameFormat);
	FGameFormat GetGameFormat() const;

	void SetGameModeFormat(EGameModeFormat InGameModeFormat);
	EGameModeFormat GetGameModeFormat() const;

	void SetCurrentTurn(int32 InTurn);
	int32 GetCurrentTurn() const;

	void SetPlayer1Score(int32 InScore);
	int32 GetPlayer1Score() const;

	void SetPlayer2Score(int32 InScore);
	int32 GetPlayer2Score() const;

	//void SetPlayer1Mana(int32 InMana);
	//int32 GetPlayer1Mana() const;
	//
	//void SetPlayer2Mana(int32 InMana);
	//int32 GetPlayer2Mana() const;

	void SetIsPlayer1Turn(bool InIsPlayer1Turn);
	bool GetIsPlayer1Turn() const; 

	void SetPlayer1(ATC_Player* InPlayer) { Player1 = InPlayer; }
	void SetPlayer2(ATC_Player* InPlayer) { Player2 = InPlayer; }

	ATC_Player* GetPlayer1() const { return Player1; }
	ATC_Player* GetPlayer2() const { return Player2; }

	//int32 GetCurrentPlayerID() const { return IsPlayer1Turn ? 1 : 2; }

	//int32& GetCurrentPlayerMana() { return IsPlayer1Turn ? Player1Mana : Player2Mana; }
};
