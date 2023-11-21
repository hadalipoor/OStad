#ifndef HMACAuth_h
#define HMACAuth_h

#include "mbedtls/md.h"
#include "mbedtls/base64.h"

class HMACAuth {
public:
    HMACAuth();
    HMACAuth(const char *key);
    void updateHash(const char *data);
    String finalizeHash();

private:
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    void initHash(const char *key);
};


HMACAuth::HMACAuth() {
}

HMACAuth::HMACAuth(const char *key) {
    initHash(key);
}

void HMACAuth::initHash(const char *key) {
    const size_t keyLength = strlen(key);
    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
    mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
}

void HMACAuth::updateHash(const char *data) {
    const size_t dataLength = strlen(data);
    mbedtls_md_hmac_update(&ctx, (const unsigned char *) data, dataLength);
}

String HMACAuth::finalizeHash() {
    byte output_HMAC[32];
    unsigned char output[65];
    size_t outlen;

    mbedtls_md_hmac_finish(&ctx, output_HMAC);
    mbedtls_md_free(&ctx);
    
    mbedtls_base64_encode(output, 64, &outlen, (unsigned char *)output_HMAC, sizeof(output_HMAC));
    output[outlen] = 0;
    
    return String((const char*)output);
}
#endif
