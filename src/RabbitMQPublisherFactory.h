//
// Created by Pavel Filonov on 17.05.15.
//

#ifndef SYSLOG_AMQP_RABBITMQPUBLISHERFACTORY_H
#define SYSLOG_AMQP_RABBITMQPUBLISHERFACTORY_H

class RabbitMQPublisher;

class RabbitMQPublisherFactory {
public:
    virtual ~RabbitMQPublisherFactory() {}

    virtual RabbitMQPublisher * createRabbitMQPublisher() = 0;
};


#endif //SYSLOG_AMQP_RABBITMQPUBLISHERFACTORY_H
