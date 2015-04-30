#include "Message.h"

std::string Message::toString() const {
    return "{}";
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

void Message::setHeader(const std::string &key, const std::string &val) {
    headers_.emplace(key, val);
}

bool Message::delHeader(const std::string &key) {
    return headers_.erase(key);
}
