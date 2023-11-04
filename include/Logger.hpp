#pragma once

#include "LogColor.hpp"

#include <iostream>
#include <string>
#include <chrono>

std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* current_time = std::localtime(&time);

    char buffer[20]; // Buffer to store the formatted date and time

    // Format the date and time as "yyyy-MM-dd HH:mm:ss"
    std::strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", current_time);

    return buffer;
}

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
    static LogLevel logLevel;

    static void log(LogLevel level, const std::string &message) {
        if (level >= logLevel) {
            std::cout << LogColor::bgBlack << LogColor::fgWhite << getCurrentDateTime() << LogColor::reset << " ";

            switch (level) {
                case LogLevel::DEBUG:
                    std::cout << LogColor::fgBlue;
                    break;
                case LogLevel::INFO:
                    std::cout << LogColor::fgGreen;
                    break;
                case LogLevel::WARNING:
                    std::cout << LogColor::fgYellow;
                    break;
                case LogLevel::ERROR:
                    std::cout << LogColor::fgRed;
                    break;
                case LogLevel::CRITICAL:
                    std::cout << LogColor::fgRed << LogColor::bold;
                    break;
            }
            std::cout << enumToString(level) << LogColor::reset << " ";

            std::cout << message << std::endl;
        }
    }

    static std::string enumToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

public:
    static void setLogLevel(LogLevel level) {
       Logger::logLevel = level;
    }

    static void debug(const std::string &message) {
        log(LogLevel::DEBUG, message);
    }

    static void info(const std::string &message) {
        log(LogLevel::INFO, message);
    }

    static void warning(const std::string &message) {
        log(LogLevel::WARNING, message);
    }

    static void error(const std::string &message) {
        log(LogLevel::ERROR, message);
    }

    static void critical(const std::string &message) {
        log(LogLevel::CRITICAL, message);
    }
};

LogLevel Logger::logLevel = LogLevel::INFO;