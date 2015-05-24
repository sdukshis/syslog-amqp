#ifndef MESSAGEOBSERVABLE_H
#define MESSAGEOBSERVABLE_H

#include <vector>
#include <memory>

class Message;
class MessageObserver;

class MessageObservable {
 public:
    MessageObservable() = default;

    MessageObservable(const MessageObservable &) = delete;

    MessageObservable(MessageObservable &&);

    virtual ~MessageObservable() { }

    MessageObservable & operator=(const MessageObservable &) = delete;

    MessageObservable & operator=(MessageObservable &&);

    void addObserver(const std::shared_ptr<MessageObserver> &);

    void delObserver(const std::shared_ptr<MessageObserver> &);

    void notifyObservers(const Message &);

 private:
    std::vector<std::shared_ptr<MessageObserver>> observers_;
};  // class MessageObservable

#endif  // MESSAGEOBSERVABLE_H
