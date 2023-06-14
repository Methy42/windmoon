#include "utils/TLSConnect.h"

TLSConnect::TLSConnect(TLSConnectOptions *options)
{
    tcp_connect = new TCPConnect(options->tcp_options);
    if (tcp_connect->getStatus() == -1) {
        status = -1;
        return;
    }

    jks_cryption = new JKSCryption(options->jks_options);

    ssl = SSL_new(jks_cryption->getCtx());
    SSL_set_fd(ssl, tcp_connect->getSockfd());
    if (SSL_connect(ssl) == -1) {
        std::cerr << "Failed to connect to server." << std::endl;
        status = -1;
        return;
    }

    status = 1;
}

TLSConnect::~TLSConnect()
{
    SSL_shutdown(ssl);
    SSL_free(ssl);
    delete tcp_connect;
    delete jks_cryption;
}

SSL* TLSConnect::getSSL()
{
    return ssl;
}

int TLSConnect::getStatus()
{
    return status;
}