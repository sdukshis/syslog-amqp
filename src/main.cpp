#include "UDPListener.h"
#include "Decoder.h"
#include "Options.h"
#include "Logging.h"

#include "AsioReactor.h"

#include "MessageObserver.h"
#include "DataObserver.h"
#include "PublishMessageObserver.h"
#include "JsonMessageEncoder.h"
#include "StdoutPublisher.h"

static auto &logger = Logger::getLogger("SyslogAmqp");

class DataLogger: public DataObserver {
 public:
    void onBegin(const Endpoint &, const std::string &) override {

    }

    void onData(const char *buffer, std::size_t lenght) override {
        LOG_DEBUG(logger, "Data received: " << std::string(buffer, lenght));
    }

    void onEnd() override {}
};

int main(int , char const *[])
try {
    logger.loglevel(Logger::Loglevel::Debug);
    Options options;
    LOG_INFO(logger, "Options: " << options);
    AsioReactor reactor;

    JsonMessageEncoder encoder;
//    RabbitMQPublisher *rabbitmq_publisher{reactor.createRabbitMQPublisher()};
//    PublishMessageObserver publish_observer{*rabbitmq_publisher, "events", RabbitMQPublisher::ExchangeType::Topic,
//                                            "raw", encoder};

    UDPListener *udp_listener{reactor.createUDPListener(Endpoint{"0.0.0.0", 1313})};
    StdoutPublisher stdout_publisher{encoder};
    DataLogger data_logger;

    Decoder decoder;

    decoder.addObserver(&stdout_publisher);
//    decoder.addObserver(&publish_observer);

    udp_listener->addObserver(&data_logger);
    udp_listener->addObserver(&decoder);

    reactor.run();

    /* code */
    return EXIT_SUCCESS;
} catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}