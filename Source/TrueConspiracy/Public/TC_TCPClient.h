#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "Templates/Function.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

class FRunnableThread;

/**

TCP Client running in a separate thread.*/
class FTC_TCPClient : public FRunnable
{
public:
    FTC_TCPClient(const FString& InIP, int32 InPort);
    virtual ~FTC_TCPClient();

    // FRunnable interface
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

    bool Connect();
    void SendMessage(const FString& Message);
    void Shutdown();
    void EnsureCompletion();
    bool Reconnect();

    void SetOnMessageReceivedCallback(TFunction<void(const FString&)> Callback);
    void OnMessageReceived(const FString& Message);

    FString ServerIP;
    int32 ServerPort;

    FSocket* Socket;
    FRunnableThread* Thread;
    FThreadSafeBool bStopThread;

private:
    TFunction<void(const FString&)> OnMessageReceivedCallback;
};