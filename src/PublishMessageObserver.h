#ifndef SYSLOG_AMQP_PUBLISHMESSAGEOBSERVER_H
#define SYSLOG_AMQP_PUBLISHMESSAGEOBSERVER_H

#include <string>

#include "MessageObserver.h"
#include "MessageEncoder.h"
#include "RabbitMQPublisher.h"

class PublishMessageObserver : public MessageObserver {
public:
    PublishMessageObserver(RabbitMQPublisher &, const std::string &exchange, RabbitMQPublisher::ExchangeType,
                           const std::string &routing_key, MessageEncoder &);

    PublishMessageObserver(const PublishMessageObserver &) = delete;

    PublishMessageObserver &operator=(const PublishMessageObserver &) = delete;

    ~PublishMessageObserver();

    void onMessage(const Message &) override;

private:
    RabbitMQPublisher &publisher_;
    std::string exchange_;
    RabbitMQPublisher::ExchangeType exchange_type_;
    std::string routing_key_;
    MessageEncoder &encoder_;
};


#endif //SYSLOG_AMQP_PUBLISHMESSAGEOBSERVER_H
