#include <gtest/gtest.h>

#include "../src/Message.h"

TEST(Message, paramCtor) {
    Message msg{Endpoint{"192.0.2.1", 1234}, "test"};


}