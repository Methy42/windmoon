#ifndef TCP_CONNECT_H
#define TCP_CONNECT_H

#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include "utils/EventTarget.h"

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
    EventTarget* event_target;
private:
    int sockfd;
};

#endif // TCP_CONNECT_H