//
// Created by Pavel Filonov on 17.05.15.
//

#ifndef SYSLOG_AMQP_STDOUTPUBLISHER_H
#define SYSLOG_AMQP_STDOUTPUBLISHER_H

#include "MessageObserver.h"

class MessageEncoder;

class StdoutPublisher : public MessageObserver {
public:
    StdoutPublisher(MessageEncoder &);
    virtual void onMessage(const Message &message) override;

private:
    MessageEncoder &encoder_;
};


#endif //SYSLOG_AMQP_STDOUTPUBLISHER_H
