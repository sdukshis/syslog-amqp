#ifndef DATAOBSERVER_H
#define DATAOBSERVER_H

#include "Endpoint.h"

class DataObserver {
 public:
    virtual ~DataObserver() { }

    virtual void onBegin(const Endpoint &recv_host, const std::string &tag) = 0;

    virtual void onData(const char *buffer, std::size_t length) = 0;

    virtual void onEnd() = 0;
};  // class DataObserver

#endif  // DATAOBSERVER_H
