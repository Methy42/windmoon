#ifndef TLS_CONNECT_H
#define TLS_CONNECT_H

#include <future>
#include "utils/PEMCryption.h"
#include "utils/TCPConnect.h"
#include "utils/EventTarget.h"

struct TLSConnectOptions
{
    TCPConnectOptions* tcp_options;
    PEMCryptionOptions* pem_options;
};

class TLSConnect
{
public:
    TLSConnect(TLSConnectOptions *options);
    ~TLSConnect();

    EventTarget* event_target;
    SSL* getSSL();
    void receive();
    int send(const char* message);
private:
    TLSConnectOptions *options;
    SSL* ssl;
    TCPConnect* tcp_connect;
    PEMCryption* pem_cryption;
    int status = 0;

    void initTCPConnect();
    void initPEMCryption();
};

#endif // TLS_CONNECT_H