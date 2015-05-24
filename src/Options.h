//
// Created by Pavel Filonov on 18.05.15.
//

#ifndef SYSLOG_AMQP_OPTIONS_H
#define SYSLOG_AMQP_OPTIONS_H

#include <string>
#include <vector>
#include <iostream>

#include "Endpoint.h"

struct InputOptions {
    enum class Protocol {
        UDP,
    };

    InputOptions(Protocol proto, Endpoint endp)
            : protocol{proto}, endpoint{endp} { }

    Protocol protocol;
    Endpoint endpoint;
};

struct OutputOptins {
    enum class Type {
        RabbitMQ,
        Stdout,
    };

    OutputOptins(Type type_)
            : type{type_}
            , endpoint{"0.0.0.0", 0} { }

    Type type;
    Endpoint endpoint;
    std::string exchange;
    std::string routing_key;
};

struct Options {
    Options() = default;
    std::vector<InputOptions> inputs;
    std::vector<OutputOptins> outputs;
};

std::string to_string(InputOptions::Protocol);

std::ostream &operator<<(std::ostream &, const InputOptions &);

std::ostream &operator<<(std::ostream &, const OutputOptins &);

std::ostream &operator<<(std::ostream &, const Options &);

std::istream &operator>>(std::istream &, Options &);

#endif //SYSLOG_AMQP_OPTIONS_H
