#include "TC_TCPClient.h"

FTC_TCPClient::FTC_TCPClient(const FString& InIP, int32 InPort)
    : ServerIP(InIP), ServerPort(InPort), Socket(nullptr), Thread(nullptr), bStopThread(false)
{
    Thread = FRunnableThread::Create(this, L"TCPClientThread");
    bStopThread = false;
}

FTC_TCPClient::~FTC_TCPClient()
{
    Shutdown();

    if (Thread)
    {
        EnsureCompletion();
        delete Thread;
        Thread = nullptr;
    }
}

bool FTC_TCPClient::Init()
{
    return true;
}

bool FTC_TCPClient::Connect()
{
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

    bool bIsValid;
    Addr->SetIp(*ServerIP, bIsValid);
    Addr->SetPort(ServerPort);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, L"Invalid IP address");
        return false;
    }

    Socket = SocketSubsystem->CreateSocket(NAME_Stream, L"TCPClientSocket", false);
    Socket->SetNonBlocking(true);  // optional for async

    bool bConnected = Socket->Connect(*Addr);
    if (!bConnected)
    {
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }

    return bConnected;
}

uint32 FTC_TCPClient::Run()
{
    while (!bStopThread)
    {
		FPlatformProcess::Sleep(0.01f); // Sleep to prevent busy waiting
    }

    return 0;
}

void FTC_TCPClient::SendMessage(const FString& Message)
{
    if (!Socket || !Socket->GetConnectionState() == SCS_Connected) return;

    FTCHARToUTF8 Convert(*Message);
    int32 BytesSent = 0;
    bool bSent = Socket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);

    if (!bSent)
    {
        UE_LOG(LogTemp, Warning, L"Failed to send message");
    }
}

void FTC_TCPClient::Stop()
{
    bStopThread = true;
}

void FTC_TCPClient::Exit()
{
    Shutdown();
}

void FTC_TCPClient::EnsureCompletion()
{
    Stop();
    Thread->WaitForCompletion();
}

void FTC_TCPClient::Shutdown()
{
    bStopThread = true;

    // Send an empty message (just a newline) to trigger disconnect on Python server
    SendMessage(L"\n");

    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
}