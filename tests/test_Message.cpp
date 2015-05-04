#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/Message.h"

TEST(Message, paramCtor) {
    Message msg{Endpoint{"192.0.2.1", 1234}, "test"};

    ASSERT_EQ((Endpoint{"192.0.2.1", 1234}), msg.getRecvHost());
    ASSERT_EQ((Datetime{}), msg.getRecvTime());
    ASSERT_EQ("test", msg.getRaw());
}

TEST(Message, copyCtor) {
    Message orig{Endpoint{"192.0.2.1", 1234}, "test"};

    Message copy{orig};

    ASSERT_EQ(orig, copy);
}

class MockTagVisitor {
public:
    MOCK_METHOD1(Call, void(const std::string &));
    void operator()(const std::string &s) { Call(s); }
};

using ::testing::_;

TEST(Message, addTag) {
    Message orig{Endpoint{"192.0.2.1", 1234}, ""};

    orig.addTag("tag1");
    orig.addTag("tag2");
    orig.addTag("tag3");

    MockTagVisitor visitor;
    EXPECT_CALL(visitor, Call("tag1"))
            .Times(1);
    EXPECT_CALL(visitor, Call("tag2"))
            .Times(1);
    EXPECT_CALL(visitor, Call("tag3"))
            .Times(1);

    orig.visitTags([&visitor](const std::string &s) { visitor(s); });
}

TEST(Message, addDuplicateTag) {
    Message msg{Endpoint{"192.0.2.1", 8080}, ""};

    msg.addTag("tag");
    msg.addTag("tag");

    MockTagVisitor visitor;
    EXPECT_CALL(visitor, Call("tag"))
            .Times(1);

    msg.visitTags([&visitor](const std::string &s) { visitor(s); });
}

TEST(Message, delTag) {
    Message msg{Endpoint{"192.0.2.1", 8080}, ""};

    msg.addTag("tag1");
    msg.addTag("tag2");

    {
        MockTagVisitor visitor;
        EXPECT_CALL(visitor, Call(_))
                .Times(2);

        msg.visitTags([&visitor](const std::string &s) { visitor(s); });
    }

    ASSERT_TRUE(msg.delTag("tag2"));
    ASSERT_FALSE(msg.delTag("tag2"));

    {
        MockTagVisitor visitor;
        EXPECT_CALL(visitor, Call(_))
                    .Times(1);
        msg.visitTags([&visitor](const std::string &s) { visitor(s); });
    }
}

class MockHeaderVisitor {
public:
    MOCK_METHOD2(Call, void(const std::string &, const std::string &));
};

TEST(Message, setHeader) {
    Message msg{Endpoint{"192.0.2.1", 8080}, ""};

    msg.setHeader("key1", "value1");
    msg.setHeader("key2", "value2");
    msg.setHeader("key3", "value3");

    MockHeaderVisitor visitor;
    EXPECT_CALL(visitor, Call("key1", "value1"))
                .Times(1);
    EXPECT_CALL(visitor, Call("key2", "value2"))
                .Times(1);
    EXPECT_CALL(visitor, Call("key3", "value3"))
                .Times(1);

    msg.visitHeaders([&visitor](const std::string &key, const std::string &value) { visitor.Call(key, value); });
}

TEST(Message, delHeader) {
    Message msg{Endpoint{"192.0.2.1", 8080}, ""};

    msg.setHeader("key1", "value1");
    msg.setHeader("key2", "value2");

    {
        MockHeaderVisitor visitor;
        EXPECT_CALL(visitor, Call(_, _))
                .Times(2);

        msg.visitHeaders([&visitor](const std::string &key, const std::string &value) { visitor.Call(key, value); });
    }

    ASSERT_TRUE(msg.delHeader("key2"));
    ASSERT_FALSE(msg.delHeader("key2"));
    {
        MockHeaderVisitor visitor;
        EXPECT_CALL(visitor, Call(_, _))
                .Times(1);

        msg.visitHeaders([&visitor](const std::string &key, const std::string &value) { visitor.Call(key, value); });
    }

}
