#include "HmacUtils.h"

#include <openssl/hmac.h>
#include <openssl/evp.h>

#include <iomanip>
#include <sstream>

std::string hmacSha256(
    const std::string& data,
    const std::string& key)
{
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen = 0;

    HMAC(
        EVP_sha256(),
        key.data(),
        static_cast<int>(key.size()),
        reinterpret_cast<const unsigned char*>(data.data()),
        data.size(),
        hash,
        &hashLen);

    std::stringstream ss;

    for (unsigned int i = 0; i < hashLen; ++i)
    {
        ss << std::hex
           << std::setw(2)
           << std::setfill('0')
           << static_cast<int>(hash[i]);
    }

    return ss.str();
}