#ifndef TLS_CONNECT_H
#define TLS_CONNECT_H

#include "utils/JKSCryption.h"
#include "utils/TCPConnect.h"

struct TLSConnectOptions
{
    TCPConnectOptions* tcp_options;
    JKSCryptionOptions* jks_options;
};

class TLSConnect
{
public:
    TLSConnect(TLSConnectOptions *options);
    ~TLSConnect();

    SSL* getSSL();
    int getStatus();
private:
    SSL* ssl;
    int status;
    TCPConnect* tcp_connect;
    JKSCryption* jks_cryption;
};

#endif // TLS_CONNECT_H