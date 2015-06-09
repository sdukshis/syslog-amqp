#include "gtest-inc.h"

#include "../src/DataObserver.h"
#include "../src/DataObservable.h"

class MockDataObserver: public DataObserver {
public:
    MOCK_METHOD2(onBegin, void(const Endpoint &, const std::string &));
    MOCK_METHOD2(onData, void(const char *, std::size_t));
    MOCK_METHOD0(onEnd, void());
};

using ::testing::_;

TEST(DataObservable, addSignleObserver) {
    DataObservable observable;
    auto observer = std::make_shared<MockDataObserver>();

    observable.addObserver(observer);

    EXPECT_CALL(*observer, onBegin(_, _))
                .Times(1);

    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");
}

TEST(DataObservable, addTwoObservers) {
    DataObservable observable;

    auto first_observer = std::make_shared<MockDataObserver>();
    auto second_observer = std::make_shared<MockDataObserver>();

    observable.addObserver(first_observer);
    observable.addObserver(second_observer);

    EXPECT_CALL(*first_observer, onBegin(_, _))
                .Times(1);
    EXPECT_CALL(*second_observer, onBegin(_, _))
                .Times(1);

    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");
}

TEST(DataObservable, delObserver) {
    DataObservable observable;

    auto observer = std::make_shared<MockDataObserver>();

    observable.addObserver(observer);

    EXPECT_CALL(*observer, onBegin(_, _))
                .Times(1);

    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");

    observable.delObserver(observer);
    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");
}

TEST(DataObservable, onData) {
    DataObservable observable;
    auto observer = std::make_shared<MockDataObserver>();

    observable.addObserver(observer);

    EXPECT_CALL(*observer, onData("12345", 5))
                .Times(1);

    observable.notifyObserversOnData("12345", 5);
}

TEST(DataObservable, onEnd) {
    DataObservable observable;
    auto observer = std::make_shared<MockDataObserver>();

    observable.addObserver(observer);

    EXPECT_CALL(*observer, onEnd())
                .Times(1);

    observable.notifyObserversOnEnd();
}

TEST(DataObservable, addObserverTwice) {
    DataObservable observable;

    auto observer = std::make_shared<MockDataObserver>();

    observable.addObserver(observer);
    observable.addObserver(observer);

    EXPECT_CALL(*observer, onBegin(_, _))
                .Times(2);

    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");

    observable.delObserver(observer);
    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");
}

TEST(DataObservable, moveCtor) {
    DataObservable observable;

    auto observer = std::make_shared<MockDataObserver>();

    EXPECT_CALL(*observer, onBegin(_, _))
                .Times(1);

    observable.addObserver(observer);

    DataObservable new_observable{std::move(observable)};

    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");

    new_observable.notifyObserversOnBegin(Endpoint{"", 0}, "");
}

TEST(DataObservable, moveAssignment) {
    DataObservable observable;

    auto observer = std::make_shared<MockDataObserver>();

    EXPECT_CALL(*observer, onBegin(_, _))
            .Times(1);

    observable.addObserver(observer);

    DataObservable new_observable;

    new_observable = std::move(observable);

    observable.notifyObserversOnBegin(Endpoint{"", 0}, "");

    new_observable.notifyObserversOnBegin(Endpoint{"", 0}, "");
}