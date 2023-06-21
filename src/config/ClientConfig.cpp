#include "config/ClientConfig.h"

ClientConfig* ClientConfig::getInstance()
{
    static ClientConfig instance;
    return &instance;
}

ClientConfig::ClientConfig(/* args */)
{
    loadConfig();
}

ClientConfig::~ClientConfig()
{
    std::cout << "ClientConfig::~ClientConfig()" << std::endl;
}

int ClientConfig::loadConfig()
{
    std::ifstream i("resources/config/client.json");
    nlohmann::json j;
    i >> j;

    context = new ClientConfigContext();

    std::string server_ip = j["server_ip"].get<std::string>();
    context->server_ip = new char[server_ip.length() + 1];
    strcpy(context->server_ip, server_ip.c_str());
    context->server_port = j["server_port"].get<int>();
    context->server_heartbeat_interval = j["server_heartbeat_interval"].get<int>();
    context->server_reconnect_interval = j["server_reconnect_interval"].get<int>();
    context->connection_blocking_waiting_time = j["connection_blocking_waiting_time"].get<int>();
    context->server_receive_interval = j["server_receive_interval"].get<int>();
    context->client_log_level = j["client_log_level"].get<int>();

    return 0;
}

int ClientConfig::saveConfig()
{
    nlohmann::json j;
    j["server_ip"] = context->server_ip;
    j["server_port"] = context->server_port;
    j["server_heartbeat_interval"] = context->server_heartbeat_interval;
    j["server_reconnect_interval"] = context->server_reconnect_interval;
    j["connection_blocking_waiting_time"] = context->connection_blocking_waiting_time;
    j["server_receive_interval"] = context->server_receive_interval;
    j["client_log_level"] = context->client_log_level;

    std::ofstream o("config/client.json");
    o << std::setw(4) << j << std::endl;

    return 0;
}

ClientConfigContext* ClientConfig::getContext()
{
    return context;
}

int ClientConfig::setContext(ClientConfigContext* context)
{
    this->context = context;
    saveConfig();
    return 0;
}