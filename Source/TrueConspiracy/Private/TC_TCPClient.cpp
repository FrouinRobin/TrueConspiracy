#include "TC_TCPClient.h"
#include "Async/Async.h"

FTC_TCPClient::FTC_TCPClient(const FString& InIP, int32 InPort)
    : ServerIP(InIP), ServerPort(InPort), Socket(nullptr), Thread(nullptr), bStopThread(false)
{
    Thread = FRunnableThread::Create(this, L"TCPClientThread");
    bStopThread = false;
}

FTC_TCPClient::~FTC_TCPClient()
{
    Exit();

    if (Thread)
    {
        EnsureCompletion();
        delete Thread;
        Thread = nullptr;
    }
}

bool FTC_TCPClient::Init()
{
    return Connect();
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
    Socket->SetNonBlocking(true);

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
        if (Socket && Socket->GetConnectionState() == SCS_Connected)
        {
            uint32 PendingDataSize = 0;
            if (Socket->HasPendingData(PendingDataSize))
            {
                TArray<uint8> ReceivedData;
                ReceivedData.SetNumUninitialized(PendingDataSize);

                int32 BytesRead = 0;
                if (Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), BytesRead))
                {
                    FString ReceivedString = FString(UTF8_TO_TCHAR(ReceivedData.GetData()));
                    
                    // Now process the message on game thread
                    AsyncTask(ENamedThreads::GameThread, [this, ReceivedString]()
                    {
                        // Handle it (see step 2)
                        OnMessageReceived(ReceivedString);
                    });
                }
            }
        }

        FPlatformProcess::Sleep(0.01f);
    }

    return 0;
}


void FTC_TCPClient::SendMessage(const FString& Message)
{
    if (!Socket || !Socket->GetConnectionState() == SCS_Connected) return;

    FString SendingMessage = Message + TEXT("\n");
    FTCHARToUTF8 Convert(*SendingMessage);
    int32 BytesSent = 0;
    bool bSent = Socket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);
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

    SendMessage(L"\n");

    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
}

void FTC_TCPClient::SetOnMessageReceivedCallback(TFunction<void(const FString&)> Callback)
{
    OnMessageReceivedCallback = Callback;
}

void FTC_TCPClient::OnMessageReceived(const FString& Message)
{
    if (OnMessageReceivedCallback)
    {
        OnMessageReceivedCallback(Message);
    }
}

bool FTC_TCPClient::Reconnect()
{
    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }

    return Connect();
}