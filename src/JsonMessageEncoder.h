#ifndef SYSLOG_AMQP_JSONMESSAGEENCODER_H
#define SYSLOG_AMQP_JSONMESSAGEENCODER_H

#include "MessageEncoder.h"

#include "rapidjson/stringbuffer.h"

class JsonMessageEncoder: public MessageEncoder {
public:
    JsonMessageEncoder();

    ~JsonMessageEncoder();

    void encode(const Message &) override;

    const char * begin() const override;

    const char * end() const override;

private:
    rapidjson::StringBuffer buffer_;
};
#endif //SYSLOG_AMQP_JSONMESSAGEENCODER_H
