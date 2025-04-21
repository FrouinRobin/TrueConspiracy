#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

class FRunnableThread;

/**
 * TCP Client running in a separate thread.
 */
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

    // Connect and send message manually
    bool Connect();
    void SendMessage(const FString& Message);
    void Shutdown();

private:
    FString ServerIP;
    int32 ServerPort;

    FSocket* Socket;
    FRunnableThread* Thread;
    FThreadSafeBool bStopThread;
};
