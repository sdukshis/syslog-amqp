#include "Decoder.h"

#include <iterator>
#include <algorithm>

#include "Message.h"

Decoder::Decoder()
    : recv_host_{"", 0} { }

Decoder::Decoder(Decoder &&other)
    : recv_buffer_{other.recv_buffer_}
    , recv_host_{other.recv_host_}
    , tag_{other.tag_} { }

Decoder & Decoder::operator=(Decoder &&other) {
    recv_buffer_ = std::move(other.recv_buffer_);
    recv_host_ = std::move(other.recv_host_);
    tag_ = std::move(other.tag_);

    return *this;
}

void Decoder::onBegin(const Endpoint &recv_host,
                      const std::string &tag) {
    recv_host_ = recv_host;
    tag_ = tag;
    recv_buffer_.clear();
}

void Decoder::onData(const char *buffer, std::size_t length) {
    recv_buffer_.reserve(recv_buffer_.size() + length);
    std::copy_n(buffer, length, std::back_inserter(recv_buffer_));
    auto eol = recv_buffer_.find_first_of('\n');
    if (eol != std::string::npos) {
        Message message{recv_host_,
                        std::string{recv_buffer_.data(),
                                    eol}};
        if (!tag_.empty()) {
            message.addTag(tag_);
        }
        notifyObservers(message);
        std::copy(recv_buffer_.begin() + eol + 1, recv_buffer_.end(),
                  recv_buffer_.begin());
        recv_buffer_.resize(recv_buffer_.size() - eol - 1);
    }
}

void Decoder::onEnd() {
    Message message{recv_host_, recv_buffer_};
    if (!tag_.empty()) {
        message.addTag(tag_);
    }
    notifyObservers(message);
}