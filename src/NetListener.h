#ifndef NETLISTENER_H
#define NETLISTENER_H

class Endpoint;

class NetListener {
 public:
    virtual ~NetListener() { }

    virtual const Endpoint & getEndpoint() const = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual bool is_stopped() const = 0;
};  // class NetListener

#endif  // NETLISTENER_H
