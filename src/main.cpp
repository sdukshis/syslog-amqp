#include <fstream>

#include "CmdOptions.h"
#include "Options.h"
#include "Logging.h"

#include "AsioReactor.h"
#include "ReactorBuilder.h"

static auto &logger = Logger::getLogger("SyslogAmqp");

int main(int argc, char *argv[])
try {
    CmdOptions cmd_options = parse_args(argc, argv);

    if (cmd_options.show_version) {
        std::cout << "0.0.1" << std::endl;
        return EXIT_FAILURE;
    }

    if (cmd_options.show_help) {
        std::cout << R"(
Usage: syslog-amqp [OPTS]

Options:
    -h            show this help and exit
    -v            show version and exit
    -c <filename> path to config file
)";
        return EXIT_FAILURE;
    }
    logger.loglevel(Logger::Loglevel::Debug);

    Options options;

    if (!cmd_options.config.empty()) {
        std::ifstream config(cmd_options.config);
        if (!config.is_open()) {
            throw std::invalid_argument("couldn't open config file");
        }
        config >> options;
    }
    LOG_INFO(logger, "Options: " << options);

    LOG_INFO(logger, "Starting up")
    AsioReactor reactor;
    ReactorBuilder().buildFromOptions(reactor, options);

    LOG_INFO(logger, "Reactor run")
    reactor.run();

    LOG_INFO(logger, "Finishing");
    return EXIT_SUCCESS;
} catch (const std::exception &e) {
    LOG_FATAL(logger, e.what());
    return EXIT_FAILURE;
}