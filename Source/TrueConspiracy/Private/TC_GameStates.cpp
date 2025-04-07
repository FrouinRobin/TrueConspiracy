#include "TC_GameStates.h"
#include "TC_AIActions.h"
#include "TC_ActionsSystem.h"
#include "TC_Player.h"
#include "Board/TC_Plate.h"

// --- Game Format(s) ---

// --- Constructor(s) ---
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

// --- Constructor(s) ---
TC_GameStates::TC_GameStates()
{
	Init();
}

TC_GameStates::TC_GameStates(EGameModeFormat InGameModeFormat)
{
	//FormatType = InGameModeFormat;
	SetGameModeFormat(InGameModeFormat);
	Init();
}

TC_GameStates::TC_GameStates(const FGameFormat& InFormat, EGameModeFormat InFormatType)
{
	SetGameFormat(InFormat);
	SetGameModeFormat(InFormatType);
}


TC_GameStates::~TC_GameStates()
{

}

// --- Initiator(s) ---

void TC_GameStates::Init()
{
	switch (GetGameModeFormat())
	{
	case EGameModeFormat::BO3: 
		SetGameFormat(FGameFormat(3));
		break;

	case EGameModeFormat::BO5: 
		SetGameFormat(FGameFormat(5));
		break;

	case EGameModeFormat::BO7: 
		SetGameFormat(FGameFormat(7));
		break;

	case EGameModeFormat::BO9: 
		SetGameFormat(FGameFormat(9));
		break;
	}
}

void TC_GameStates::Init(const FGameFormat& InFormat)
{
	//GameFormat = InFormat;
	SetGameFormat(InFormat);
}

bool TC_GameStates::IsGameRunning() const
{
	if (GetCurrentTurn() >= GetGameFormat().MaxRounds)
		return false;
	
	if (GetPlayer1Score() >= GetGameFormat().PointsToWin || GetPlayer2Score() >= GetGameFormat().PointsToWin)
		return false;

	return true;
}

int32 TC_GameStates::GetWinner() const
{
	if (IsGameRunning()) return -1; // Game still running

	if (GetPlayer1Score() > GetPlayer2Score()) return 1;
	if (GetPlayer2Score() > GetPlayer1Score()) return 2;

	return 0; // Draw
}

// --- Generating Futur State(s) ---

TArray<TC_GameStates> TC_GameStates::GetNextStates() const
{
	return TArray<TC_GameStates>();
}

//void TC_GameStates::ApplyAction(const FAIActions& InAction, ATC_Player* InCurrentPlayer)
//{
//	// Déléguer la logique à TC_ActionsSystem
//	TC_ActionsSystem::ApplyAction(*this, InAction, InCurrentPlayer);
//}

void TC_GameStates::ApplyAction(const FAIActions& InAction)
{
	// Déléguer la logique à TC_ActionsSystem
	TC_ActionsSystem::ApplyAction(*this, InAction);
}

// --- Tool(s) Function(s) ---

TC_GameStates TC_GameStates::Clone() const
{
	//TC_GameStates clone;
	//clone._Player1Hand = _Player1Hand;
	//clone._Player2Hand = _Player2Hand;
	//clone._Player1BoardCard = _Player1BoardCard;
	//clone._Player2BoardCard = _Player2BoardCard;
	//clone.SetPlayer1Mana(GetPlayer1Mana());
	//clone.SetPlayer2Mana(GetPlayer2Mana());
	//clone.SetIsPlayer1Turn(GetIsPlayer1Turn());
	//return clone;
	
	TC_GameStates clone;
	clone.Player1->SetHand(Player1->GetHand());
	clone.Player2->SetHand(Player2->GetHand());
	//clone._Player1BoardCard = _Player1BoardCard;
	//clone._Player2BoardCard = _Player2BoardCard;
	clone.Player1->SetPlayerMana(Player1->GetPlayerMana());
	clone.Player2->SetPlayerMana(Player2->GetPlayerMana());
	clone.SetIsPlayer1Turn(GetIsPlayer1Turn());
	return clone;
}

// --- Setter(s) / Getter(s) ---

void TC_GameStates::SetGameFormat(FGameFormat InGameFormat)
{
	_GameFormat = InGameFormat;
}

FGameFormat TC_GameStates::GetGameFormat() const
{
	return _GameFormat;
}

void TC_GameStates::SetGameModeFormat(EGameModeFormat InGameModeFormat)
{
	_FormatType = InGameModeFormat;
}

EGameModeFormat TC_GameStates::GetGameModeFormat() const
{
	return _FormatType;
}

void TC_GameStates::SetCurrentTurn(int32 InTurn)
{
	_CurrentTurn = InTurn;
}

int32 TC_GameStates::GetCurrentTurn() const
{
	return _CurrentTurn;
}

void TC_GameStates::SetPlayer1Score(int32 InScore)
{
	_Player1Score = InScore;
}

int32 TC_GameStates::GetPlayer1Score() const
{
	return _Player1Score;
}

void TC_GameStates::SetPlayer2Score(int32 InScore)
{
	_Player2Score = InScore;
}

int32 TC_GameStates::GetPlayer2Score() const
{
	return _Player2Score;
}

//void TC_GameStates::SetPlayer1Mana(int32 InMana)
//{
//	_Player1Mana = InMana;
//}
//
//int32 TC_GameStates::GetPlayer1Mana() const
//{
//	return _Player1Mana;
//}
//
//void TC_GameStates::SetPlayer2Mana(int32 InMana)
//{
//	_Player2Mana = InMana;
//}
//
//int32 TC_GameStates::GetPlayer2Mana() const
//{
//	return _Player2Mana;
//}

void TC_GameStates::SetIsPlayer1Turn(bool InIsPlayer1Turn)
{
	_IsPlayer1Turn = InIsPlayer1Turn;
}

bool TC_GameStates::GetIsPlayer1Turn() const
{
	return _IsPlayer1Turn;
}
