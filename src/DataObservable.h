#ifndef DATAOBSERVABLE_H
#define DATAOBSERVABLE_H

#include <vector>

class DataObserver;
class Endpoint;

class DataObservable {
 public:
    DataObservable() = default;

    DataObservable(const DataObservable &) = delete;

    DataObservable(DataObservable &&);

    virtual ~DataObservable() { }

    DataObservable & operator=(const DataObservable &) = delete;

    DataObservable & operator=(DataObservable &&);

    void addObserver(DataObserver *);

    void delObserver(DataObserver *);

    void notifyObserversOnBegin(const Endpoint &recv_host,
                                const std::string &tag);

    void notifyObserversOnData(const char *buffer, std::size_t length);

    void notifyObserversOnEnd();

 private:
    std::vector<DataObserver *> observers_;
};  // class DataObservable

#endif  // DATAOBSERVABLE_H
