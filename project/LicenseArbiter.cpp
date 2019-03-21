/* Generate keys
 *  openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:4196 -out private.pem
 *  openssl rsa -in private.pem -outform PEM -pubout -out public.pem
 * Create signature of ExampleLicense.txt and store as ExampleLicense.sig
 *  openssl dgst -sha512 -sign ./private.pem -out ./ExampleLicense.sig ./ExampleLicense.txt 
 * Encode binary signature to base64
 *  openssl base64 -in  ./ExampleLicense.sig -out ./ExampleLicense.sig.base64
 * Decode base64 back to binary signature
 *  openssl base64 -d -in ./ExampleLicense.sig.base64 -out ./ExampleLicense.sig.base64.d
 * Verify signature ExampleLicense against signature
 *  openssl dgst -sha512 -verify ./public.pem -signature ExampleLicense.sig.base64.d ./ExampleLicense.txt
 * */
#include <cstring>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <assert.h>
#include <string>
#include <fstream>
#include <streambuf>

RSA* createPublicRSA(const char* key) {
    RSA *rsa = nullptr;
    BIO *keybio;
    keybio = BIO_new_mem_buf((void*)key, -1);
    if (keybio != nullptr)
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, nullptr, nullptr);
    return rsa;
}

void RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen,
                        const char* Msg, size_t MsgLen, bool& authentic) {
    EVP_PKEY* pubKey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pubKey, rsa);
    EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

    if (EVP_DigestVerifyInit(m_RSAVerifyCtx, nullptr, EVP_sha512(), nullptr, pubKey) == 1)
        if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) == 1)
            if (EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen) == 1)
                authentic = true;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
}

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
    std::unique_ptr<BIO,BIOFreeAll> b64(BIO_new(BIO_f_base64()));
    BIO_set_flags(b64.get(), BIO_FLAGS_BASE64_NO_NL);
    BIO* source = BIO_new_mem_buf(encoded, -1); // read-only source
    BIO_push(b64.get(), source);
    const int maxlen = strlen(encoded) / 4 * 3 + 1;
    std::vector<unsigned char> decoded(maxlen);
    const int len = BIO_read(b64.get(), decoded.data(), maxlen);
    decoded.resize(len);
    return decoded;
}

void Base64Decode(std::string b64sig, unsigned char*& buffer, size_t* length) {
    size_t padding = 0;
    for (auto br = b64sig.rbegin(); br != b64sig.rend() && padding <= 2 && *br != '='; ++br, ++padding)
        ;
    int decodeLen = (b64sig.length() * 3) / 4 - padding;
    buffer = new (unsigned char*)[decodeLen + 1];
    (buffer)[decodeLen] = '\0';

    BIO *bio = BIO_new_mem_buf(b64sig.c_str(), -1);
    BIO *b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    *length = BIO_read(bio, buffer, b64sig.length());
    BIO_free_all(bio);
}

bool verifySignature(std::string publicKey, std::string plainText, std::string b64sig) {
    RSA* publicRSA = createPublicRSA(publicKey.c_str());
    unsigned char* encMessage;
    size_t encMessageLength;
    bool authentic = false;
    Base64Decode(b64sig, encMessage, &encMessageLength);
    RSAVerifySignature(publicRSA, encMessage, encMessageLength, plainText.c_str(), plainText.length(), authentic);
    return authentic;
}

int main() {
    std::ifstream pubifs("public.pem");
    std::string publicKey((std::istreambuf_iterator<char>(pubifs)),
                     std::istreambuf_iterator<char>());

    std::ifstream privifs("private.pem");
    std::string privateKey((std::istreambuf_iterator<char>(privifs)),
                     std::istreambuf_iterator<char>());

    std::ifstream licifs("ExampleLicense.txt");
    std::string license((std::istreambuf_iterator<char>(licifs)),
                     std::istreambuf_iterator<char>());
    std::ifstream sigifs("ExampleLicense.sig.base64");
    std::string signature((std::istreambuf_iterator<char>(sigifs)),
                     std::istreambuf_iterator<char>());
    //char* signature = signMessage(privateKey, plainText);
    std::cout << license << std::endl;
    bool authentic = verifySignature(publicKey, license, signature);
    if ( authentic ) {
        std::cout << "Authentic" << std::endl;
    } else {
        std::cout << "Not Authentic" << std::endl;
    }
}
