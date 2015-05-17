//
// Created by Pavel Filonov on 17.05.15.
//

#ifndef SYSLOG_AMQP_ASIOREACTOR_H
#define SYSLOG_AMQP_ASIOREACTOR_H

#include "AbstractReactor.h"
#include "AsioRabbitMQPublisherFactory.h"

#include <asio.hpp>

class AsioReactor : public AbstractReactor {
public:
    AsioReactor();

    virtual ~AsioReactor();

    virtual void run() override;

    AsioReactor(const AsioReactor &) = delete;

    AsioReactor operator=(const AsioReactor &) = delete;


    virtual UDPListener *createUDPListener(const Endpoint &endpoint) override;

    virtual RabbitMQPublisher *createRabbitMQPublisher() override;

private:
    asio::io_service io_service_;
    AsioRabbitMQPublisherFactory rmq_publisher_factory_;
public:
    virtual void stop() override;
};


#endif //SYSLOG_AMQP_ASIOREACTOR_H
