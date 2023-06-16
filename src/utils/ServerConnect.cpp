#include "utils/ServerConnect.h"

ServerConnect *ServerConnect::getInstance()
{
    static ServerConnect instance;
    return &instance;
};

int ServerConnect::run()
{
    initTLSConnect();

    tls_connect->event_target->addEventListener("error", [this](void *data)
    {
        onTLSConnectionInterruption(data);
    });

    tls_connect->event_target->addEventListener("connected", [this](void *data)
    {
        std::cout << "Success to connect to server" << std::endl;
        status = 1;
        connect_time = time(NULL);
        std::thread heartbeat_thread(&ServerConnect::heartbeat, this);
        heartbeat_thread.detach();
    });

    return 0;
};

void ServerConnect::initTLSConnect()
{
    ClientConfig *config = ClientConfig::getInstance();

    tls_connect = new TLSConnect(new TLSConnectOptions{
        new TCPConnectOptions{
            config->getContext()->server_ip,
            config->getContext()->server_port
        },
        new PEMCryptionOptions{
            certificate_data,
            private_key_data,
            pem_password
        }
    });
};

void ServerConnect::onTLSConnectionInterruption(void *data)
{
    EventCallbackParam *param = (EventCallbackParam *)data;
    event_target->dispatchEvent("error", param);
    std::cout << "On TLS connection interruption" << std::endl;
    closeConnect();
    ClientConfig *config = ClientConfig::getInstance();
    std::this_thread::sleep_for(std::chrono::seconds(config->getContext()->server_reconnect_interval));
    run();
};

int ServerConnect::sendMessage(const char *message)
{
    std::cout << "send message: " << message << std::endl;
    if (status == 0)
    {
        std::cerr << "Failed to send message, server is not connected." << std::endl;
        return -1;
    }

    int bytes_write = SSL_write(tls_connect->getSSL(), message, strlen(message));
    if (bytes_write <= 0)
    {
        std::cerr << "Failed to send message." << std::endl;
        closeConnect();
        return -1;
    }

    laster_send_time = time(NULL);
    return 0;
};

/**
 * 关闭套接字
 * @return 0
 */
int ServerConnect::closeConnect()
{
    status = 0;
    delete tls_connect;
    return 0;
};

/**
 * 心跳
 * @return 0
 */
int ServerConnect::heartbeat()
{
    while (status == 1)
    {
        ClientConfig *config = ClientConfig::getInstance();
        int now_time = time(NULL);
        if (now_time - laster_send_time > config->getContext()->server_heartbeat_interval)
        {
            std::cout << "start to send heartbeat" << std::endl;

            nlohmann::json j;
            j["type"] = "heartBeat";
            // msgId是消息id 全局唯一 保证不重复UUID 32位
            j["msgId"] = UUIDUtil::generateUUID();
            // 当前时间戳到毫秒 int 13位
            j["time"] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            std::cout << "send heartbeat: " << j.dump().c_str() << std::endl;

            sendMessage(j.dump().c_str());
        }
    }
    return 0;
};

int ServerConnect::processReceivedData(char* data)
{
    std::cout << "data: " << data << std::endl;
    // for (int i = 0; i < eventList.size(); i++)
    // {
    //     eventList[i]->event_callback();
    // }
    return 0;
};