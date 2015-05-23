//
// Created by Pavel Filonov on 18.05.15.
//

#include "Options.h"

std::string to_string(InputOptions::Protocol protocol) {
    switch(protocol) {
        case InputOptions::Protocol::UDP:
            return "UDP";
    }
}

std::ostream & operator<<(std::ostream &stream, const InputOptions &input) {
    stream << "{protocol: " << to_string(input.protocol) << ", "
           << "endpoint: " << input.endpoint << "}";
    return stream;
}

std::ostream & operator<<(std::ostream &stream, const RabbitMQOptions &rmq_options) {
    stream << "{endpoint: " << rmq_options.endpoint << ", "
           << "exchange: " << rmq_options.exchange << ", "
           << "routing_key: " << rmq_options.routing_key << "}";
    return stream;
}

std::ostream & operator<<(std::ostream &stream, const Options &options) {
    stream << "inputs: [";
    for (const auto &input: options.inputs) {
        stream << input;
    }
    stream << "], output: " << options.output;
    return stream;
}

std::istream & operator>>(std::istream &stream, Options &) {
    return stream;
}