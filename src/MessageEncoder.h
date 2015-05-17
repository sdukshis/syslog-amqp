#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include <cstdlib>

class Message;

class MessageEncoder {
public:
    virtual ~MessageEncoder() { }

    virtual void encode(const Message &) = 0;

    virtual const char * begin() const = 0;

    virtual const char * end() const = 0;

    std::size_t size() const { return end() - begin();}
};
#endif //MESSAGEENCODER_H
