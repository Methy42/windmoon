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
        Logger::getInstance()->error("TLS connect has ERROR!");
        onTLSConnectionInterruption(data);
    });

    tls_connect->event_target->addEventListener("connected", [this](void *data)
    {
        Logger::getInstance()->info("Success to connect to server");
        status = 1;
        connect_time = time(NULL);
        std::thread heartbeat_thread(&ServerConnect::heartbeat, this);
        heartbeat_thread.detach();
    });

    tls_connect->event_target->addEventListener("disconnect", [this](void *data)
    {
        Logger::getInstance()->info("TLS connect has DISCONNECTED!");
        status = 0;
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
        },
        config->getContext()->server_receive_interval
    });
};

void ServerConnect::onTLSConnectionInterruption(void *data)
{
    EventCallbackParam *param = (EventCallbackParam *)data;
    event_target->dispatchEvent("error", param);
    Logger::getInstance()->error("On TLS connection interruption");
    closeConnect();
    Logger::getInstance()->info("Try to reconnect to server");
    ClientConfig *config = ClientConfig::getInstance();
    std::this_thread::sleep_for(std::chrono::seconds(config->getContext()->server_reconnect_interval));
    run();
};

int ServerConnect::sendMessage(const char *message)
{
    if (status == 0)
    {
        Logger::getInstance()->error("Failed to send message, server is not connected.");
        return -1;
    }

    tls_connect->send(message);

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
            Logger::getInstance()->debug("Start to send heartbeat");

            nlohmann::json j;
            j["type"] = "heartBeat";
            // msgId是消息id 全局唯一 保证不重复UUID 32位
            j["msgId"] = UUIDUtil::generateUUID();
            // 当前时间戳到毫秒 int 13位
            j["time"] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            Logger::getInstance()->debug(std::string("Send heartbeat: ") + j.dump().c_str());

            sendMessage(j.dump().c_str());
        }

        // 放弃 CPU 时间片，允许其他线程或进程运行
        std::this_thread::yield();
        // 等待一段时间，避免占用 CPU 过多
        if (config->getContext()->server_heartbeat_interval > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(config->getContext()->server_heartbeat_interval - 1));
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