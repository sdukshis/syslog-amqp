#include "Logging.h"

#include <iostream>

#include "Datetime.h"


Logger::Logger(const std::string &name)
        : name_{name} { }

void Logger::log(const std::string &/*file*/, const std::string &/*func*/, size_t /*line*/, Loglevel level,
                 const std::string &msg) {
    std::clog << Datetime{}.toString() << " " << name_ << "[" << level << "]: " << msg << std::endl;
};

Logger &Logger::getLogger(const std::string &name) {
    static std::map<std::string, Logger> loggers_;
    auto pair = loggers_.emplace(name, Logger(name));
    return pair.first->second;
}

std::ostream &operator<<(std::ostream &stream, Logger::Loglevel level) {
    switch (level) {
        case Logger::Loglevel::Trace:
            stream << "TRACE";
            break;
        case Logger::Loglevel::Debug:
            stream << "DEBUG";
            break;
        case Logger::Loglevel::Info:
            stream << "INFO";
            break;
        case Logger::Loglevel::Warning:
            stream << "WARN";
            break;
        case Logger::Loglevel::Error:
            stream << "ERROR";
            break;
        case Logger::Loglevel::Fatal:
            stream << "FATAL";
            break;
    }
    return stream;
}
