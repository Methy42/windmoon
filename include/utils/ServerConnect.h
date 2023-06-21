#ifndef SERVER_CONNECT_H
#define SERVER_CONNECT_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <nlohmann/json.hpp>
#include "utils/TLSConnect.h"
#include "utils/TCPConnect.h"
#include "utils/PEMCryption.h"
#include "config/ClientConfig.h"
#include "utils/UUIDUtil.h"
#include "config/PEMConfig.h"
#include "utils/Logger.h"

class ServerConnect
{
private:
    // Privatizing constructors and destructors ensures that instances can only be obtained through the getInstance method
    ServerConnect() {
        event_target = new EventTarget();
    };
    ~ServerConnect() {
        delete event_target;
    };
    TLSConnect* tls_connect;
    int status = 0;
    int connect_time = 0;
    int laster_send_time = 0;
    
public:
    static ServerConnect* getInstance();

    // Prohibit copying constructors and copying assignment operators
    ServerConnect(const ServerConnect&) = delete;
    ServerConnect& operator=(const ServerConnect&) = delete;

    EventTarget* event_target;

    int run();
    void initTLSConnect();
    void onTLSConnectionInterruption(void* data);
    int sendMessage(const char* message);
    int heartbeat();
    int processReceivedData(char* data);
    int closeConnect();
};

#endif // SERVER_CONNECT_H
