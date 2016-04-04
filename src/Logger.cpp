#include "eva.h"
#include "Logger.h"

void Logger::initialize()
{
    writeln(LOG_DEBUG, "logger", "logger initialized (buffer=64bytes)");
}

void Logger::writeln(const int channel, const std::string component, const char* fmt, ...) const
{
    static char buffer[64];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, 63, fmt, args);

    Serial.print("[");
    Serial.print(LoggerInterface::channelToString(channel).c_str());
    Serial.print("]");

    Serial.print("[");
    Serial.print(component.c_str());
    Serial.print("]");

    Serial.print(" ");
    Serial.println(buffer);

    va_end(args);
}

