#include "Message.h"

#include "JsonMessageEncoder.h"

std::string Message::toString() const {
    JsonMessageEncoder encoder;

    encoder.encode(*this);

    return std::string(encoder.begin(), encoder.end());
}

void Message::toString(std::string &s) const {
    s = toString();
}

void Message::addTag(const std::string &tag) {
    tags_.emplace(tag);
}

bool Message::delTag(const std::string &tag) {
    return tags_.erase(tag);
}

void Message::visitTags(tag_visitor_t visitor) const {
    for (const auto &tag : tags_) {
        visitor(tag);
    }
}

void Message::setHeader(const std::string &key, const std::string &val) {
    headers_.emplace(key, val);
}

bool Message::delHeader(const std::string &key) {
    return headers_.erase(key);
}

void Message::visitHeaders(header_visitor_t visitor) const {
    for (const auto &header : headers_) {
        visitor(header.first, header.second);
    }
}