#include "Datetime.h"

Datetime::Datetime(std::chrono::seconds epoch_time_t,
                   std::chrono::minutes tz_offset)
    : epoch_time_t_{epoch_time_t}
    , tz_offset_{tz_offset} { }

std::string Datetime::toString() const {
    return "1970-01-01T00:00:00Z";
}

void Datetime::toString(std::string &s) const {
    s = toString();
}
