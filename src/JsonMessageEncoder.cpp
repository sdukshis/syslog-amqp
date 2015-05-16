#include "JsonMessageEncoder.h"

#include "Message.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

JsonMessageEncoder::JsonMessageEncoder() { }

JsonMessageEncoder::~JsonMessageEncoder() { }

void JsonMessageEncoder::encode(const Message &msg) {
    buffer_.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer_);

    writer.StartObject();
    writer.Key("recv_host");
    auto recv_host_str = msg.getRecvHost().toString();
    writer.String(recv_host_str.data(), recv_host_str.size());
    writer.Key("recv_time");
    auto recv_time_str = msg.getRecvTime().toString();
    writer.String(recv_time_str.data(), recv_time_str.size());
    writer.Key("raw");
    writer.String(msg.getRaw().data(), msg.getRaw().size());

    writer.Key("tags");
    writer.StartArray();
    msg.visitTags([&writer](const std::string &tag) {
        writer.String(tag.data(), tag.size());
    });
    writer.EndArray();


    writer.Key("headers");
    writer.StartObject();
    msg.visitHeaders([&writer](const std::string &key, const std::string &value) {
        writer.Key(key.data(), key.size());
        writer.String(value.data(), value.size());
    });
    writer.EndObject();

    writer.EndObject();
}

const char * JsonMessageEncoder::begin() const {
    return buffer_.GetString();
}

const char * JsonMessageEncoder::end() const {
    return begin() + buffer_.GetSize();
}
