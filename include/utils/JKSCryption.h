#ifndef JKS_CRYPTION_H
#define JKS_CRYPTION_H

#include <iostream>
#include <cstring>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pkcs12.h>
#include "config/ClientConfig.h"

class JKSCryption
{
private:
    // Privatizing constructors and destructors ensures that instances can only be obtained through the getInstance method
    JKSCryption()
    {
        ClientConfig* config = ClientConfig::getInstance();

        // Initialize the OpenSSL library
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();

        // open JKS file
        FILE* fp = fopen(config->getClientJksFilePath().c_str(), "rb");
        if (!fp) {
            std::cerr << "Cannot open JKS file" << std::endl;
        }

        // load JKS file
        PKCS12* p12 = d2i_PKCS12_fp(fp, NULL);
        fclose(fp);
        if (!p12) {
            std::cerr << "Error loading JKS file" << std::endl;
        }

        // Extract certificate
        cert = NULL;
        pkey = NULL;
        STACK_OF(X509)* ca = NULL;
        if (!PKCS12_parse(p12, config->getClientJksPassword().c_str(), &pkey, &cert, &ca)) {
            std::cerr << "Error parsing JKS file" << std::endl;
        }

        ctx = EVP_CIPHER_CTX_new();

        // Clean up resources
        PKCS12_free(p12);
    };

    ~JKSCryption()
    {
        // Clean up the OpenSSL library
        EVP_cleanup();
        ERR_free_strings();

        EVP_PKEY_free(pkey);
        X509_free(cert);
        EVP_CIPHER_CTX_free(ctx);
    };

    X509* cert;
    EVP_PKEY* pkey;
    EVP_CIPHER_CTX *ctx;

public:
    static JKSCryption* getInstance();

    // Prohibit copying constructors and copying assignment operators
    JKSCryption(const JKSCryption&) = delete;
    JKSCryption& operator=(const JKSCryption&) = delete;

    std::string encrypt(const unsigned char *data);
    std::string decrypt(const char* data);
};

#endif /* JKS_CRYPTION_H */