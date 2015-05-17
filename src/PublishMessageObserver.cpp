#include "PublishMessageObserver.h"

#include "RabbitMQPublisher.h"
#include "MessageEncoder.h"

PublishMessageObserver::PublishMessageObserver(RabbitMQPublisher &publisher, const std::string &exchange,
                                               RabbitMQPublisher::ExchangeType exchange_type,
                                               const std::string &routing_key, MessageEncoder &encoder)
        : publisher_{publisher}, exchange_{exchange}, exchange_type_{exchange_type}, routing_key_{routing_key},
          encoder_{encoder} {
    publisher.declareExchange(exchange_, exchange_type_);
}

PublishMessageObserver::~PublishMessageObserver() { }

void PublishMessageObserver::onMessage(const Message &msg) {
    encoder_.encode(msg);
    publisher_.basicPublish(exchange_, routing_key_, encoder_.begin(), encoder_.size());
}