//
// Created by Pavel Filonov on 23.05.15.
//

#include "gtest-inc.h"

#include "../src/Options.h"

#include <stdexcept>
#include <string>
#include <sstream>

TEST(Options, UDPInput) {
    std::string config = R"(
[input]
protocol=UDP
listen=0.0.0.0
port=1313

)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ss >> options;

    ASSERT_EQ(1, options.inputs.size());
    const auto &input = options.inputs.at(0);
    ASSERT_EQ(InputOptions::Protocol::UDP, input.protocol);
    ASSERT_EQ("0.0.0.0", input.endpoint.getAddr());
    ASSERT_EQ(1313, input.endpoint.getPort());

}

TEST(Options, StdoutOutput) {
    std::string config = R"(
[output]
driver=stdout

)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ss >> options;
    ASSERT_EQ(1, options.outputs.size());
    const auto &output = options.outputs.at(0);
    ASSERT_EQ(OutputOptins::Type::Stdout, output.type);
}

TEST(Options, RabbitMQOutput) {
    std::string config = R"(
[output]
driver=rabbitmq
host=192.0.2.1
port=5672
exchange=events
routing_key=raw

)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ss >> options;
    ASSERT_EQ(1, options.outputs.size());
    const auto &output = options.outputs.at(0);
    ASSERT_EQ(OutputOptins::Type::RabbitMQ, output.type);
    ASSERT_EQ("192.0.2.1", output.endpoint.getAddr());
    ASSERT_EQ(5672, output.endpoint.getPort());
    ASSERT_EQ("events", output.exchange);
    ASSERT_EQ("raw", output.routing_key);
}

TEST(Options, UnknownInputProtocol) {
    std::string config = R"(
[input]
protocol=Unknown
listen=0.0.0.0
port=1313

)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ASSERT_THROW(ss >> options, std::invalid_argument);
}

TEST(Options, InputListenNotFound) {
    std::string config = R"(
[input]
protocol=UDP
port=1313

)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ASSERT_THROW(ss >> options, std::invalid_argument);
}

TEST(Options, InputPortNotFound) {
    std::string config = R"(
[input]
protocol=UDP
listen=0.0.0.0
)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ASSERT_THROW(ss >> options, std::invalid_argument);
}

TEST(Options, InputInvalidPort) {
    std::string config = R"(
[input]
protocol=UDP
listen=0.0.0.0
port=invalid
)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ASSERT_THROW(ss >> options, std::invalid_argument);
}

TEST(Options, DISABLED_InputInvalidAddress) {
    std::string config = R"(
[input]
protocol=UDP
listen=0.0.
port=1313
)";

    std::istringstream ss(config);
    ss.unsetf(std::ios::skipws);

    Options options;
    ASSERT_THROW(ss >> options, std::invalid_argument);
}