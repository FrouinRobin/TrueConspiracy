// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_MainServer.h"
#include "TC_Player.h"

void ATC_MainServer::StartPlay()
{
    Super::StartPlay();

    // Code d'initialisation lorsque le serveur démarre, comme l'ajout de règles
    UE_LOG(LogTemp, Log, TEXT("Le serveur de jeu a démarré !"));
}

void ATC_MainServer::HandlePlayerConnection(ATC_Player* NewPlayer)
{
    if (NewPlayer)
    {
        // Ajouter le joueur à la session de jeu
        UE_LOG(LogTemp, Log, TEXT("Un nouveau joueur s'est connecté !"));
        // Par exemple, tu peux créer un acteur de joueur ici
    }
}

int32 ATC_MainServer::GetAvailablePort()
{
	return 7777 + ActiveSessions.Num();
}

void ATC_MainServer::CreateNewSession(const TArray<FString>& Players)
{
	int32 Port = GetAvailablePort();
	if (Port == -1)
		return;

	FGuid NewSessionGUID = FGuid::NewGuid();
	FString SessionID = NewSessionGUID.ToString(EGuidFormats::Digits);

	FString ExePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("/Binaries/Win64/GameSession.exe"));

	FString Params = FString::Printf(TEXT("%s -log -port=%d"), *SessionID, Port);

	FProcHandle Handle = FPlatformProcess::CreateProc(
		*ExePath,
		*Params,
		true, false, false,
		nullptr, 0,
		nullptr, nullptr
	);

	if (!Handle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to launch GameSession server for Session %s."), *SessionID);
		return;
	}

	FSessionInfo NewSession;
	NewSession.SessionID = SessionID;
	NewSession.Port = Port;
	NewSession.PlayerIDs = Players;
	NewSession.bIsRunning = true;

	ActiveSessions.Add(NewSession);

	UE_LOG(LogTemp, Log, TEXT("Launched session %s on port %d."), *SessionID, Port);
}


