#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <nlohmann/json.hpp>

class ClientConfig
{
private:
    // Privatizing constructors and destructors ensures that instances can only be obtained through the getInstance method
    ClientConfig();
    ~ClientConfig();

    std::string server_ip;
    int server_port;
    int server_heartbeat_interval;

    int loadConfig();
    int saveConfig();

public:
    static ClientConfig* getInstance();

    // Prohibit copying constructors and copying assignment operators
    ClientConfig(const ClientConfig&) = delete;
    ClientConfig& operator=(const ClientConfig&) = delete;

    std::string getServerIp();
    int getServerPort();
    int getServerHeartbeatInterval();

    int setServerIp(std::string server_ip);
    int setServerPort(int server_port);
    int setServerHeartbeatInterval(int server_heartbeat_interval);
};

#endif // CLIENT_CONFIG_H