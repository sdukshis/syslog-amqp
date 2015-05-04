#include "Datetime.h"

#include <ctime>
#include <iomanip>
#include <sstream>

/*
 * By default set Datetime time_point to current time
 */

Datetime::Datetime()
    : time_point_{clock_t::now()} { }

/*
 * Convert Datetime to ISO8601 format YYYY-MM-DDTHH:MM:SS+HH:MM
 */
std::string Datetime::toString() const {
    std::time_t time_point = clock_t::to_time_t(time_point_);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_point), "%FT%T%z");
    return ss.str();
}

void Datetime::toString(std::string &s) const {
    s = toString();
}
