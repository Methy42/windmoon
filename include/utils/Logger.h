#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

class Logger
{
public:
    enum LogLevel
    {
        LOG_LEVEL_DEBUG = 0,
        LOG_LEVEL_INFO,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_FATAL
    };

    static Logger* getInstance();

    void setLogLevel(LogLevel level);
    void setLogPath(const std::string& path);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void fatal(const std::string& message);

private:
    Logger(/* args */);
    ~Logger();

    void log(LogLevel level, const std::string& message);

    static Logger* m_instance;

    LogLevel m_level;
    std::string m_path;
    std::ofstream m_file;
};

#endif  // UTILS_LOGGER_H