//
// Created by Pavel Filonov on 17.05.15.
//

#ifndef SYSLOG_AMQP_ASIORABBITMQPUBLISHERFACTORY_H
#define SYSLOG_AMQP_ASIORABBITMQPUBLISHERFACTORY_H

#include "RabbitMQPublisherFactory.h"
#include "Endpoint.h"
#include "RabbitMQPublisher.h"

#include <vector>
#include <memory>

#include <asio.hpp>
#include <amqpcpp.h>

class AsioRabbitMQPublisherFactory : public RabbitMQPublisherFactory, public AMQP::ConnectionHandler {
public:
    AsioRabbitMQPublisherFactory(const Endpoint &server_endpoint, asio::io_service &);

    AsioRabbitMQPublisherFactory(const AsioRabbitMQPublisherFactory &) = delete;

    AsioRabbitMQPublisherFactory &operator=(const AsioRabbitMQPublisherFactory &) = delete;

    ~AsioRabbitMQPublisherFactory();

    virtual RabbitMQPublisher *createRabbitMQPublisher() override;

    virtual void onData(AMQP::Connection *connection, const char *buffer, size_t size) override;

    virtual void onError(AMQP::Connection *connection, const char *message) override;

    virtual void onConnected(AMQP::Connection *connection) override;

    virtual void onClosed(AMQP::Connection *connection) override;

    virtual void stop() override;

protected:
    void doRead();

private:
    Endpoint server_endpoint_;
    asio::io_service &io_;
    asio::ip::tcp::socket socket_;
    std::array<char, 64 * 1024> buffer_;
    std::unique_ptr<AMQP::Connection> connection_;
    bool async_mode_ = false;
    std::vector<std::unique_ptr<RabbitMQPublisher>> publishers_;
};


#endif //SYSLOG_AMQP_ASIORABBITMQPUBLISHERFACTORY_H
