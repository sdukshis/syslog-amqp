#ifndef MESSAGEOBSERVER_H
#define MESSAGEOBSERVER_H

#include "Message.h"

class MessageObserver {
 public:
    virtual ~MessageObserver() { }

    virtual void onMessage(const Message &) = 0;
};  // class MessageObserver

#endif  // MESSAGEOBSERVER_H
