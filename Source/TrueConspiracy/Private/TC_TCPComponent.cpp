#include "TC_TCPComponent.h"
#include "TC_TCPClient.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformTime.h"

UTC_TCPComponent::UTC_TCPComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    _tcpClient = nullptr;
}

void UTC_TCPComponent::BeginPlay()
{
    Super::BeginPlay();

    // Start pinging every 5 seconds
    GetWorld()->GetTimerManager().SetTimer(_pingTimerHandle, this, &UTC_TCPComponent::_sendPing, 1.f, true);
    GetWorld()->GetTimerManager().SetTimer(_connectionCheckTimer, this, &UTC_TCPComponent::_checkConnectionStatus, 1.f, true);
}

void UTC_TCPComponent::_sendPing()
{
    if (_tcpClient && CanPing)
    {
        _tcpClient->SendMessage(L"ping");
    }
}

void UTC_TCPComponent::StartClient(const FString& ServerIP, int32 ServerPort)
{
    if (!_tcpClient)
    {
        _tcpClient = new FTC_TCPClient(ServerIP, ServerPort);
        _tcpClient->SetOnMessageReceivedCallback([this](const FString& Message)
        {
            _handleServerMessage(Message);
        });

    }
}

void UTC_TCPComponent::SendMessageToServer(const FString& Message)
{
    if (_tcpClient)
    {
        _tcpClient->SendMessage(Message);
    }
}

void UTC_TCPComponent::StopClient()
{
    if (_tcpClient)
    {
        UE_LOG(LogTemp, Error, L"Stopping TCP Client");
        _tcpClient->Stop();
        _tcpClient->Shutdown();
        delete _tcpClient;
        _tcpClient = nullptr;
    }
}

void UTC_TCPComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (_pingTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(_pingTimerHandle);
    }

    if (_tcpClient)
    {
        StopClient();
    }

    if (_connectionCheckTimer.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(_connectionCheckTimer);
    }

    Super::EndPlay(EndPlayReason);
}

void UTC_TCPComponent::_handleServerMessage(const FString& Message)
{
	FString CleanMessage = Message;
    CleanMessage = CleanMessage.Replace(TEXT("\r"), TEXT(""));
    CleanMessage = CleanMessage.TrimStartAndEnd();

    TArray<FString> Lines;
    Message.ParseIntoArrayLines(Lines);

    for (const FString& Line : Lines)
    {
        FString CleanLine = Line.TrimStartAndEnd();

        if (CleanLine.Equals("pong", ESearchCase::IgnoreCase))
        {
            UE_LOG(LogTemp, Warning, TEXT("PONG received"));
            IsConnected = true;
        }
        else if (CleanLine.StartsWith("match:"))
        {
            FString URL = CleanLine.RightChop(6);
            UE_LOG(LogTemp, Warning, TEXT("Match message: %s"), *URL);

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                PC->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Unknown message: %s"), *CleanLine);
        }
    }
}

void UTC_TCPComponent::_checkConnectionStatus()
{
    const int32 PingTimeoutSeconds = 5;

    FDateTime Now = FDateTime::UtcNow();
    FTimespan TimeSinceLastPong = Now - _lastPongTime;

    IsConnected = (TimeSinceLastPong.GetTotalSeconds() <= PingTimeoutSeconds);

    if (!IsConnected)
    {
        if (_tcpClient && (!_tcpClient->Socket ||
            _tcpClient->Socket->GetConnectionState() != SCS_Connected))
        {
            UE_LOG(LogTemp, Warning, TEXT("Connection lost, trying to reconnect..."));
            _tcpClient->Reconnect();
        }
    }
}
