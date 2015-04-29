#include "UDPListener.h"

#include <assert.h>
#include <iostream>

using namespace asio::ip;

UDPListener::UDPListener(const Endpoint &endpoint, asio::io_service &io)
    : endpoint_{endpoint} 
    , socket_{io, udp::endpoint(address::from_string(endpoint_.getAddr().c_str()),
                                endpoint_.getPort())} { }

UDPListener::UDPListener(UDPListener &&other)
    : endpoint_{std::move(other.endpoint_)}
    , socket_{std::move(other.socket_)}
    , stopped_{other.stopped_} { }

UDPListener::~UDPListener() {
    if (!is_stopped()) {
        stop();
    }
}

UDPListener & UDPListener::operator=(UDPListener &&other) {
    assert(this != std::addressof(other));
    if (!is_stopped()) {
        stop();
    }
    endpoint_ = std::move(other.endpoint_);
    socket_ = std::move(other.socket_);
    stopped_ = other.stopped_;

    return *this;
}

const Endpoint & UDPListener::getEndpoint() const {
    return endpoint_;
}

void UDPListener::start() {
    if (is_stopped()) {
        start_receive();
        stopped_ = false;
    }
}

void UDPListener::stop() {
    if (!is_stopped()) {
        socket_.close();
    }
}

bool UDPListener::is_stopped() const {
    return stopped_;
}

void UDPListener::start_receive() {
    socket_.async_receive_from(asio::buffer(recv_buffer_),
                               remote_endpoint_,
                [this] (const std::error_code &error,
                        std::size_t bytes_received) {
                    on_data_received(error, bytes_received);
                    if (!is_stopped()) {
                        start_receive();
                    }
                });    
}

void UDPListener::on_data_received(const std::error_code &error,
                                   std::size_t bytes_received) {
    if (!error || error == asio::error::message_size) {
        // handle data from recv_buffer_
        std::cout << "Data: " << recv_buffer_.data() << std::endl;
    } else {
        stop();
    }
}
