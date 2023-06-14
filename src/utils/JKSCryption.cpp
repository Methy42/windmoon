#include "utils/JKSCryption.h"

int password_cb(char *buf, int size, int rwflag, void *user_data)
{
    JKSCryptionOptions *options = (JKSCryptionOptions *)user_data;

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

JKSCryption::JKSCryption(JKSCryptionOptions *options)
{
    std::cout << "JKSCryption::JKSCryption" << std::endl;

    // Initialize the OpenSSL library
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    ctx = SSL_CTX_new(TLS_method());
    if (ctx == NULL)
    {
        std::cerr << "Failed to create SSL context." << std::endl;
    }

    // Load the certificate and private key from the disk
    BIO *certificate_bio = BIO_new_mem_buf(options->certificate_data, -1);
    if (certificate_bio == NULL)
    {
        std::cerr << "Failed to create BIO." << std::endl;
    }
    cert = PEM_read_bio_X509(certificate_bio, NULL, password_cb, options);
    BIO_free(certificate_bio);

    BIO *private_key_bio = BIO_new_mem_buf(options->private_key_data, -1);
    if (private_key_bio == NULL)
    {
        std::cerr << "Failed to create BIO." << std::endl;
    }
    pkey = PEM_read_bio_PrivateKey(private_key_bio, NULL, password_cb, options);
    BIO_free(private_key_bio);

    if (cert == NULL || pkey == NULL)
    {
        std::cerr << "Failed to read certificate or private key." << std::endl;
    }

    SSL_CTX_use_certificate(ctx, cert);
    SSL_CTX_use_PrivateKey(ctx, pkey);

    // Check if the client certificate and private-key matches
    if (!SSL_CTX_check_private_key(ctx))
    {
        std::cerr << "Private key does not match the certificate public key" << std::endl;
    }

    std::cout << "JKSCryption::JKSCryption end" << std::endl;
};

JKSCryption::~JKSCryption()
{
    // Clean up the OpenSSL library
    EVP_cleanup();
    ERR_free_strings();
    SSL_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    X509_free(cert);
};

X509 *JKSCryption::getCert()
{
    return cert;
};

EVP_PKEY *JKSCryption::getPkey()
{
    return pkey;
};

SSL_CTX *JKSCryption::getCtx()
{
    return ctx;
};