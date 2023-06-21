#include "utils/Logger.h"

Logger* Logger::m_instance = nullptr;

Logger::Logger(/* args */)
{
    m_level = LOG_LEVEL_DEBUG;
    m_path = "log.txt";
    m_file.open(m_path, std::ios::out | std::ios::app);
}

Logger::~Logger()
{
    m_file.close();
}

Logger* Logger::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Logger();
    }

    return m_instance;
}

void Logger::setLogLevel(LogLevel level)
{
    m_level = level;
}

void Logger::setLogPath(const std::string& path)
{
    m_path = path;
}

void Logger::debug(const std::string& message)
{
    log(LOG_LEVEL_DEBUG, message);
}

void Logger::info(const std::string& message)
{
    log(LOG_LEVEL_INFO, message);
}

void Logger::warning(const std::string& message)
{
    log(LOG_LEVEL_WARNING, message);
}

void Logger::error(const std::string& message)
{
    log(LOG_LEVEL_ERROR, message);
}

void Logger::fatal(const std::string& message)
{
    log(LOG_LEVEL_FATAL, message);
}

void Logger::log(LogLevel level, const std::string& message)
{
    if (level < m_level)
    {
        return;
    }

    std::string levelStr;
    switch (level)
    {
    case LOG_LEVEL_DEBUG:
        levelStr = "DEBUG";
        break;
    case LOG_LEVEL_INFO:
        levelStr = "INFO";
        break;
    case LOG_LEVEL_WARNING:
        levelStr = "WARNING";
        break;
    case LOG_LEVEL_ERROR:
        levelStr = "ERROR";
        break;
    case LOG_LEVEL_FATAL:
        levelStr = "FATAL";
        break;
    default:
        break;
    }

    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timeStr(dt);
    timeStr = timeStr.substr(0, timeStr.length() - 1);

    std::stringstream ss;
    ss << "[" << timeStr << "] " << "[" << levelStr << "] " << message << std::endl;
    std::string logStr = ss.str();

    std::cout << logStr;
    m_file.write(logStr.c_str(), logStr.length());
}

// Path: src/utils/ServerConnect.cpp