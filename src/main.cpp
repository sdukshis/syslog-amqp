#include "Message.h"
#include "UDPListener.h"
#include "Decoder.h"

#include "MessageObserver.h"
#include "DataObserver.h"

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

class MessageLogger: public MessageObserver {
 public:
    void onMessage(const Message &m) override {
        std::cout << "Message received: " << m << std::endl;
    }
};

#include <asio.hpp>
int main(int argc, char const *argv[])
{
    asio::io_service io_service;
    UDPListener udp_listener(Endpoint("0.0.0.0", 1313), io_service);

    MessageLogger message_logger;
    DataLogger data_logger;

    Decoder decoder;

    decoder.addObserver(&message_logger);

    udp_listener.addObserver(&data_logger);
    udp_listener.addObserver(&decoder);

    udp_listener.start();

    io_service.run();
    /* code */
    return 0;
}