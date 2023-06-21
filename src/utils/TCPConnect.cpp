#include "utils/TCPConnect.h"

TCPConnect::TCPConnect(TCPConnectOptions *options)
{
    event_target = new EventTarget();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        Logger::getInstance()->error("Failed to create socket.");
        event_target->dispatchEvent("error", new EventCallbackParam { "SocketCreationFailure", "Failed to create socket." });
    } else {
        Logger::getInstance()->info("Socket created.");
        event_target->dispatchEvent("socket_created", new EventCallbackParam { "SocketCreationSuccess", "Socket created." });
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    // 设置服务器地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(options->server_port);  // 设置端口号为1234
    inet_pton(AF_INET, options->server_ip, &server_addr.sin_addr);
    Logger::getInstance()->info(std::string("Start TCP connect to ") + options->server_ip + ":" + std::to_string(options->server_port));


    // 连接服务器
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    std::thread connect_thread([this]()
    {
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);

        // 设置超时时间, 5秒
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int ret = select(sockfd + 1, NULL, &writefds, NULL, &timeout);
        if (ret <= 0) {
            Logger::getInstance()->error("Failed to create TCP connect.");
            event_target->dispatchEvent("error", new EventCallbackParam { "SocketConnectFailure", "Failed to create TCP connect." });
        } else {
            int error = -1;
            socklen_t len = sizeof(error);
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
            if (error != 0) {
                Logger::getInstance()->error("Failed to get sockopt.");
                event_target->dispatchEvent("error", new EventCallbackParam { "SocketConnectFailure", "Failed to get sockopt." });
            } else {
                Logger::getInstance()->info("Connected to server.");
                event_target->dispatchEvent("connected", new EventCallbackParam { "SocketConnectSuccess", "Connected to server." });
            }
        }
    });
    connect_thread.detach();
}

TCPConnect::~TCPConnect()
{
    delete event_target;
    close(sockfd);
}

int TCPConnect::getSockfd()
{
    return sockfd;
}