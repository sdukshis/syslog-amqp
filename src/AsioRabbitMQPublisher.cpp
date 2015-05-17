#include "AsioRabbitMQPublisher.h"

#include <assert.h>

using namespace asio::ip;

namespace {
    AMQP::ExchangeType convert_exchange_type(AsioRabbitMQPublisher::ExchangeType type) {
        switch (type) {
            case RabbitMQPublisher::ExchangeType::Topic:
                return AMQP::ExchangeType::topic;
            case RabbitMQPublisher::ExchangeType::Fanout:
                return AMQP::ExchangeType::fanout;
            case RabbitMQPublisher::ExchangeType::Direct:
                return AMQP::ExchangeType::direct;
            default:
                throw std::invalid_argument("Unknown ExchangeType");
        }
    }
}

AsioRabbitMQPublisher::AsioRabbitMQPublisher(const Endpoint &server_endpoint, asio::io_service &io)
        : server_endpoint_{server_endpoint}, io_{io}, socket_{io_} {
    tcp::resolver resolver(io_);
    tcp::resolver::query query(server_endpoint_.getAddr(), std::to_string(server_endpoint_.getPort()));
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;

    std::error_code error = asio::error::host_not_found;
    while (error && endpoint_iterator != end) {
        socket_.close();
        socket_.connect(*endpoint_iterator++, error);
    }
    if (error)
        throw std::system_error(error);

    connection_.reset(new AMQP::Connection(this));
    doRead();
};

AsioRabbitMQPublisher::~AsioRabbitMQPublisher() {
    if (connection_) {
        connection_->close();
    }
}

void AsioRabbitMQPublisher::declareExchange(const std::string &name, ExchangeType type) {
    assert(channel_);
    channel_->declareExchange(name, convert_exchange_type(type));
}

void AsioRabbitMQPublisher::basicPublish(const std::string &exchange, const std::string &routing_key, const char *data,
                                         std::size_t length) {
    assert(channel_);
    channel_->publish(exchange, routing_key, data, length);
}

void AsioRabbitMQPublisher::onConnected(AMQP::Connection *connection) {
    assert(connection_.get() == connection);
    std::clog << "AsioRabbitMQPublisher::onConnected" << std::endl;
    channel_.reset(new AMQP::Channel(connection_.get()));
}

void AsioRabbitMQPublisher::onData(AMQP::Connection * /*connection*/, const char *data, std::size_t size) {
    // assert(connection_.get() == connection);
    std::clog << "AsioRabbitMQPublisher::onData: send " << size << " bytes\n";
    socket_.async_send(asio::buffer(data, size),
                       [size](std::error_code ec, std::size_t bytes_written) {
                           assert(!ec);
                           //FIXME: handle nonwritten bytes
                           assert(size == bytes_written);
                       });
}

void AsioRabbitMQPublisher::onError(AMQP::Connection *connection, const char *) {
    assert(connection_.get() == connection);
    // TODO: log error
}

void AsioRabbitMQPublisher::onClosed(AMQP::Connection *connection) {
    assert(connection_.get() == connection);
    socket_.close();
}

void AsioRabbitMQPublisher::doRead() {
    socket_.async_receive(asio::buffer(buffer_.data(), buffer_.size()),
                          [this](std::error_code ec, std::size_t bytes_read) {
                              std::clog << "AsioRabbitMQPublisher::doRead: receive " << bytes_read << " bytes\n";
                              assert(!ec);
                              //FIXME: handle nonparsed bytes
                              std::size_t bytes_parsed = connection_->parse(buffer_.data(), bytes_read);
                              assert(bytes_parsed == bytes_read);
                              doRead();
                          });
}