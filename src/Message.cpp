#include "Message.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string Message::toString() const {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key("recv_host");
    writer.String(recv_host_.data(), recv_host_.size());
    writer.Key("recv_time");
    auto recv_time_str = recv_time_.toString();
    writer.String(recv_time_str.data(), recv_time_str.size());
    writer.Key("raw");
    writer.String(msg_.data(), msg_.size());
    if (!tags_.empty()) {
        writer.Key("tags");
        writer.StartArray();
        for (const auto &tag : tags_) {
            writer.String(tag.data(), tag.size());
        }
        writer.EndArray();
    }
    if (!headers_.empty()) {
        writer.Key("headers");
        writer.StartObject();
        for (const auto &header : headers_) {
            writer.Key(header.first.data(), header.first.size());
            writer.String(header.second.data(), header.second.size());
        }
        writer.EndObject();
    }

    writer.EndObject();

    return buffer.GetString();
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
