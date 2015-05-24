//
// Created by Pavel Filonov on 24.05.15.
//

#include "CmdOptions.h"

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include <getopt.h>

CmdOptions parse_args(int argc, char* argv[]) {
    CmdOptions options;

    opterr = 0;
    int c;
    while ((c = getopt(argc, argv, "hvc:")) != -1) {
        switch (c) {
            case 'h':
                options.show_help = true;
                break;
            case 'v':
                options.show_version = true;
                break;
            case 'c':
                options.config = optarg;
                break;
            case '?':
                if (optopt == 'c') {
                    throw std::invalid_argument{"options 'c' requires an argument"};
                } else if (isprint(optopt)) {
                    std::stringstream ss;
                    ss << "Unknown option '" << optopt << "'";
                    throw std::invalid_argument{ss.str()};
                } else {
                    throw std::invalid_argument{"Error while parsing program options"};
                }
            default:
                throw std::logic_error{"getopt error"};
        }
    }
    return options;
}
