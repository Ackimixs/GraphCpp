#include "../include/Utils.hpp"

bool Utils::isNumber(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool Utils::isDouble(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c) && c != '.'; }) == s.end();
}
