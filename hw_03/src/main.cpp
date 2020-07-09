#include "HuffmnaAchiever.h"
#include "CLI.h"
#include <iostream>
#include <exception>

using std::cin;
using std::cout;

void printStatistics(int32_t size1, int32_t size2, int32_t size3, int32_t size4) {
    cout << size1 << '\n' << size2 << '\n' << (!size3 ? 0 : size4) << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(0);
    CliArguments args;
    huffman::HuffmanAchiever huffman;
    try {
        args = parseArguments(argc, argv);
    } catch (std::runtime_error &ex) {
        cout << ex.what() << '\n';
        return 1;
    }
    statistics stcs;
    try {
        std::ifstream ifs(args.infile.c_str());
        std::ofstream ofs(args.outfile.c_str());
        if (args.act == CODE) {
            huffman.compress(ifs, ofs, stcs);
            printStatistics(stcs.srcsz, stcs.compsz, stcs.srcsz, stcs.EXTRADATA);
        } else if (args.act == DECODE) {
            huffman.decompress(ifs, ofs, stcs);
            printStatistics(stcs.decompsz, stcs.compsz, stcs.compsz, stcs.EXTRADATA);
        }
    } catch (const std::exception &ex) {
        cout << ex.what() << '\n';
        return 1;
    }
    return 0;
}