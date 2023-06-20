#include "utils/TLSConnect.h"

TLSConnect::TLSConnect(TLSConnectOptions *options): options(options)
{
    event_target = new EventTarget();
    ssl = NULL;
    ssl_error_message = NULL;
    tcp_connect = NULL;
    pem_cryption = NULL;
    status = 0;

    std::thread([this]()
    {
        initTCPConnect();
        initPEMCryption();

        ssl = SSL_new(pem_cryption->getCtx());
        // 将已有的网络 socket 转换成 SSL 对象
        // 需要通过 SSL 库提供的函数进行握手和加解密操作
        SSL_set_fd(ssl, tcp_connect->getSockfd());

        initSSLConnect();
    }).detach();
}

TLSConnect::~TLSConnect()
{
    delete event_target;
    status = 0;
    if (ssl != NULL)
    {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }
    if (tcp_connect != NULL) delete tcp_connect;
    if (pem_cryption != NULL) delete pem_cryption;
}

void TLSConnect::initTCPConnect()
{
    std::promise<void> promise;
    std::future<void> future = promise.get_future();

    tcp_connect = new TCPConnect(options->tcp_options);
    tcp_connect->event_target->addEventListener("error", [this, &promise](void* data) -> void
    {
        std::cout << "Create TCP connect has ERROR!" << std::endl;
        EventCallbackParam* param = (EventCallbackParam*)data;
        promise.set_exception(std::make_exception_ptr(std::runtime_error(param->message)));
    });

    tcp_connect->event_target->addEventListener("connected", [this, &promise](void* data) -> void
    {
        std::cout << "Success to create TCP connect" << std::endl;
        promise.set_value();
    });

    future.get();

    std::cout << "initTCPConnect success" << std::endl;
}

void TLSConnect::initPEMCryption()
{
    std::promise<void> promise;
    std::future<void> future = promise.get_future();

    pem_cryption = new PEMCryption(options->pem_options);

    pem_cryption->event_target->addEventListener("error", [this, &promise](void* data) -> void
    {
        EventCallbackParam* param = (EventCallbackParam*)data;
        promise.set_exception(std::make_exception_ptr(std::runtime_error(param->message)));
    });

    pem_cryption->event_target->addEventListener("created", [this, &promise](void* data) -> void
    {
        std::cout << "Success to create PEMCryption" << std::endl;
        promise.set_value();
    });

    future.get();
    std::cout << "initPEMCryption success" << std::endl;
}

void TLSConnect::initSSLConnect()
{
    if (SSL_connect(ssl) <= 0) {
        std::cout << "SSL connect error" << std::endl;
        handleSSLError();
        return;
    }
    std::cout << "initSSLConnect success" << std::endl;
    event_target->dispatchEvent("connected", NULL);
    status = 1;

    std::thread receive_thread(&TLSConnect::receive, this);
    receive_thread.detach();
}

void TLSConnect::waitSocketReadable()
{
    std::cout << "wait socket readable" << std::endl;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(tcp_connect->getSockfd(), &rfds);

    struct timeval timeout;
    timeout.tv_sec = 5;  // 超时时间为 5 秒
    timeout.tv_usec = 0;

    int ret = select(tcp_connect->getSockfd() + 1, &rfds, NULL, NULL, &timeout);
    if (ret == -1) {
        handleSSLError();
    } else if (ret == 0) {
        handleSSLError();
    } else {
        initSSLConnect();
    }
}

void TLSConnect::waitSocketWritable()
{
    std::cout << "wait socket writable" << std::endl;
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(tcp_connect->getSockfd(), &wfds);

    struct timeval timeout;
    timeout.tv_sec = 5;  // 超时时间为 5 秒
    timeout.tv_usec = 0;

    int ret = select(tcp_connect->getSockfd() + 1, NULL, &wfds, NULL, &timeout);
    if (ret == -1) {
        handleSSLError();
    } else if (ret == 0) {
        handleSSLError();
    } else {
        initSSLConnect();
    }
}

void TLSConnect::handleSSLError()
{
    std::cout << "handleSSLError" << std::endl;
    status = 0;
    event_target->dispatchEvent("disconnect", NULL);
    const char* err_buf = "";
    switch (SSL_get_error(ssl, 0))
    {
        case SSL_ERROR_NONE:
            err_buf = "SSL_ERROR_NONE";
            break;
        case SSL_ERROR_ZERO_RETURN:
            err_buf = "SSL_ERROR_ZERO_RETURN";
            break;
        case SSL_ERROR_WANT_READ:
            return waitSocketReadable();
            break;
        case SSL_ERROR_WANT_WRITE:
            return waitSocketWritable();
            break;
        case SSL_ERROR_WANT_CONNECT:
            err_buf = "SSL_ERROR_WANT_CONNECT";
            break;
        case SSL_ERROR_WANT_ACCEPT:
            err_buf = "SSL_ERROR_WANT_ACCEPT";
            break;
        case SSL_ERROR_WANT_X509_LOOKUP:
            err_buf = "SSL_ERROR_WANT_X509_LOOKUP";
            break;
        case SSL_ERROR_SYSCALL:
            err_buf = "SSL_ERROR_SYSCALL";
            break;
        case SSL_ERROR_SSL:
            err_buf = "SSL_ERROR_SSL";
            break;
        default:
            err_buf = "Unknown error";
            break;
    }
    std::string err_str = "SSL connect has error: " + std::string(err_buf) + std::string(strerror(errno));
    const char* err_msg = err_str.c_str();
    ssl_error_message = err_msg;
    std::cout << err_msg << std::endl;
    ERR_print_errors_fp(stdout);
    event_target->dispatchEvent("error", new EventCallbackParam { "TLSConnectFailure", err_msg });
    return;
}

SSL* TLSConnect::getSSL()
{
    return ssl;
}

void TLSConnect::receive()
{
    std::cout << "start receive" << std::endl;
    while (status == 1)
    {
        char buffer[65535];
        memset(buffer, 0, sizeof(buffer));

        if (ssl == NULL)
        {
            std::cerr << "ssl is null" << std::endl;
            event_target->dispatchEvent("error", new EventCallbackParam { "TLSConnectFailure", "ssl is null" });
            return;
        }

        int pending_ret = SSL_pending(ssl);
        if (pending_ret > 0)
        {
            int bytes_read = SSL_read(ssl, buffer, sizeof(buffer));
            if (bytes_read > 0)
            {
                event_target->dispatchEvent("message", new EventCallbackParam { "message", buffer });
            }
            else
            {
                handleSSLError();
                return;
            }
        }
        else if (pending_ret == 0)
        {
            // std::cout << "SSL_pending return 0" << std::endl;
        }
        else {
            std::cout << "SSL_pending return -1" << std::endl;
            handleSSLError();
            return;
        }
        // 放弃 CPU 时间片，允许其他线程或进程运行
        std::this_thread::yield();
        // 等待一段时间，避免占用 CPU 过多
        std::this_thread::sleep_for(std::chrono::seconds(options->server_receive_interval));
    }
    return;
};

int TLSConnect::send(const char* message)
{
    if (ssl == NULL)
    {
        std::cerr << "ssl is null" << std::endl;
        event_target->dispatchEvent("error", new EventCallbackParam { "TLSConnectFailure", "ssl is null" });
        return -1;
    }

    if (status != 1) {
        std::cerr << "Tls not connected" << std::endl;
        return -1;
    }

    int bytes_sent = SSL_write(ssl, message, strlen(message));
    if (bytes_sent <= 0)
    {
        std::cout << "SSL_write error" << std::endl;
        handleSSLError();
        return -1;
    }
    return bytes_sent;
};