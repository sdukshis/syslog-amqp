#ifndef DATETIME_H
#define DATETIME_H

#include <chrono>
#include <string>
#include <ostream>

class Datetime {
 public:
    Datetime(std::chrono::seconds = std::chrono::seconds{0},
             std::chrono::minutes = std::chrono::minutes{0});

    Datetime(const Datetime &) noexcept = default;

    Datetime & operator=(const Datetime &) noexcept = default;

    ~Datetime() = default;

    friend bool operator==(const Datetime &, const Datetime &) noexcept;

    std::string toString() const;

    void toString(std::string &) const;

 private:
    std::chrono::seconds epoch_time_t_;
    std::chrono::minutes tz_offset_;
};  // class Datetime

inline bool operator==(const Datetime &lhs, const Datetime &rhs) noexcept {
    return lhs.epoch_time_t_ == rhs.epoch_time_t_ &&
           lhs.tz_offset_ == rhs.tz_offset_;
}

inline bool operator!=(const Datetime &lhs, const Datetime &rhs) noexcept {
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream &stream, const Datetime &datetime) {
    return stream << datetime.toString();
}

#endif  // DATETIME_H
