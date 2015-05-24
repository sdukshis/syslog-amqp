#ifndef SYSLOG_AMQP_PUBLISHMESSAGEOBSERVER_H
#define SYSLOG_AMQP_PUBLISHMESSAGEOBSERVER_H

#include <string>
#include <memory>

#include "MessageObserver.h"
#include "MessageEncoder.h"
#include "RabbitMQPublisher.h"

class PublishMessageObserver : public MessageObserver {
public:
    PublishMessageObserver(RabbitMQPublisher &, const std::string &exchange,
                           RabbitMQPublisher::ExchangeType,
                           const std::string &routing_key, const std::shared_ptr<MessageEncoder> &);

    PublishMessageObserver(const PublishMessageObserver &) = delete;

    PublishMessageObserver &operator=(const PublishMessageObserver &) = delete;

    ~PublishMessageObserver();

    void onMessage(const Message &) override;

private:
    RabbitMQPublisher &publisher_;
    std::string exchange_;
    RabbitMQPublisher::ExchangeType exchange_type_;
    std::string routing_key_;
    std::shared_ptr<MessageEncoder> encoder_;
};


#endif //SYSLOG_AMQP_PUBLISHMESSAGEOBSERVER_H
