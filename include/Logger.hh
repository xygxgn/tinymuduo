#pragma once

#include <string>

#include "noncopyable.hh"

enum LogLevel
{
    INFO,
    WARN,
    ERROR,
    FATAL,
    DEBUG
};

class Logger : noncopyable
{
public:
    static Logger& instance();
    void setLogLevel(int level);
    void log(std::string& msg);
private:
    Logger() = default;
    int logLevel_;
};

