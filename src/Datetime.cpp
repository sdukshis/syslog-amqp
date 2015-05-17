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
    // FIXME: gcc-4.9 still doesn't support std::put_time
    size_t format_size = sizeof("YYYY-MM-DDTHH:SS:MM+HH:MM");
    char str[format_size + 1];
    std::strftime(str, format_size, "%FT%T%z", std::localtime(&time_point));
    // ss << std::put_time(std::localtime(&time_point), "%FT%T%z");
    return str;
}

void Datetime::toString(std::string &s) const {
    s = toString();
}
