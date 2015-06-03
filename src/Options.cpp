//
// Created by Pavel Filonov on 18.05.15.
//

#include "Options.h"

#include <map>
#include <string>

#include "IniParser.h"

std::string to_string(InputOptions::Protocol protocol) {
    switch (protocol) {
        case InputOptions::Protocol::UDP:
            return "UDP";
        default:
            throw std::logic_error{"Unknown protocol type"};
    }
}

std::ostream &operator<<(std::ostream &stream, const InputOptions &input) {
    stream << "{protocol: " << to_string(input.protocol) << ", "
    << "endpoint: " << input.endpoint << "}";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const OutputOptins &output) {
    switch (output.type) {
        case OutputOptins::Type::RabbitMQ:
            stream << "{endpoint: " << output.endpoint << ", "
            << "exchange: " << output.exchange << ", "
            << "routing_key: " << output.routing_key << "}";
            break;
        case OutputOptins::Type::Stdout:
            stream << "{stdout}";
            break;
    }
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Options &options) {
    stream << "inputs: [";
    for (const auto &input: options.inputs) {
        stream << input;
    }
    stream << "], outputs: [";
    for (const auto &output: options.outputs) {
        stream << output;
    }
    stream << "]";
    return stream;
}

class OptionsHandler : public IniParser::Handler {
public:
    OptionsHandler() {
        auto pair = config_.emplace("global", section_t());
        current_section_ = pair.first;
    }

    void onSection(const std::string &name)

    override {
        auto pair = config_.emplace(name, section_t{});
        current_section_ = pair.first;
    }

    void onKey(const std::string &key)

    override {
        current_key_ = key;
    }

    void onValue(const std::string &value)

    override {
        current_section_->second.emplace(current_key_, value);
    }

    Options getOptions() const {
        Options options;
        auto input = config_.find("input");
        if (input != config_.cend()) {
            auto protocol = input->second.find("protocol");
            if (protocol == input->second.cend()) {
                throw std::invalid_argument{"input protocol not found"};
            };
            auto listen = input->second.find("listen");
            if (listen == input->second.cend()) {
                throw std::invalid_argument{"input listen not found"};
            };
            auto port = input->second.find("port");
            if (port == input->second.cend()) {
                throw std::invalid_argument{"input port not found"};
            };

            if (protocol->second == "UDP") {
                options.inputs.emplace_back(InputOptions::Protocol::UDP,
                                            Endpoint{listen->second,
                                                     static_cast<Endpoint::port_t >(std::stoi(port->second))});
            } else {
                throw std::invalid_argument{"Unknown protocol: " + protocol->second};
            }
        }

        auto output = config_.find("output");
        if (output != config_.cend()) {
            auto driver = output->second.find("driver");
            if (driver == output->second.cend()) {
                throw std::invalid_argument{"output driver not set"};
            }


            if (driver->second == "stdout") {
                options.outputs.emplace_back(OutputOptins::Type::Stdout);
            } else if (driver->second == "rabbitmq") {
                OutputOptins rmq_options{OutputOptins::Type::RabbitMQ};
                auto host = output->second.find("host");
                if (host == output->second.cend()) {
                    throw std::invalid_argument{"output host not found"};
                }
                auto port = output->second.find("port");
                if (port == output->second.cend()) {
                    throw std::invalid_argument{"output port not found"};
                }
                rmq_options.endpoint = Endpoint{host->second, static_cast<Endpoint::port_t >(std::stoi(port->second))};
                auto exchange = output->second.find("exchange");
                if (exchange == output->second.cend()) {
                    throw std::invalid_argument{"output exchange not found"};
                }
                rmq_options.exchange = exchange->second;
                auto routing_key = output->second.find("routing_key");
                if (routing_key == output->second.cend()) {
                    throw std::invalid_argument{"output routing key not found"};
                }
                rmq_options.routing_key = routing_key->second;
                options.outputs.emplace_back(rmq_options);
            }
        }
        return options;
    }

private:
    using section_t = std::map<std::string, std::string>;
    using config_t = std::map<std::string, section_t>;

    config_t config_;
    config_t::iterator current_section_;
    std::string current_key_;
};

std::istream &operator>>(std::istream &stream, Options &options) {
    OptionsHandler handler;
    IniParser parser;
    stream.unsetf(std::ios::skipws);
    parser.parse(stream, &handler);
    options = handler.getOptions();
    return stream;
}