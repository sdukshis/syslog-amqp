#include "gtest-inc.h"

#include "../src/Endpoint.h"

TEST(Endpoint, paramsCtor) {
    Endpoint e{"127.0.0.1", 8080};

    ASSERT_EQ("127.0.0.1", e.getAddr());
    ASSERT_EQ(8080, e.getPort());
}

TEST(Endpoint, copyCtor) {
    Endpoint orig{"192.0.0.1", 8080};

    Endpoint copy{orig};

    ASSERT_EQ("192.0.0.1", copy.getAddr());
    ASSERT_EQ(8080, copy.getPort());
}

TEST(Endpoint, moveCtor) {
    Endpoint orig{"192.0.0.1", 8080};

    Endpoint dest{std::move(orig)};

    ASSERT_EQ("192.0.0.1", dest.getAddr());
    ASSERT_EQ(8080, dest.getPort());
}

TEST(Endpoint, copyAssign) {
    Endpoint orig{"192.0.2.1", 8080};

    Endpoint dest{"127.0.0.1", 123};

    dest = orig;

    ASSERT_EQ("192.0.2.1", dest.getAddr());
    ASSERT_EQ(8080, dest.getPort());
}

TEST(Endpoint, moveAssign) {
    Endpoint orig{"192.0.2.1", 8080};

    Endpoint dest{"127.0.0.1", 123};

    dest = std::move(orig);

    ASSERT_EQ("192.0.2.1", dest.getAddr());
    ASSERT_EQ(8080, dest.getPort());
}

TEST(Endpoint, equal) {
    ASSERT_TRUE((Endpoint{"192.0.2.1", 8080} == Endpoint{"192.0.2.1", 8080}));
    ASSERT_FALSE((Endpoint{"192.0.2.1", 8080} == Endpoint{"192.0.2.1", 8081}));
    ASSERT_FALSE((Endpoint{"192.0.2.1", 8080} == Endpoint{"192.0.2.2", 8080}));
    ASSERT_FALSE((Endpoint{"192.0.2.1", 8080} == Endpoint{"192.0.2.2", 8081}));
}

TEST(Endpoint, toString) {
    ASSERT_EQ("127.0.0.1:8080", (Endpoint{"127.0.0.1", 8080}.toString()));
    ASSERT_EQ("*:8080", (Endpoint{"", 8080}.toString()));
}