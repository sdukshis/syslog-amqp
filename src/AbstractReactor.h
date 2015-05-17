//
// Created by Pavel Filonov on 17.05.15.
//

#ifndef SYSLOG_AMQP_ABSTRACTREACTOR_H
#define SYSLOG_AMQP_ABSTRACTREACTOR_H

class Endpoint;
class UDPListener;
class RabbitMQPublisher;

class AbstractReactor {
public:
    virtual ~AbstractReactor() {}

    virtual UDPListener * createUDPListener(const Endpoint &) = 0;

    virtual RabbitMQPublisher * createRabbitMQPublisher() = 0;

    virtual void run() = 0;

    virtual void stop() = 0;
};
#endif //SYSLOG_AMQP_ABSTRACTREACTOR_H
