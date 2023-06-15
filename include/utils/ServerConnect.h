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
#include "utils/JKSCryption.h"
#include "config/ClientConfig.h"
#include "utils/UUIDUtil.h"
#include "config/PEMConfig.h"

struct ServerConnectEvent
{
    char* event_name;
    void (*event_callback)();
};


class ServerConnect
{
private:
    // Privatizing constructors and destructors ensures that instances can only be obtained through the getInstance method
    ServerConnect() {};
    ~ServerConnect() {};
    TLSConnect* tls_connect;
    int status = 0;
    int connect_time = 0;
    int laster_send_time = 0;
    std::vector<ServerConnectEvent*> eventList;
    std::thread receive_thread;

    int receive()
    {
        std::cout << "start receive" << std::endl;
        while (status == 1)
        {
            char buffer[65535];
            memset(buffer, 0, sizeof(buffer));

            if (tls_connect == NULL)
            {
                std::cerr << "tls_connect is null" << std::endl;
                return -1;
            }

            if (tls_connect->getSSL() == NULL)
            {
                std::cerr << "ssl is null" << std::endl;
                return -1;
            }

            int bytes_read = SSL_read(tls_connect->getSSL(), buffer, sizeof(buffer));
            if (bytes_read > 0)
            {
                processReceivedData(buffer);
            }
            else
            {
                std::cerr << "Failed to receive data." << std::endl;
                closeConnect();
                return -1;
            }
        }
        return 0;
    };
    int processReceivedData(char* data)
    {
        std::cout << "data: " << data << std::endl;
        // for (int i = 0; i < eventList.size(); i++)
        // {
        //     eventList[i]->event_callback();
        // }
        return 0;
    };
    
public:
    static ServerConnect* getInstance();

    // Prohibit copying constructors and copying assignment operators
    ServerConnect(const ServerConnect&) = delete;
    ServerConnect& operator=(const ServerConnect&) = delete;

    int run();
    int sendMessage(const char* message);
    int addEvent(ServerConnectEvent* event);
    int removeEvent(int index);
    int removeAllEvent();
    int heartbeat();

    int closeConnect();
};

#endif // SERVER_CONNECT_H
