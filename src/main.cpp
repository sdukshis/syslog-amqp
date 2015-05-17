#include "Message.h"
#include "UDPListener.h"
#include "Decoder.h"

#include "AsioReactor.h"

#include "MessageObserver.h"
#include "DataObserver.h"
#include "PublishMessageObserver.h"
#include "JsonMessageEncoder.h"
#include "StdoutPublisher.h"

#include <iostream>

class DataLogger: public DataObserver {
 public:
    void onBegin(const Endpoint &, const std::string &) override {

    }

    void onData(const char *buffer, std::size_t lenght) override {
        std::clog << "Data received: " << std::string{buffer, lenght}
                  << std::endl;
    }

    void onEnd() override {}
};

int main(int , char const *[])
try {
    AsioReactor reactor;

    JsonMessageEncoder encoder;
    std::unique_ptr<RabbitMQPublisher> rabbitmq_publisher{reactor.createRabbitMQPublisher()};
    PublishMessageObserver publish_observer{*rabbitmq_publisher, "events", RabbitMQPublisher::ExchangeType::Topic,
                                            "raw", encoder};

    std::unique_ptr<UDPListener> udp_listener{reactor.createUDPListener(Endpoint{"0.0.0.0", 1313})};
    StdoutPublisher stdout_publisher{encoder};
    DataLogger data_logger;

    Decoder decoder;

    decoder.addObserver(&stdout_publisher);
    decoder.addObserver(&publish_observer);

    udp_listener->addObserver(&data_logger);
    udp_listener->addObserver(&decoder);

    reactor.run();

    /* code */
    return EXIT_SUCCESS;
} catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}