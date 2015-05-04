#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <map>
#include <set>

#include "Datetime.h"
#include "MessageId.h"
#include "Endpoint.h"

class Message {
 public:
    template<class T, class U>
    Message(T &&recv_host, U &&msg);

    Message(const Message &) = default;

    Message(Message &&) = default;

    Message & operator=(const Message &) = default;

    Message & operator=(Message &&) = default;

    friend bool operator==(const Message &, const Message &) noexcept;

    const MessageId & getId() const;

    const Datetime & getRecvTime() const;

    const Endpoint & getRecvHost() const;

    const std::string & getRaw() const;

    std::string toString() const;

    void toString(std::string &) const;

    void addTag(const std::string &);

    bool delTag(const std::string &);

    using tag_visitor_t = std::function<void(const std::string &)>;

    void visitTags(tag_visitor_t) const;

    void setHeader(const std::string &key, const std::string &val);

    bool delHeader(const std::string &key);

    using header_visitor_t = std::function<void(const std::string &, const std::string &)>;

    void visitHeaders(header_visitor_t) const;

 private:
    friend class MessageEncoder;

    MessageId id_;
    Datetime recv_time_;
    Endpoint recv_host_;
    std::string msg_;
    std::set<std::string> tags_;
    std::map<std::string, std::string> headers_;
};  // class Message

template<class T, class U>
Message::Message(T &&recv_host, U &&msg)
    : recv_host_(std::forward<T>(recv_host))
    , msg_(std::forward<U>(msg)) { }

inline bool operator==(const Message &lhs, const Message &rhs) noexcept {
    return lhs.id_ == rhs.id_;
}

inline bool operator!=(const Message &lhs, const Message &rhs) noexcept {
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream &stream, const Message &msg) {
    return stream << msg.toString();
}

inline const MessageId & Message::getId() const {
    return id_;
}

inline const Datetime & Message::getRecvTime() const {
    return recv_time_;
}

inline const Endpoint & Message::getRecvHost() const {
    return recv_host_;
}

inline const std::string & Message::getRaw() const {
    return msg_;
}

#endif  // MESSAGE_H