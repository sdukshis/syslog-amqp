#include <gtest/gtest.h>

#include "../src/Endpoint.h"
#include "../src/Message.h"
#include "../src/JsonMessageEncoder.h"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
    std::string time_t_to_str(const time_t t) {
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%FT%T%z");
        return ss.str();
    }
}

TEST(JsonMessageEncoder, SingleMessage) {
    Message msg{Endpoint{"127.0.0.1", 1313}, "Hello"};

    JsonMessageEncoder encoder;

    encoder.encode(msg);

    ASSERT_EQ("{"
                      R"("recv_host":"127.0.0.1:1313",)"
                      R"("recv_time":")" + time_t_to_str(std::time(nullptr)) + R"(",)"
                      R"("raw":"Hello",)"
                      R"("tags":[],)"
                      R"("headers":{}})", (std::string{encoder.begin(), encoder.end()}));
}

TEST(JsonMessageEncoder, MessageWIthTags) {
    Message msg{Endpoint{"127.0.0.1", 1313}, "Hello"};
    msg.addTag("first");
    msg.addTag("second");

    JsonMessageEncoder encoder;

    encoder.encode(msg);

    ASSERT_EQ("{"
                      R"("recv_host":"127.0.0.1:1313",)"
                      R"("recv_time":")" + time_t_to_str(std::time(nullptr)) + R"(",)"
                      R"("raw":"Hello",)"
                      R"("tags":["first","second"],)"
                      R"("headers":{}})", (std::string{encoder.begin(), encoder.end()}));

}

TEST(JsonMessageEncoder, MessageWIthHeaders) {
    Message msg{Endpoint{"127.0.0.1", 1313}, "Hello"};
    msg.setHeader("1", "one");
    msg.setHeader("2", "two");

    JsonMessageEncoder encoder;

    encoder.encode(msg);

    ASSERT_EQ("{"
                      R"("recv_host":"127.0.0.1:1313",)"
                      R"("recv_time":")" + time_t_to_str(std::time(nullptr)) + R"(",)"
                      R"("raw":"Hello",)"
                      R"("tags":[],)"
                      R"("headers":{"1":"one","2":"two"}})", (std::string{encoder.begin(), encoder.end()}));

}