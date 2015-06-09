#include "gtest-inc.h"

#include "../src/Datetime.h"
#include <ctime>
#include <iomanip>
#include <sstream>

std::string time_t_to_str(const time_t t) {
    std::stringstream ss;
    // FIXME: gcc-4.9 still doesn't support std::put_time
    size_t format_size = sizeof("YYYY-MM-DDTHH:SS:MM+HH:MM");
    char str[format_size + 1];
    std::strftime(str, format_size, "%FT%T%z", std::localtime(&t));

    // ss << std::put_time(std::localtime(&t), "%FT%T%z");
    return str;
}

TEST(Datetime, defaultCtor) {
    Datetime time;

    ASSERT_EQ(time_t_to_str(std::time(0)), time.toString());
}

TEST(Datetime, copyCtor) {
    Datetime time1;

    Datetime time2{time1};

    ASSERT_EQ(time1, time2);
}

TEST(Datetime, copyAssign) {
    Datetime time1, time2;

    time2 = time1;

    ASSERT_EQ(time1, time2);
}

TEST(Datetime, toString) {
    Datetime time1;
    std::string str;
    time1.toString(str);

    ASSERT_EQ(str, time1.toString());
}

TEST(Datetime, equal) {
    ASSERT_EQ((Datetime{}), (Datetime{}));
}
