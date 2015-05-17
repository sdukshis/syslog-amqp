#include "MessageObservable.h"

#include <algorithm>
#include <assert.h>

#include "MessageObserver.h"

MessageObservable::MessageObservable(MessageObservable &&other)
    : observers_{other.observers_} { }

MessageObservable & MessageObservable::operator=(MessageObservable &&other) {
    assert(this != std::addressof(other));

    observers_ = std::move(other.observers_);

    return *this;
}

void MessageObservable::addObserver(MessageObserver *observer) {
    assert(observer != nullptr);

    observers_.emplace_back(observer);
}

void MessageObservable::delObserver(MessageObserver *observer) {
    observers_.erase(std::remove(std::begin(observers_),
                                 std::end(observers_),
                                 observer),
                     std::end(observers_));
}

void MessageObservable::notifyObservers(const Message &msg) {
    for (auto observer : observers_) {
        observer->onMessage(msg);
    }
}
