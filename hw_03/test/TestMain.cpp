#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "HuffmnaAchiever.h"

using std::stringstream;
using namespace huffman;

TEST_CASE ("simple test 1") {
    stringstream input, comp, decomp;
    input << "I am very tired";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("simple test 2") {
    stringstream input, comp, decomp;
    input << "Help me!!!!!!";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
            CHECK(input.str() == decomp.str());
}

TEST_CASE ("simple test 3") {
    stringstream input, comp, decomp;
    input << "a12345fgrbfu%#@&^*&($^#(*&^\n(&!$gFHSDBFVHSBuyvfueyr7324274t7";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("simple test 4") {
    stringstream input, comp, decomp;
    input << "I want to sleep\n balalalalbla blablbalablbalab";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}


TEST_CASE ("simple not simple test 5") {
    stringstream input, comp, decomp;
    input << "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
             "Aenean scelerisque rutrum vestibulum. Donec mollis lectus eget vehicula cursus."
             " In massa nisi, commodo et auctor in, iaculis ut ex."
             " Nulla sed tortor commodo, ultricies ipsum ut, accumsan lectus. Praesent id placerat purus."
             " Quisque condimentum, ligula quis tincidunt rhoncus, nibh risus varius nunc,"
             " sit amet faucibus nisl velit sagittis neque."
             " Aliquam vitae lorem pellentesque nulla elementum accumsan eu sed eros."
             " Aenean facilisis rhoncus augue eget euismod. Praesent nec purus diam. "
             "Ut consectetur, nunc at auctor mattis, orci nunc facilisis metus, non volutpat odio nunc non augue. "
             "Donec eleifend justo arcu, in sollicitudin turpis vestibulum ac."
             " Fusce et magna finibus dui egestas convallis non vel quam.";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("one byte, letter") {
    stringstream input, comp, decomp;
    input << "R";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("one byte, symbol") {
    stringstream input, comp, decomp;
    input << "&";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("many identical characters") {
    int n = 5e6;
    stringstream input, comp, decomp;
    for (int i = 0; i < n; i++)
        input << "*";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("many characters") {
    int n = 5e6;
    stringstream input, comp, decomp;
    for (int i = 0; i < n; i++)
        input << "ABC";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

TEST_CASE ("empty file") {
    stringstream input, comp, decomp;
    input << "";
    statistics stcs;
    HuffmanAchiever huffman;
    huffman.compress(input, comp, stcs);
    huffman.decompress(comp, decomp, stcs);
    CHECK(input.str() == decomp.str());
}

int main(int argc, char *argv[]) {
    return doctest::Context(argc, argv).run();
}