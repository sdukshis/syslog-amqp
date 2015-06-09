#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include "NetListener.h"

#include <system_error>

#include "asio-inc.h"

#include "Endpoint.h"
#include "DataObservable.h"

class UDPListener: public NetListener, public DataObservable {
 public:
    UDPListener() = delete;

    UDPListener(const Endpoint &, asio::io_service &);

    UDPListener(const UDPListener &) = delete;

    UDPListener(UDPListener &&);

    ~UDPListener() override;

    UDPListener & operator=(const UDPListener &) = delete;

    UDPListener & operator=(UDPListener &&);

    const Endpoint & getEndpoint() const override;

    void start() override;

    void stop() override;

    bool is_stopped() const override;
 
 private:
    void start_receive();

    void on_data_received(const std::error_code &, std::size_t bytes_received);

    Endpoint endpoint_;
    asio::ip::udp::endpoint remote_endpoint_;
    asio::ip::udp::socket socket_;
    bool stopped_ = true;
    std::array<char, 1024> recv_buffer_;
};  // class UDPListener

#endif  // UDPLISTENER_H
