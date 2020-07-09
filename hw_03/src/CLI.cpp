#include <CLI.h>

CliArguments parseArguments(int argc, char *argv[]) {
    CliArguments args;
    for (int i = 1; i < argc; i++) {
        std::string_view arg = argv[i];
        if (arg == "-c")
            args.act = CODE;
        else if (arg == "-u")
            args.act = DECODE;
        else if (arg == "-f" || arg == "--file") {
            if (i + 1 == argc)
                throw std::runtime_error("Error opening input file.");
            args.infile = argv[++i];
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 == argc)
                throw std::runtime_error("Error opening output file.");
            args.outfile = argv[++i];
        } else
            throw std::runtime_error("Invalid argument: " + std::string(argv[i]));
    }
    return args;
}