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
#include "JKSCryption.h"
#include "config/ClientConfig.h"

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
    int status = 0;
    int sockfd;
    int laster_send_time = 0;
    std::vector<ServerConnectEvent*> eventList;
    std::thread receive_thread;
    int receive()
    {
        while (status == 1)
        {
            char buffer[1024];
            int n = recv(sockfd, buffer, sizeof(buffer), 0);
            if (n == -1) {
                std::cerr << "Failed to receive data from server." << std::endl;
                status = 0;
                return -1;
            } else if (n == 0) {
                std::cerr << "Server disconnected." << std::endl;
                status = 0;
                return -1;
            } else {
                // 将接收到的数据输出到控制台
                buffer[n] = '\0';
                processReceivedData(buffer);
            }
        }
        return 0;
    };
    int processReceivedData(char* data)
    {
        std::string decrypt_data = JKSCryption::getInstance()->decrypt(data);
        std::cout << "decrypt_data: " << decrypt_data << std::endl;
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
