//
// Created by Pavel Filonov on 23.05.15.
//

#ifndef SYSLOG_AMQP_INIPARSER_H
#define SYSLOG_AMQP_INIPARSER_H

#include <string>
#include <istream>
#include <stdexcept>

class SyntaxError: public std::invalid_argument {
public:
    using std::invalid_argument::invalid_argument;
};

class IniParser {
public:
    class Handler;

    IniParser() = default;

    IniParser(const IniParser &) = delete;

    IniParser & operator=(const IniParser &) = delete;

    void parse(std::istream &, Handler *);

private:
    enum class State {
        Expect_section_begin_or_key,
        Expect_section_name,
        Expect_section_end,
        Expect_assign,
        Expect_value,
        Expect_newline_or_eof,
        Finish,
    };
    friend std::ostream & operator<<(std::ostream &, IniParser::State);

    State state_ = State::Expect_section_begin_or_key;
};

class IniParser::Handler {
public:
    virtual ~Handler() { }

    virtual void onSection(const std::string &name) = 0;

    virtual void onKey(const std::string &key) = 0;

    virtual void onValue(const std::string &value) = 0;
};

#endif //SYSLOG_AMQP_INIPARSER_H
