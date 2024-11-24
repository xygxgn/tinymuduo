#ifndef _TINYMUDUO_LOGGER_H
#define _TINYMUDUO_LOGGER_H

#include "tinymuduo/noncopyable.hh"

#include <stdlib.h>
#include <string>

#define LOG_INFO(logMsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_WARN(logMsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(WARN); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_ERROR(logMsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_FATAL(logMsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } while(0)

#ifdef MUDUO_DEBUG
#define LOG_DEBUG(logMsgFormat, ...) \
    do \
    {\
        Logger &logger = Logger::instance();\
        logger.setLogLevel(DEBUG);\
        char buf[1024] = {0};\
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__);\
        logger.log(buf);\
    } while(0)
#else
#define LOG_DEBUG(logMsgFormat, ...)
#endif
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
    void log(std::string msg);
private:
    Logger() = default;
    int logLevel_;
};

#endif
