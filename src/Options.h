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
    Protocol protocol;
    Endpoint endpoint;
};

struct RabbitMQOptions {
    RabbitMQOptions()
            : endpoint{"localhost", 5672} {}
    Endpoint endpoint;
    std::string exchange;
    std::string routing_key;
};

struct Options {
    std::vector<InputOptions> inputs;
    RabbitMQOptions output;
};

std::string to_string(InputOptions::Protocol);

std::ostream & operator<<(std::ostream &, const InputOptions &);
std::ostream & operator<<(std::ostream &, const RabbitMQOptions &);
std::ostream & operator<<(std::ostream &, const Options &);

std::istream & operator>>(std::istream &, Options &);

#endif //SYSLOG_AMQP_OPTIONS_H
