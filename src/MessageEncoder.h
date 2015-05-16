#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

class Message;

class MessageEncoder {
public:
    virtual ~MessageEncoder() { }

    virtual void encode(const Message &) = 0;

    virtual const char * begin() const = 0;

    virtual const char * end() const = 0;
};
#endif //MESSAGEENCODER_H
