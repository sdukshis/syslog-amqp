//
// Created by Pavel Filonov on 17.05.15.
//

#ifndef SYSLOG_AMQP_STDOUTPUBLISHER_H
#define SYSLOG_AMQP_STDOUTPUBLISHER_H

#include "MessageObserver.h"

#include <memory>

class MessageEncoder;

class StdoutPublisher : public MessageObserver {
public:
    StdoutPublisher(const std::shared_ptr<MessageEncoder> &);

    ~StdoutPublisher() { }

    virtual void onMessage(const Message &message) override;

private:
    std::shared_ptr<MessageEncoder> encoder_;
};


#endif //SYSLOG_AMQP_STDOUTPUBLISHER_H
