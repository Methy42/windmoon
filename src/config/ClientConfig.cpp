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

    server_ip = j["server_ip"].get<std::string>();
    server_port = j["server_port"].get<int>();
    client_jks_file_path = j["client_jks_file_path"].get<std::string>();
    client_jks_password = j["client_jks_password"].get<std::string>();
    server_heartbeat_interval = j["server_heartbeat_interval"].get<int>();

    return 0;
}

int ClientConfig::saveConfig()
{
    nlohmann::json j;
    j["server_ip"] = server_ip;
    j["server_port"] = server_port;
    j["client_jks_file_path"] = client_jks_file_path;
    j["client_jks_password"] = client_jks_password;
    j["server_heartbeat_interval"] = server_heartbeat_interval;

    std::ofstream o("config/client.json");
    o << std::setw(4) << j << std::endl;

    return 0;
}

std::string ClientConfig::getServerIp()
{
    return server_ip;
}

int ClientConfig::getServerPort()
{
    return server_port;
}

std::string ClientConfig::getClientJksFilePath()
{
    return client_jks_file_path;
}

std::string ClientConfig::getClientJksPassword()
{
    return client_jks_password;
}

int ClientConfig::getServerHeartbeatInterval()
{
    return server_heartbeat_interval;
}

int ClientConfig::setServerIp(std::string server_ip)
{
    this->server_ip = server_ip;
    saveConfig();
    return 0;
}

int ClientConfig::setServerPort(int server_port)
{
    this->server_port = server_port;
    saveConfig();
    return 0;
}

int ClientConfig::setClientJksFilePath(std::string client_jks_file_path)
{
    this->client_jks_file_path = client_jks_file_path;
    saveConfig();
    return 0;
}

int ClientConfig::setClientJksPassword(std::string client_jks_password)
{
    this->client_jks_password = client_jks_password;
    saveConfig();
    return 0;
}

int ClientConfig::setServerHeartbeatInterval(int server_heartbeat_interval)
{
    this->server_heartbeat_interval = server_heartbeat_interval;
    saveConfig();
    return 0;
}