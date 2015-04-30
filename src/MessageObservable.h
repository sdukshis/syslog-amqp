#ifndef MESSAGEOBSERVABLE_H
#define MESSAGEOBSERVABLE_H

#include <vector>

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

    void addObserver(MessageObserver *);

    void delObserver(MessageObserver *);

    void notifyObservers(const Message &);

 private:
    std::vector<MessageObserver *> observers_;
};  // class MessageObservable

#endif  // MESSAGEOBSERVABLE_H
