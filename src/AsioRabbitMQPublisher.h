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

class AsioRabbitMQPublisher : public RabbitMQPublisher, public AMQP::ConnectionHandler {
public:
    AsioRabbitMQPublisher(const Endpoint &server_endpoint, asio::io_service &);

    AsioRabbitMQPublisher(const AsioRabbitMQPublisher &) = delete;

    AsioRabbitMQPublisher &operator=(const AsioRabbitMQPublisher &) = delete;

    ~AsioRabbitMQPublisher();

    void declareExchange(const std::string &name, ExchangeType) override;

    void basicPublish(const std::string &exchange, const std::string &routing_key, const char *data,
                      std::size_t length) override;

    void onConnected(AMQP::Connection *) override;

    void onData(AMQP::Connection *, const char *data, std::size_t size) override;

    void onError(AMQP::Connection *, const char *message) override;

    void onClosed(AMQP::Connection *) override;

protected:
    void doRead();

private:
    Endpoint server_endpoint_;
    asio::io_service &io_;
    asio::ip::tcp::socket socket_;
    std::unique_ptr<AMQP::Connection> connection_;
    std::unique_ptr<AMQP::Channel> channel_;
    std::array<char, 64*1024> buffer_;
};


#endif //SYSLOG_AMQP_ASIORABBITMQPUBLISHER_H
