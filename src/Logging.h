//
// Created by Pavel Filonov on 18.05.15.
//

#ifndef SYSLOG_AMQP_LOGGING_H
#define SYSLOG_AMQP_LOGGING_H

#include <map>
#include <string>
#include <sstream>

class Logger {
public:
    enum class Loglevel {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    Logger(const Logger &) = delete;

    Logger(Logger &&) = default;

    Logger & operator=(const Logger &) = delete;

    Logger & operator=(Logger &&) = default;

    Loglevel loglevel() const { return loglevel_; }

    void loglevel(Loglevel ll) { loglevel_ = ll; }

    bool enabled(Loglevel ll) { return ll >= loglevel_; }

    void log(const std::string &file, const std::string &func, size_t line, const std::string &msg);

    static Logger & getLogger(const std::string &name);

private:
    Loglevel loglevel_ = Loglevel::Info;
    std::string name_;
    Logger(const std::string &name);
};

#define LOG(logger, level, msg)                             \
    if (logger.enabled(level)){                             \
        std::stringstream ss;                               \
        ss << msg;                                          \
        logger.log(__FILE__, __PRETTY_FUNCTION__, __LINE__, ss.str()); \
    }

#define LOG_TRACE(logger, msg) LOG(logger, Logger::Loglevel::Trace, msg)
#define LOG_DEBUG(logger, msg) LOG(logger, Logger::Loglevel::Debug, msg)
#define LOG_INFO(logger, msg) LOG(logger, Logger::Loglevel::Info, msg)
#define LOG_WARN(logger, msg) LOG(logger, Logger::Loglevel::Warning, msg)
#define LOG_ERROR(logger, msg) LOG(logger, Logger::Loglevel::Error, msg)
#define LOG_FATAL(logger, msg) LOG(logger, Logger::Loglevel::Fatal, msg)

#endif //SYSLOG_AMQP_LOGGING_H
