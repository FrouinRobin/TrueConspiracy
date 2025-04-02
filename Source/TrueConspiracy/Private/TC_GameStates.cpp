#include "TC_GameStates.h"
#include "TC_AIActions.h"
#include "TC_ActionsSystem.h"

// --- Game Format(s) ---
FGameFormat::FGameFormat()
{
}

FGameFormat::FGameFormat(int32 InMaxRounds)
{
	MaxRounds = InMaxRounds;
	PointsToWin = (InMaxRounds + 1 ) / 2;
}

FGameFormat::FGameFormat(int32 InMaxRounds, int32 InPointsToWin)
{
	MaxRounds = InMaxRounds;
	PointsToWin = InPointsToWin;
}

// --- Game States(s) ---
TC_GameStates::TC_GameStates()
{
	Init();
}

TC_GameStates::TC_GameStates(EGameModeFormat InGameModeFormat)
{
	FormatType = InGameModeFormat;
	Init();
}

TC_GameStates::TC_GameStates(const FGameFormat& InFormat)
{
	Init(InFormat);
}

TC_GameStates::~TC_GameStates()
{

}

void TC_GameStates::Init()
{
	switch (FormatType)
	{
	case EGameModeFormat::BO3: 
		GameFormat = FGameFormat(3); 
		break;

	case EGameModeFormat::BO5: 
		GameFormat = FGameFormat(5); 
		break;

	case EGameModeFormat::BO7: 
		GameFormat = FGameFormat(7); 
		break;

	case EGameModeFormat::BO9: 
		GameFormat = FGameFormat(9); 
		break;
	}
}

void TC_GameStates::Init(const FGameFormat& InFormat)
{
	GameFormat = InFormat;
}

bool TC_GameStates::IsGameRunning() const
{
	if (CurrentTurn >= GameFormat.MaxRounds)
		return false;
	
	if (Player1Score >= GameFormat.PointsToWin || Player2Score >= GameFormat.PointsToWin)
		return false;

	return true;
}

int32 TC_GameStates::GetWinner() const
{
	if (IsGameRunning()) return -1; // Game still running

	if (Player1Score > Player2Score) return 1;
	if (Player2Score > Player1Score) return 2;

	return 0; // Draw
}

TArray<TC_GameStates> TC_GameStates::GetNextStates() const
{
	return TArray<TC_GameStates>();
}

void TC_GameStates::ApplyAction(const FAIActions& InAction)
{
	// Déléguer la logique à TC_ActionsSystem
	TC_ActionsSystem::ApplyAction(*this, InAction);
}

TC_GameStates TC_GameStates::Clone() const
{
	TC_GameStates clone;
	clone.Player1Hand = Player1Hand;
	clone.Player2Hand = Player2Hand;
	clone.Player1BoardCard = Player1BoardCard;
	clone.Player2BoardCard = Player2BoardCard;
	clone.Player1Mana = Player1Mana;
	clone.Player2Mana = Player2Mana;
	clone.bIsPlayer1Turn = bIsPlayer1Turn;
	return clone;
}