#include "utils/PEMCryption.h"

int password_cb(char *buf, int size, int rwflag, void *user_data)
{
    PEMCryptionOptions *options = (PEMCryptionOptions *)user_data;

    if (options->pem_password != NULL)
    {
        int len = std::strlen(options->pem_password);
        if (len > size)
            len = size;
        std::memcpy(buf, options->pem_password, len);
        return len;
    }
    return 0;
};

PEMCryption::PEMCryption(PEMCryptionOptions *options)
{
    Logger::getInstance()->info("Start to create PEMCryption");

    event_target = new EventTarget();

    std::thread([this, options]() {
        // Initialize the OpenSSL library
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();

        ctx = SSL_CTX_new(TLS_method());
        if (ctx == NULL)
        {
            Logger::getInstance()->error("Failed to create SSL context.");
            event_target->dispatchEvent("error", new EventCallbackParam{ "SSLContextCreationFailure", "Failed to create SSL context." });
            return;
        }

        SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1 | SSL_OP_NO_TLSv1_2);

        // Load the certificate and private key from the disk
        BIO *certificate_bio = BIO_new_mem_buf(options->certificate_data, -1);
        if (certificate_bio == NULL)
        {
            Logger::getInstance()->error("Failed to create certificate BIO.");
            event_target->dispatchEvent("error", new EventCallbackParam{ "CertificateCreationFailure", "Failed to create certificate BIO." });
            return;
        }
        cert = PEM_read_bio_X509(certificate_bio, NULL, password_cb, options);
        BIO_free(certificate_bio);

        BIO *private_key_bio = BIO_new_mem_buf(options->private_key_data, -1);
        if (private_key_bio == NULL)
        {
            Logger::getInstance()->error("Failed to create private key BIO.");
            event_target->dispatchEvent("error", new EventCallbackParam{ "PrivateKeyCreationFailure", "Failed to create private key BIO." });
            return;
        }
        pkey = PEM_read_bio_PrivateKey(private_key_bio, NULL, password_cb, options);
        BIO_free(private_key_bio);

        if (cert == NULL || pkey == NULL)
        {
            Logger::getInstance()->error("Failed to read certificate or private key.");
            event_target->dispatchEvent("error", new EventCallbackParam{ "CertificateOrPrivateKeyReadFailure", "Failed to read certificate or private key." });
            return;
        }

        SSL_CTX_use_certificate(ctx, cert);
        SSL_CTX_use_PrivateKey(ctx, pkey);

        // Check if the client certificate and private-key matches
        if (!SSL_CTX_check_private_key(ctx))
        {
            Logger::getInstance()->error("Private key does not match the certificate public key");
            event_target->dispatchEvent("error", new EventCallbackParam{ "PrivateKeyDoesNotMatchCertificatePublicKey", "Private key does not match the certificate public key" });
            return;
        }

        event_target->dispatchEvent("created", new EventCallbackParam{ "PEMCryptionCreationSuccess", "Success to create PEMCryption" });
    }).detach();
};

PEMCryption::~PEMCryption()
{
    // Clean up the OpenSSL library
    delete event_target;
    EVP_cleanup();
    ERR_free_strings();
    SSL_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    X509_free(cert);
};

X509 *PEMCryption::getCert()
{
    return cert;
};

EVP_PKEY *PEMCryption::getPkey()
{
    return pkey;
};

SSL_CTX *PEMCryption::getCtx()
{
    return ctx;
};