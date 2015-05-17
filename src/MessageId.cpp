#include "MessageId.h"

#include <random>
#include <limits>
#include <sstream>
#include <ios>
#include <assert.h>
#include <iomanip>

/*
 * Generates id with 16 random octets according to UUID4
 */
MessageId::MessageId() {
    std::random_device rd;
    std::uniform_int_distribution<container::value_type> dist(std::numeric_limits<container::value_type>::min(),
                                                              std::numeric_limits<container::value_type>::max());
    for (auto &octet : id_bytes_) {
        octet = dist(rd);
    }
}

/*
 * Converts MessageId to string in UUID format (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)
 */
std::string MessageId::toString() const {
    std::stringstream ss;

    auto fmt = [&ss](unsigned char octet) {
        ss << std::hex
           << std::setw(2)
           << std::setfill('0')
           << std::noshowbase
           << (int)octet;
    };

    auto octet = std::begin(id_bytes_);
    fmt(*octet++); fmt(*octet++); fmt(*octet++); fmt(*octet++);
    ss << '-';
    fmt(*octet++); fmt(*octet++);
    ss << '-';
    fmt(*octet++); fmt(*octet++);
    ss << '-';
    fmt(*octet++); fmt(*octet++);
    ss << '-';
    fmt(*octet++); fmt(*octet++); fmt(*octet++); fmt(*octet++); fmt(*octet++); fmt(*octet++);

    assert(octet == std::end(id_bytes_));
    return ss.str();
}

void MessageId::toString(std::string &s) const {
    s = toString();
}
