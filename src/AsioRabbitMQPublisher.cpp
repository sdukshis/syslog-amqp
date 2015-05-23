#include "AsioRabbitMQPublisher.h"

#include <assert.h>

#include "Logging.h"

static auto &logger = Logger::getLogger("AsioRabbitMQPublisher");
using namespace asio::ip;

namespace {
    AMQP::ExchangeType convert_exchange_type(AsioRabbitMQPublisher::ExchangeType type) {
        switch (type) {
            case RabbitMQPublisher::ExchangeType::Topic:
                return AMQP::ExchangeType::topic;
            case RabbitMQPublisher::ExchangeType::Fanout:
                return AMQP::ExchangeType::fanout;
            case RabbitMQPublisher::ExchangeType::Direct:
                return AMQP::ExchangeType::direct;
        }
    }
}

AsioRabbitMQPublisher::AsioRabbitMQPublisher(AMQP::Channel *channel)
        : channel_{channel} {
    assert(channel_.get());
};

AsioRabbitMQPublisher::~AsioRabbitMQPublisher() {
    if (channel_) {
        channel_->close();
    }
}

void AsioRabbitMQPublisher::declareExchange(const std::string &name, ExchangeType type) {
    assert(channel_);
    std::clog << "AsioRabbitMQPublisher::declareExchange" << std::endl;
    channel_->declareExchange(name, convert_exchange_type(type));
}

void AsioRabbitMQPublisher::basicPublish(const std::string &exchange, const std::string &routing_key, const char *data,
                                         std::size_t length) {
    assert(channel_);
    std::clog << "AsioRabbitMQPublisher::basicPublish" << std::endl;
    channel_->publish(exchange, routing_key, data, length);
}


void AsioRabbitMQPublisher::close() {
    assert(channel_);
    channel_->close();
}
