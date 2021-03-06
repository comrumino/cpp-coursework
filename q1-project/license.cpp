/*
 * Generate keys
 *  openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:4196 -out private.pem
 *  openssl rsa -in private.pem -outform PEM -pubout -out public.pem
 *
 * Create signature of ExampleLicense.txt and store as ExampleLicense.sig
 *  openssl dgst -sha256 -sign ./npview_signature_public_key.pem -out ./ExampleLicense.sig ./ExampleLicense.txt
 * Encode binary signature to base64
 *  openssl base64 -in  ./ExampleLicense.sig -out ./ExampleLicense.sig.base64
 * Decode base64 back to binary signature
 *  openssl base64 -d -in ./ExampleLicense.sig.base64 -out ./ExampleLicense.sig.base64.d
 * Verify signature ExampleLicense against signature
 *  openssl dgst -verify ./npview_signature_public_key.pem -signature ExampleLicense.sig.base64.d ./ExampleLicense.txt
 *
 * openssl dgst -verify npview_signature_key.pem -signature ExampleLicense.txt.sig ExampleLicense.txt
 * openssl dsa -in npview_signature_key.pem -pubout -out ./npview_signature_public_key.pem
 * openssl dgst -verify npview_signature_public_key.pem -signature ExampleLicense.txt.sig ExampleLicense.txt
 *
 *  https://www.openssl.org/docs/man1.1.0/man3/PEM_read_bio_PrivateKey.html
 *
 *  https://stackoverflow.com/questions/20058862/using-openssl-to-generate-a-dsa-key-pair/22580463
 *   g++ -g3 -O1 -Wall  -I/usr/include/openssl/ -lssl -lcrypto LicenseArbiter.cpp -o a.out
 * */
#include "license.h"
#include <assert.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/dsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <streambuf>
#include <string>
#include <vector>

std::unique_ptr<DSA, tDSA_free> createPublicDSA(const char *key) {
    std::unique_ptr<BIO, tBIO_free> keybio(BIO_new_mem_buf((void *)key, -1), BIO_free);
    std::unique_ptr<DSA, tDSA_free> dsa(PEM_read_bio_DSA_PUBKEY(keybio.get(), nullptr, nullptr, nullptr), DSA_free);
    return dsa;
}

void DSAVerifySignature(DSA *dsa, unsigned char *MsgHash, size_t MsgHashLen, const char *Msg, size_t MsgLen,
                        bool &authentic) {
    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_MD_CTX *ctx = EVP_MD_CTX_create();
    EVP_PKEY_assign_DSA(pkey, dsa);

    if (EVP_DigestVerifyInit(ctx, nullptr, EVP_sha256(), nullptr, pkey) == 1) {
        std::cout << "fucked 0" << std::endl;
        if (EVP_DigestVerifyUpdate(ctx, Msg, MsgLen) == 1) {
            std::cout << "fucked 1" << std::endl;
            if (EVP_DigestVerifyFinal(ctx, MsgHash, MsgHashLen) == 1) {
                std::cout << "fucked 2" << std::endl;
                authentic = true;
            }
        }
    }
    EVP_MD_CTX_free(ctx);
}

/*
namespace unsigned_types {
    typedef std::basic_string<unsigned char> string;
}

namespace crypto {
    using unsigned_types::string;

    class AES {
        string data;
    };
}

// Assumes no newlines or extra characters in encoded string
std::vector<unsigned char> PreferredBase64Decode(const char* encoded)
{
    std::unique_ptr<BIO,BIO_free_all> b64(BIO_new(BIO_f_base64()));
    BIO_set_flags(b64.get(), BIO_FLAGS_BASE64_NO_NL);
    BIO* source = BIO_new_mem_buf(encoded, -1); // read-only source
    BIO_push(b64.get(), source);
    const int maxlen = strlen(encoded) / 4 * 3 + 1;
    std::vector<unsigned char> decoded(maxlen);
    const int len = BIO_read(b64.get(), decoded.data(), maxlen);
    decoded.resize(len);
    return decoded;
}*/

void Base64Decode(std::string b64sig, unsigned char *&buffer, size_t *length) {
    size_t padding = 0;
    for (auto br = b64sig.rbegin(); br != b64sig.rend() && padding <= 2 && *br != '='; ++br, ++padding)
        ;
    int decodeLen = (b64sig.length() * 3) / 4 - padding;
    buffer = new unsigned char[decodeLen + 1];
    (buffer)[decodeLen] = '\0';

    std::unique_ptr<BIO, tBIO_free> bio(BIO_new_mem_buf(b64sig.c_str(), -1), BIO_free);
    std::unique_ptr<BIO, tBIO_free> b64(BIO_new(BIO_f_base64()), BIO_free);

    *length = BIO_read(BIO_push(b64.get(), bio.get()), buffer, b64sig.length());
}

bool verifySignature(std::string publicKey, std::string plainText, std::string b64sig) {
    std::unique_ptr<DSA, tDSA_free> publicDSA(createPublicDSA(publicKey.c_str()));
    unsigned char *encMessage;
    size_t encMessageLength;
    bool authentic = false;
    Base64Decode(b64sig, encMessage, &encMessageLength);
    DSAVerifySignature(publicDSA.get(), encMessage, encMessageLength, plainText.c_str(), plainText.length(), authentic);
    return authentic;
}
