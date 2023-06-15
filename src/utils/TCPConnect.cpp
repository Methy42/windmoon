#include "utils/TCPConnect.h"

TCPConnect::TCPConnect(TCPConnectOptions *options)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        status = -1;
    } else {
        status = 0;
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    // 设置服务器地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(options->server_port);  // 设置端口号为1234
    inet_pton(AF_INET, options->server_ip, &server_addr.sin_addr);

    std::cout << "start tcp connect" << std::endl;
    std::cout << "server_ip: " << options->server_ip << std::endl;
    std::cout << "server_port: " << options->server_port << std::endl;


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
            std::cerr << "Failed to connect to server." << std::endl;
            status = -1;
        } else {
            int error = -1;
            socklen_t len = sizeof(error);
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
            if (error != 0) {
                std::cerr << "Failed to connect to server." << std::endl;
                status = -1;
            } else {
                std::cout << "Connected to server." << std::endl;
                status = 1;
            }
        }
    });
    connect_thread.detach();
}

TCPConnect::~TCPConnect()
{
    close(sockfd);
}

int TCPConnect::getSockfd()
{
    return sockfd;
}

int TCPConnect::getStatus()
{
    return status;
}