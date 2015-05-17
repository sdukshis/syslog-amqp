#include "DataObservable.h"

#include <algorithm>
#include <assert.h>

#include "Endpoint.h"
#include "DataObserver.h"

DataObservable::DataObservable(DataObservable &&other)
    : observers_{std::move(other.observers_)} { }

DataObservable & DataObservable::operator=(DataObservable &&other) {
    assert(this != std::addressof(other));
    observers_ = std::move(other.observers_);

    return *this;
}

void DataObservable::addObserver(DataObserver *observer) {
    assert(observer != nullptr);
    observers_.emplace_back(observer);
}

void DataObservable::delObserver(DataObserver *observer) {
    assert(observer != nullptr);
    observers_.erase(std::remove(std::begin(observers_),
                                 std::end(observers_),
                                 observer),
                     std::end(observers_));
}

void DataObservable::notifyObserversOnBegin(const Endpoint &recv_host,
                                            const std::string &tag) {
    for(auto observer : observers_) {
        observer->onBegin(recv_host, tag);
    }
}

void DataObservable::notifyObserversOnData(const char *buffer,
                                           std::size_t length) {
    for (auto observer: observers_) {
        observer->onData(buffer, length);
    }
}

void DataObservable::notifyObserversOnEnd() {
    for (auto observer : observers_) {
        observer->onEnd();
    }
}
