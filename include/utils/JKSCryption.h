#ifndef JKS_CRYPTION_H
#define JKS_CRYPTION_H

#include <iostream>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pkcs12.h>

struct JKSCryptionOptions
{
    const char *certificate_data;
    const char *private_key_data;
    const char *pem_password;
};

class JKSCryption
{
private:
    X509* cert;
    EVP_PKEY* pkey;
    SSL_CTX* ctx;

public:
    JKSCryption(JKSCryptionOptions *options);
    ~JKSCryption();

    X509* getCert();
    EVP_PKEY* getPkey();
    SSL_CTX* getCtx();
};

#endif /* JKS_CRYPTION_H */