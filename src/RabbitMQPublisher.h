//
// Created by Pavel Filonov on 16.05.15.
//

#ifndef SYSLOG_AMQP_AMQPCHANNEL_H
#define SYSLOG_AMQP_AMQPCHANNEL_H

#include <string>

class RabbitMQPublisher {
public:
    enum class ExchangeType {
        Fanout,
        Direct,
        Topic,
    };

    virtual ~RabbitMQPublisher() {}

    virtual void declareExchange(const std::string &exchange, ExchangeType) = 0;

    virtual void basicPublish(const std::string &exchange, const std::string &routing_key, const char *data,
                              std::size_t length) = 0;
};


#endif //SYSLOG_AMQP_AMQPCHANNEL_H
