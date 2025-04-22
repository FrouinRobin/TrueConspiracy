#include "TC_TCPComponent.h"
#include "TC_TCPClient.h"

UTC_TCPComponent::UTC_TCPComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    _tcpClient = nullptr;
}

void UTC_TCPComponent::BeginPlay()
{
    Super::BeginPlay();

    // Start pinging every 5 seconds
    GetWorld()->GetTimerManager().SetTimer(_pingTimerHandle, this, &UTC_TCPComponent::_sendPing, 0.1f, true);
}

void UTC_TCPComponent::_sendPing()
{
    if (_tcpClient && CanPing)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("PING DESU"));
        _tcpClient->SendMessage(L"ping\n");
    }
}

void UTC_TCPComponent::StartClient(const FString& ServerIP, int32 ServerPort)
{
    if (!_tcpClient)
    {
        _tcpClient = new FTC_TCPClient(ServerIP, ServerPort);
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

    Super::EndPlay(EndPlayReason);
}
