#ifndef HW_03_CLI_H
#define HW_03_CLI_H

#include "HuffmnaAchiever.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include <string_view>

enum acts {
    CODE, DECODE
};

class CliArguments {
public:
    int act;
    std::string infile, outfile;
};

CliArguments parseArguments(int args, char *argv[]);

#endif
