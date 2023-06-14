#include "utils/ServerConnect.h"

ServerConnect* ServerConnect::getInstance()
{
    static ServerConnect instance;
    return &instance;
};

int ServerConnect::run()
{
    ClientConfig* config = ClientConfig::getInstance();

    std::string server_ip = config->getServerIp();
    char* ip_str = const_cast<char*>(server_ip.c_str());

    tls_connect = new TLSConnect(new TLSConnectOptions {
        new TCPConnectOptions {
            ip_str,
            config->getServerPort()
        },
        new JKSCryptionOptions {
            certificate_data,
            private_key_data,
            pem_password
        }
    });

    if (tls_connect->getStatus() == -1)
    {
        std::cerr << "Failed to connect to server." << std::endl;
        return -1;
    }

    status = 1;

    // 接收数据
    receive_thread = std::thread(&ServerConnect::receive, this);

    // 开始心跳
    heartbeat();

    return 0;
};

int ServerConnect::sendMessage(const char* message)
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
 * 添加事件
 * @param event 事件
 * @return 事件索引
*/
int ServerConnect::addEvent(ServerConnectEvent* event)
{
    eventList.push_back(event);
    return eventList.size() - 1;
};

/**
 * 移除事件
 * @param index 事件索引
 * @return 0
*/
int ServerConnect::removeEvent(int index)
{
    eventList.erase(eventList.begin() + index);
    return 0;
};

/**
 * 移除所有事件
 * @return 0
*/
int ServerConnect::removeAllEvent()
{
    eventList.clear();
    return 0;
};

/**
 * 关闭套接字
 * @return 0
*/
int ServerConnect::closeConnect()
{
    status = 0;
    removeAllEvent();
    return 0;
};

/**
 * 心跳
 * @return 0
*/
int ServerConnect::heartbeat()
{
    std::cout << "start heartbeat" << std::endl;
    if (status == 1)
    {
        ClientConfig* config = ClientConfig::getInstance();
        int now_time = time(NULL);
        if (now_time - laster_send_time > config->getServerHeartbeatInterval())
        {
            std::cout << "start to send heartbeat" << std::endl;

            nlohmann::json j;
            j["type"] = "heartBeat";
            // msgId是消息id 全局唯一 保证不重复UUID 32位
            j["msgId"] = UUIDUtil::generateUUID();
            // 当前时间戳到毫秒 int 13位
            j["time"] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            std::cout << "send heartbeat: "<< j.dump().c_str() << std::endl;

            sendMessage(j.dump().c_str());
        }

        // 等待config->getServerHeartbeatInterval()秒后再次执行
        std::this_thread::sleep_for(std::chrono::seconds(config->getServerHeartbeatInterval()));
        heartbeat();
    }
    return 0;
};