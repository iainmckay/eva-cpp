#ifndef EVA_LOGGER_H
#define EVA_LOGGER_H

#include "eva.h"
#include "LoggerInterface.h"

class Logger : public LoggerInterface
{

    public:
        void initialize();
        void writeln(const int channel, const std::string component, const char *fmt, ...) const;
};

#endif /* EVA_LOGGER_H */
