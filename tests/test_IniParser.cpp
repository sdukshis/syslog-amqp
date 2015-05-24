//
// Created by Pavel Filonov on 23.05.15.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/IniParser.h"
#include "../src/Logging.h"

class MockHandler: public IniParser::Handler {
public:
    MOCK_METHOD1(onSection, void(const std::string &));
    MOCK_METHOD1(onKey, void(const std::string &));
    MOCK_METHOD1(onValue, void(const std::string &));
};

TEST(IniParser, SingleSection) {
    MockHandler handler;

    EXPECT_CALL(handler, onSection("test"))
                .Times(1);

    IniParser parser;

    std::string input = "[test]";

    std::istringstream ss(input);

    parser.parse(ss, &handler);
}

TEST(IniParser, MultiSection) {
    MockHandler handler;

    EXPECT_CALL(handler, onSection("one"))
            .Times(1);
    EXPECT_CALL(handler, onSection("two"))
            .Times(1);
    EXPECT_CALL(handler, onSection("three"))
            .Times(1);
    IniParser parser;

    std::string input = R"(
[one]

[two]

[three]
)";

    std::istringstream ss(input);
    ss.unsetf(std::ios::skipws);

    parser.parse(ss, &handler);
}

TEST(IniParser, SingleKey) {
    MockHandler handler;

    EXPECT_CALL(handler, onKey("key"))
                .Times(1);
    EXPECT_CALL(handler, onValue("value"))
                .Times(1);
    IniParser parser;
    std::string input = R"(
key=value
)";
    std::istringstream ss(input);
    ss.unsetf(std::ios::skipws);

    parser.parse(ss, &handler);
}

TEST(IniParser, MultipleKeys) {
    MockHandler handler;

    EXPECT_CALL(handler, onKey("key"))
            .Times(2);
    EXPECT_CALL(handler, onValue("value"))
            .Times(2);
    IniParser parser;
    std::string input = R"(
key=value

key=value
)";
    std::istringstream ss(input);
    ss.unsetf(std::ios::skipws);

    parser.parse(ss, &handler);
}

TEST(IniParser, SkipComments) {
    MockHandler handler;

    EXPECT_CALL(handler, onSection("test"))
            .Times(1);
    EXPECT_CALL(handler, onKey("key"))
            .Times(2);
    EXPECT_CALL(handler, onValue("value"))
            .Times(2);
    IniParser parser;
    std::string input = R"(
; Some test comments
; and more
[test]
   ; some more comments with special chars = [ ] ;
key=value  ; key value comment

key=value# hash comment
)";
    std::istringstream ss(input);
    ss.unsetf(std::ios::skipws);

    parser.parse(ss, &handler);
}

TEST(IniParser, EmptyHandler) {
    std::string input = R"(
; Some test comments
; and more
[test]
   ; some more comments with special chars = [ ] ;
key=value  ; key value comment

key=value# hash comment
)";
    std::istringstream ss(input);
    ss.unsetf(std::ios::skipws);

    IniParser parser;
    parser.parse(ss, nullptr);
}