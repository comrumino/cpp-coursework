#pragma once
#include <cstring>
#include <iostream>
#include <vector>
#include <memory>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <assert.h>
#include <string>
#include <fstream>
#include <streambuf>

using tDSA_free = decltype(&::DSA_free);
using tBIO_free = decltype(&::BIO_free);

std::unique_ptr<DSA, tDSA_free> createPublicDSA(const char* key);

void DSAVerifySignature(DSA* dsa, unsigned char* MsgHash, size_t MsgHashLen,
                        const char* Msg, size_t MsgLen, bool& authentic);

void Base64Decode(std::string b64sig, unsigned char*& buffer, size_t* length);

bool verifySignature(std::string publicKey, std::string plainText, std::string b64sig);
