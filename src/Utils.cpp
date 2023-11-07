#include "../include/Utils.hpp"

bool Utils::isNumber(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool Utils::isDouble(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c) && c != '.'; }) == s.end();
}

std::string Utils::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* current_time = std::localtime(&time);

    char buffer[20]; // Buffer to store the formatted date and time

    // Format the date and time as "yyyy-MM-dd HH:mm:ss"
    std::strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", current_time);

    return buffer;
}