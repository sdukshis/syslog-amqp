#include <fstream>

#include "Options.h"
#include "Logging.h"

#include "AsioReactor.h"
#include "ReactorBuilder.h"

static auto &logger = Logger::getLogger("SyslogAmqp");

int main(int , char const *[])
try {
    LOG_INFO(logger, "Starting up")
    logger.loglevel(Logger::Loglevel::Debug);

    std::ifstream config("syslog-amqp.conf");
    if (!config.is_open()) {
        throw std::invalid_argument("couldn't open config file");
    }
    Options options;
    config >> options;
    LOG_INFO(logger, "Options: " << options);

    AsioReactor reactor;
    ReactorBuilder builder;
    builder.buildFromOptions(reactor, options);

    LOG_INFO(logger, "Reactor run")
    reactor.run();

    LOG_INFO(logger, "Finishing");
    return EXIT_SUCCESS;
} catch (const std::exception &e) {
    LOG_FATAL(logger, e.what());
    return EXIT_FAILURE;
}