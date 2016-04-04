#ifndef EVA_LOGGERINTERFACE_H
#define EVA_LOGGERINTERFACE_H

#include "eva.h"

#define LOG_INFO 0
#define LOG_DEBUG 1
#define LOG_WARNING 2
#define LOG_ERROR 3

class LoggerInterface
{

public:
    virtual ~LoggerInterface()
    {

    }

    virtual void initialize() = 0;

    virtual void writeln(const int channel, const std::string component, const char* fmt, ...) const = 0;

    static std::string channelToString(const int channel)
    {
        switch(channel)
        {
        case LOG_INFO:
            return std::string("info");
        case LOG_DEBUG:
            return std::string("debug");
        case LOG_WARNING:
            return std::string("warn");
        case LOG_ERROR:
            return std::string("error");
        }

        return std::string("unknown");
    }
};

#endif /* EVA_LOGGERINTERFACE_H */
