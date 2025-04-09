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

void ATC_MainServer::CreateNewSession(TArray<ATC_Player*> Players)
{
    ATC_GameManager* NewSession = GetWorld()->SpawnActor<ATC_GameManager>();
    NewSession->GetCurrentGameState().SetPlayer1(Players[0]);
    NewSession->GetCurrentGameState().SetPlayer2(Players[1]);
    ActiveSessions.Add(NewSession);
}

TArray<ATC_Player*> ATC_MainServer::GetAvailablePlayer()
{
    TArray<ATC_Player*> NewSessionPlayers;
    while (NewSessionPlayers.Num() < 2) 
    {
        for (ATC_Player* Player : ConnectedPlayer)
        {
            //if(Player->ConnectedState == ETC_ConnectedState::Searching)
            //{
            //  NewSessionPlayers.Add(Player);
            //  Break;
            //}
        }
    }
    return NewSessionPlayers;
}


