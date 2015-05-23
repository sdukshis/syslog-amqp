//
// Created by Pavel Filonov on 17.05.15.
//

#include "AsioReactor.h"

#include "Logging.h"

#include "UDPListener.h"

static auto &logger = Logger::getLogger("AsioReactor");

AsioReactor::AsioReactor()
        : rmq_publisher_factory_{Endpoint{"127.0.0.1", 5672}, io_service_} {

}

AsioReactor::~AsioReactor() {
    stop();
}

RabbitMQPublisher *AsioReactor::createRabbitMQPublisher() {
    return rmq_publisher_factory_.createRabbitMQPublisher();
}

UDPListener *AsioReactor::createUDPListener(const Endpoint &endpoint) {
    udp_listeners_.emplace_back(new UDPListener{endpoint, io_service_});
    return udp_listeners_.back().get();
}

void AsioReactor::run() {
    LOG_INFO(logger, "run");
    asio::signal_set signals(io_service_, SIGINT, SIGTERM);
    signals.async_wait([this](const asio::error_code &ec, int) {
        std::clog << ec.message() << std::endl;
        assert(!ec);
        LOG_INFO(logger, "signal catched");
        stop();
    });
    io_service_.run();
}

void AsioReactor::stop() {
    LOG_INFO(logger, "stop");
    rmq_publisher_factory_.stop();
    for (auto &udp_listener : udp_listeners_) {
        udp_listener->stop();
    }
    io_service_.stop();

}
