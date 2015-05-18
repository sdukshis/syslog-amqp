//
// Created by Pavel Filonov on 17.05.15.
//

#include "AsioRabbitMQPublisherFactory.h"
#include "AsioRabbitMQPublisher.h"

using namespace asio::ip;

AsioRabbitMQPublisherFactory::AsioRabbitMQPublisherFactory(const Endpoint &server_endpoint, asio::io_service &io)
        : server_endpoint_{server_endpoint}, io_{io}, socket_{io_} {
    tcp::resolver resolver(io_);
    tcp::resolver::query query(server_endpoint_.getAddr(), std::to_string(server_endpoint_.getPort()));
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;

    asio::error_code error = asio::error::host_not_found;
    while (error && endpoint_iterator != end) {
        socket_.close();
        socket_.connect(*endpoint_iterator++, error);
    }
    if (error)
        throw std::system_error(error);

    connection_.reset(new AMQP::Connection(this));
    doRead();
}


AsioRabbitMQPublisherFactory::~AsioRabbitMQPublisherFactory() {
    stop();
}

RabbitMQPublisher *AsioRabbitMQPublisherFactory::createRabbitMQPublisher() {
    std::clog << "AsioRabbitMQPublisherFactory::createRabbitMQPublisher" << std::endl;
    async_mode_ = false;
    publishers_.emplace_back(new AsioRabbitMQPublisher{new AMQP::Channel{connection_.get()}});
    async_mode_ = true;
    doRead();
    return publishers_.back().get();
}

void AsioRabbitMQPublisherFactory::onData(AMQP::Connection *, const char *buffer, size_t size) {
    std::clog << "AsioRabbitMQPublisherFactory::onData: send " << size << " bytes\n";
    if (async_mode_) {
        socket_.async_write_some(asio::buffer(buffer, size),
                                 [size](asio::error_code ec, size_t bytes_written) {
                                     assert(!ec);
                                     assert (bytes_written == size);
                                 });
    } else {
        asio::error_code ec;
        socket_.write_some(asio::buffer(buffer, size), ec);
        assert(!ec);
    }
}

void AsioRabbitMQPublisherFactory::onClosed(AMQP::Connection *) {
    socket_.close();
}

void AsioRabbitMQPublisherFactory::onConnected(AMQP::Connection *) {
    async_mode_ = true;
}

void AsioRabbitMQPublisherFactory::onError(AMQP::Connection *, const char *message) {
    std::clog << "AMQP Error: " << message << std::endl;
    socket_.close();
}


void AsioRabbitMQPublisherFactory::doRead() {
    if (async_mode_) {
        socket_.async_read_some(asio::buffer(buffer_.data(), buffer_.size()),
                                [this](asio::error_code ec, size_t bytes_read) {
                                    assert(!ec);
                                    size_t bytes_parsed = connection_->parse(buffer_.data(), bytes_read);
                                    assert(bytes_parsed == bytes_read);
                                    doRead();
                                });
    }

    while (!async_mode_) {
        asio::error_code ec;
        size_t bytes_read = socket_.read_some(asio::buffer(buffer_.data(), buffer_.size()), ec);
        std::clog << "AsioRabbitMQPublisherFactory::doRead: read " << bytes_read << " bytes, ec:" << ec.message() <<
        std::endl;
        assert(!ec);
        size_t bytes_parsed = connection_->parse(buffer_.data(), bytes_read);
        assert(bytes_parsed == bytes_read);
    }
}

void AsioRabbitMQPublisherFactory::stop() {
    for (auto &publisher : publishers_) {
        publisher->close();
    }
    connection_->close();
    socket_.close();
}
