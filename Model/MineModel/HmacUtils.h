#pragma once

#include <string>

std::string hmacSha256( const std::string& data, const std::string& key);