#include <gtest/gtest.h>
#include <MessageId.h>

#include <regex>
#include <string>

const std::regex uuid_pattern{"[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}"};

TEST(MessageId, defaultCtor) {
    for (auto i = 0; i < 10; ++i) {
        MessageId id;
        auto strId = id.toString();
        ASSERT_TRUE(std::regex_match(strId, uuid_pattern));
    }
}

TEST(MessageId, copyCtor) {
    MessageId firstId;

    MessageId secondId{firstId};

    ASSERT_EQ(firstId, secondId);
}

TEST(MessageId, moveCtor) {
    MessageId firstId;

    MessageId secondId{std::move(firstId)};

    ASSERT_TRUE(std::regex_match(secondId.toString(), uuid_pattern));
}

TEST(MessageId, toString) {
    MessageId id;

    std::string strId;
    id.toString(strId);

    ASSERT_EQ(strId, id.toString());
}

TEST(MessageId, copyAssign) {
    MessageId firstId;

    MessageId secondId;

    secondId = firstId;

    ASSERT_EQ(firstId, secondId);
}

TEST(MessageId, notEqual) {
    MessageId firstId, secondId;

    ASSERT_NE(firstId, secondId);
}
