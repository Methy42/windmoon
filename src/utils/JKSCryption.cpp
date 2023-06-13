#include "utils/JKSCryption.h"

JKSCryption* JKSCryption::getInstance()
{
    static JKSCryption instance;
    return &instance;
}

std::string JKSCryption::encrypt(const unsigned char *data)
{
    int data_len = strlen((const char*)data);
    int max_result_len = EVP_CIPHER_CTX_block_size(ctx) + data_len;
    std::string result(max_result_len, '\0');
    int result_len = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, NULL, NULL);
    EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&result[0]), &result_len, data, data_len);
    EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&result[result_len]), &result_len);

    result.resize(result_len);

    return result;
}

std::string JKSCryption::decrypt(const char* data)
{
    int data_len = strlen(data);
    int max_result_len = data_len;
    std::string result(max_result_len, '\0');
    int result_len = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, NULL, NULL);
    EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&result[0]), &result_len, reinterpret_cast<const unsigned char*>(data), data_len);
    EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&result[result_len]), &result_len);

    result.resize(result_len);

    return result;
}
