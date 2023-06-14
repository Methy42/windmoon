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

    // 设置服务器地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(options->server_port);  // 设置端口号为1234
    inet_pton(AF_INET, options->server_ip, &server_addr.sin_addr);

    std::cout << "start tcp connect" << std::endl;
    std::cout << "server_ip: " << options->server_ip << std::endl;
    std::cout << "server_port: " << options->server_port << std::endl;

    // 连接服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "Failed to connect to server." << std::endl;
        close(sockfd);
        status = -1;
    }

    status = 1;
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