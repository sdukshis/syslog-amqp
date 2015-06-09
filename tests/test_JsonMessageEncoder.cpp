#include "gtest-inc.h"

#include "../src/Endpoint.h"
#include "../src/Message.h"
#include "../src/JsonMessageEncoder.h"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
std::string time_t_to_str(const time_t t) {
    std::stringstream ss;
    // FIXME: gcc-4.9 still doesn't support std::put_time
    size_t format_size = sizeof("YYYY-MM-DDTHH:SS:MM+HH:MM");
    char str[format_size + 1];
    std::strftime(str, format_size, "%FT%T%z", std::localtime(&t));

    // ss << std::put_time(std::localtime(&t), "%FT%T%z");
    return str;
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