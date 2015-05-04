#ifndef DATETIME_H
#define DATETIME_H

#include <chrono>
#include <string>
#include <ostream>

class Datetime {
 public:
    Datetime();

    Datetime(const Datetime &) noexcept = default;

    Datetime & operator=(const Datetime &) noexcept = default;

    ~Datetime() = default;

    friend bool operator==(const Datetime &, const Datetime &) noexcept;

    std::string toString() const;

    void toString(std::string &) const;

 private:
    using clock_t = std::chrono::system_clock;
    clock_t::time_point time_point_;
};  // class Datetime

inline bool operator==(const Datetime &lhs, const Datetime &rhs) noexcept {
    return lhs.time_point_ == rhs.time_point_;
}

inline bool operator!=(const Datetime &lhs, const Datetime &rhs) noexcept {
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream &stream, const Datetime &datetime) {
    return stream << datetime.toString();
}

#endif  // DATETIME_H
