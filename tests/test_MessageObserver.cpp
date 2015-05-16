#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/MessageObservable.h"
#include "../src/MessageObserver.h"
#include "../src/Message.h"

class MockMessageObserver : public MessageObserver {
public:
    MOCK_METHOD1(onMessage, void(const Message &));
};

using ::testing::_;

TEST(MessageObserver, SingleObserver) {
    MessageObservable observable;

    MockMessageObserver mock_observer;

    EXPECT_CALL(mock_observer, onMessage(_))
            .Times(1);

    observable.addObserver(&mock_observer);

    observable.notifyObservers(Message{Endpoint{"192.0.2.1", 1313}, "Hello"});
}

TEST(MessageObserver, TwoObservers) {
    MessageObservable observable;

    MockMessageObserver first_observer;

    EXPECT_CALL(first_observer, onMessage(_))
            .Times(1);
    MockMessageObserver second_observer;
    EXPECT_CALL(second_observer, onMessage(_))
            .Times(1);
    observable.addObserver(&first_observer);
    observable.addObserver(&second_observer);

    observable.notifyObservers(Message{Endpoint{"192.0.2.1", 1313}, "Hello"});
}