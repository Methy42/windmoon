#ifndef TCP_CONNECT_H
#define TCP_CONNECT_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

struct TCPConnectOptions
{
    char* server_ip;
    int server_port;
};

class TCPConnect
{
public:
    TCPConnect(TCPConnectOptions *options);
    ~TCPConnect();
    int getSockfd();
    int getStatus();
private:
    int sockfd;
    int status;
};

#endif // TCP_CONNECT_H