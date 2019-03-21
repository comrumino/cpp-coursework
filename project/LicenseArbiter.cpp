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

RSA* createPublicRSA(std::string key) {
  RSA *rsa = NULL;
  BIO *keybio;
  const char* c_string = key.c_str();
  keybio = BIO_new_mem_buf((void*)c_string, -1);
  if (keybio == NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
  return rsa;
}

void RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen,
                        const char* Msg, size_t MsgLen, bool& authentic) {
  EVP_PKEY* pubKey = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(pubKey, rsa);
  EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

  if (EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha512(), NULL, pubKey) <= 0) {
    ;
  } else if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
    ;
  } else if (EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen) == 1) {
    authentic = true;
    ;
  }
    EVP_MD_CTX_free(m_RSAVerifyCtx);
}

void Base64Decode(const char* b64msg, unsigned char** buffer, size_t* length) {
    BIO *bio;
    BIO *b64;
    size_t len = strlen(b64msg);
    size_t padding = 0;

    if (b64msg[len-1] == '=' && b64msg[len-2] == '=') {
        // last two chars are =
        padding = 2;
    } else if (b64msg[len-1] == '=') {
        // last char is =
        padding = 1;
    }
    int decodeLen = (len * 3) / 4 - padding;
    *buffer = (unsigned char*) malloc(decodeLen + 1);
    (*buffer)[decodeLen] = '\0';

    bio = BIO_new_mem_buf(b64msg, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    *length = BIO_read(bio, *buffer, strlen(b64msg));
    BIO_free_all(bio);
}

bool verifySignature(std::string publicKey, std::string plainText, const char* signatureBase64) {
  RSA* publicRSA = createPublicRSA(publicKey);
  unsigned char* encMessage;
  size_t encMessageLength;
  bool authentic = false;
  Base64Decode(signatureBase64, &encMessage, &encMessageLength);
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
    bool authentic = verifySignature(publicKey, license, signature.c_str());
    if ( authentic ) {
        std::cout << "Authentic" << std::endl;
    } else {
        std::cout << "Not Authentic" << std::endl;
    }
}
