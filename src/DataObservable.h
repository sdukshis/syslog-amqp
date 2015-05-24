#ifndef DATAOBSERVABLE_H
#define DATAOBSERVABLE_H

#include <vector>
#include <string>
#include <memory>

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

    void addObserver(const std::shared_ptr<DataObserver> &);

    void delObserver(const std::shared_ptr<DataObserver> &);

    void notifyObserversOnBegin(const Endpoint &recv_host,
                                const std::string &tag);

    void notifyObserversOnData(const char *buffer, std::size_t length);

    void notifyObserversOnEnd();

 private:
    std::vector<std::shared_ptr<DataObserver>> observers_;
};  // class DataObservable

#endif  // DATAOBSERVABLE_H
