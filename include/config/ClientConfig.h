#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <nlohmann/json.hpp>

struct ClientConfigContext
{
    char* server_ip; // Server IP
    int server_port; // Server port
    int server_heartbeat_interval; // Heartbeat interval
    int server_reconnect_interval; // Reconnect interval
    int connection_blocking_waiting_time; // Connection blocking waiting time
    int server_receive_interval; // Server receive interval
};

class ClientConfig
{
private:
    // Privatizing constructors and destructors ensures that instances can only be obtained through the getInstance method
    ClientConfig();
    ~ClientConfig();

    ClientConfigContext* context;

    int loadConfig();
    int saveConfig();

public:
    static ClientConfig* getInstance();

    // Prohibit copying constructors and copying assignment operators
    ClientConfig(const ClientConfig&) = delete;
    ClientConfig& operator=(const ClientConfig&) = delete;

    ClientConfigContext* getContext();

    int setContext(ClientConfigContext* context);
};

#endif // CLIENT_CONFIG_H