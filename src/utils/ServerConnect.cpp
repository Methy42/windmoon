#include "utils/ServerConnect.h"
#include "utils/UUIDUtil.h"

ServerConnect* ServerConnect::getInstance()
{
    static ServerConnect instance;
    return &instance;
};

int ServerConnect::run()
{
    ClientConfig* config = ClientConfig::getInstance();

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // 设置服务器地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config->getServerPort());  // 设置端口号为1234
    inet_pton(AF_INET, config->getServerIp().c_str(), &server_addr.sin_addr);

    std::cout << "start net connect" << std::endl;
    std::cout << "server_ip: " << config->getServerIp() << std::endl;
    std::cout << "server_port: " << config->getServerPort() << std::endl;

    // 连接服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "Failed to connect to server." << std::endl;
        close(sockfd);
        return -1;
    }

    status = 1;

    // 接收数据
    std::thread new_thread(&ServerConnect::receive, this);
    receive_thread = std::move(new_thread);

    // 开始心跳
    std::cout << "start heartbeat!!!" << std::endl;
    heartbeat();

    return 0;
};

int ServerConnect::sendMessage(const char* message)
{
    if (status == 0)
    {
        std::cerr << "Failed to send message, server is not connected." << std::endl;
        return -1;
    }
    JKSCryption* jksCryption = JKSCryption::getInstance();
    std::string encrypt_message = jksCryption->encrypt(reinterpret_cast<const unsigned char*>(message));
    send(sockfd, encrypt_message.c_str(), strlen(encrypt_message.c_str()), 0);
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
    close(sockfd);
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
            std::cout << "send heartbeat" << std::endl;

             nlohmann::json j;
            j["type"] = "heartbeat";
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