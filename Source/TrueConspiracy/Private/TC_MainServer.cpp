// Fill out your copyright notice in the Description page of Project Settings.


#include "TC_MainServer.h"
#include "TC_Player.h"

void ATC_MainServer::StartPlay()
{
    Super::StartPlay();

    // Code d'initialisation lorsque le serveur démarre, comme l'ajout de règles
    UE_LOG(LogTemp, Log, TEXT("Le serveur de jeu a démarré !"));
}

void ATC_MainServer::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);



    // Caster le pawn ou en faire spawn un
    ATC_Player* PlayerPawn = Cast<ATC_Player>(NewPlayer->GetPawn());
    if (!PlayerPawn)
    {
        // Spawn le pawn manuellement s’il n’y est pas
        FVector SpawnLocation = FVector::ZeroVector;
        FRotator SpawnRotation = FRotator::ZeroRotator;
        PlayerPawn = GetWorld()->SpawnActor<ATC_Player>(DefaultPawnClass, SpawnLocation, SpawnRotation);
        NewPlayer->Possess(PlayerPawn);
    }

    HandlePlayerConnection(PlayerPawn);
}

void ATC_MainServer::HandlePlayerConnection(ATC_Player* NewPlayer)
{
    if (NewPlayer)
    {
        ConnectedPlayer.Add(NewPlayer);
        UE_LOG(LogTemp, Log, TEXT("Un nouveau joueur s'est connecté !"));
    }
    if (GetAvailablePlayer().Num() == 2)
    {
        CreateNewSession(GetAvailablePlayer());
    }
}


void ATC_MainServer::CreateNewSession(TArray<ATC_Player*> Players)
{
    ATC_GameManager* NewSession = GetWorld()->SpawnActor<ATC_GameManager>();
    NewSession->StartGame(EGameModeFormat::BO3, Players);
    ActiveSessions.Add(NewSession);
}

TArray<ATC_Player*> ATC_MainServer::GetAvailablePlayer()
{
    TArray<ATC_Player*> NewSessionPlayers;
    for (ATC_Player* Player : ConnectedPlayer)
    {
        if(Player->GetPlayerConnectState() == ETC_ConnectState::Searching)
        {
          NewSessionPlayers.Add(Player);
          if (NewSessionPlayers.Num() == 2)
          {
              return NewSessionPlayers;
          }
          
        }
        else
        {
            continue;
        }
    }
    return NewSessionPlayers;
}


