#pragma once

#include "LogColor.hpp"
#include "Utils.hpp"

#include <iostream>
#include <string>

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
            std::cout << LogColor::bgBlack << LogColor::fgWhite << Utils::getCurrentDateTime() << LogColor::reset << " ";

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
