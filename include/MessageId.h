#ifndef MESSAGEID_H
#define MESSAGEID_H

#include <string>
#include <ostream>
#include <array>

class MessageId {
 public:
    MessageId();

    MessageId(const MessageId &) noexcept = default;

    MessageId & operator=(const MessageId &) noexcept = default;

    ~MessageId() = default;

    friend bool operator==(const MessageId &, const MessageId &) noexcept;

    std::string toString() const;

    void toString(std::string &) const;

 private:
    std::array<unsigned char, 16> id_bytes_;
};  // class MessageId

inline bool operator==(const MessageId &lhs, const MessageId &rhs) noexcept {
    return lhs.id_bytes_ == rhs.id_bytes_;
}

inline bool operator!=(const MessageId &lhs, const MessageId &rhs) noexcept {
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream &stream, const MessageId &id) {
    return stream << id.toString();
}

#endif  // MESSAGEID_H
