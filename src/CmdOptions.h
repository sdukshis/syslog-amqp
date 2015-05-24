//
// Created by Pavel Filonov on 24.05.15.
//

#ifndef SYSLOG_AMQP_CMDOPTIONS_H
#define SYSLOG_AMQP_CMDOPTIONS_H

#include <string>

struct CmdOptions {
    CmdOptions()
            : show_help{false}
            , show_version{false}
    { }
    bool show_help;
    bool show_version;
    std::string config;
};

CmdOptions parse_args(int argc, char* argv[]);

#endif //SYSLOG_AMQP_CMDOPTIONS_H
