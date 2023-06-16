#include "utils/TLSConnect.h"

TLSConnect::TLSConnect(TLSConnectOptions *options): options(options)
{
    event_target = new EventTarget();
    status = 0;

    std::thread([this]()
    {
        try
        {
            initTCPConnect();
            initPEMCryption();
            status = 1;
            event_target->dispatchEvent("connected", NULL);

            std::thread receive_thread(&TLSConnect::receive, this);
            receive_thread.detach();
        }
        catch(const std::exception& e)
        {
            status = 0;
            char *error_message = const_cast<char *>(e.what());
            std::cerr << error_message << '\n';
            event_target->dispatchEvent("error", new EventCallbackParam { "TLSConnectFailure", error_message });
        }
    }).detach();
}

TLSConnect::~TLSConnect()
{
    delete event_target;
    status = 0;
    SSL_shutdown(ssl);
    SSL_free(ssl);
    delete tcp_connect;
    delete pem_cryption;
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
        ssl = SSL_new(pem_cryption->getCtx());
        SSL_set_fd(ssl, tcp_connect->getSockfd());
        if (SSL_connect(ssl) <= 0) {
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
                    err_buf = "SSL_ERROR_WANT_READ";
                    break;
                case SSL_ERROR_WANT_WRITE:
                    err_buf = "SSL_ERROR_WANT_WRITE";
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
            std::string err_str = "SSL_connect error: " + std::string(err_buf);
            const char* err_msg = err_str.c_str();
            promise.set_exception(std::make_exception_ptr(std::runtime_error(err_msg)));
            return;
        }
        promise.set_value();
    });

    future.get();
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
            return;
        }

        int bytes_read = SSL_read(ssl, buffer, sizeof(buffer));
        if (bytes_read > 0)
        {
            event_target->dispatchEvent("message", new EventCallbackParam { "message", buffer });
        }
        else
        {
            status = 0;
            event_target->dispatchEvent("error", new EventCallbackParam { "TLSConnectFailure", "Failed to receive data." });
            std::cerr << "Failed to receive data." << std::endl;
            return;
        }
    }
    return;
};

int TLSConnect::send(const char* message)
{
    if (ssl == NULL)
    {
        std::cerr << "ssl is null" << std::endl;
        return -1;
    }

    if (status != 1) {
        std::cerr << "Tls not connected" << std::endl;
        return -1;
    }

    int bytes_sent = SSL_write(ssl, message, strlen(message));
    if (bytes_sent <= 0)
    {
        int err = SSL_get_error(ssl, bytes_sent);

        if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE)
        {
            std::cerr << "SSL_write error" << std::endl;
            return 0;
        }
        std::cerr << "TLS connection interrupted" << std::endl;
        status = 0;
        event_target->dispatchEvent("error", new EventCallbackParam { "TLSConnectFailure", "TLS connection interrupted" });
        return -1;
    }
    return bytes_sent;
};