//
// Created by Pavel Filonov on 16.05.15.
//

#ifndef SYSLOG_AMQP_ASIORABBITMQPUBLISHER_H
#define SYSLOG_AMQP_ASIORABBITMQPUBLISHER_H

#include <memory>

#include "RabbitMQPublisher.h"
#include "Endpoint.h"

#include <asio.hpp>
#include <amqpcpp.h>

class AsioRabbitMQPublisher : public RabbitMQPublisher {
public:
    AsioRabbitMQPublisher(AMQP::Channel *);

    AsioRabbitMQPublisher(const AsioRabbitMQPublisher &) = delete;

    AsioRabbitMQPublisher &operator=(const AsioRabbitMQPublisher &) = delete;

    ~AsioRabbitMQPublisher();

    void declareExchange(const std::string &name, ExchangeType) override;

    void basicPublish(const std::string &exchange, const std::string &routing_key, const char *data,
                      std::size_t length) override;

protected:
    void doRead();

private:
    std::unique_ptr<AMQP::Channel> channel_;
};


#endif //SYSLOG_AMQP_ASIORABBITMQPUBLISHER_H
