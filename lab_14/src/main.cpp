#include <iostream>
#include <fstream>
#include <string>

#include "matrix.h"

const int NUMBER_REGS = 10;

void load(Matrix reg[]) {
    std::string id, name;
    std::cin >> id >> name;
    std::ifstream fin(name);
    if (!fin) {
        std::cout <<"LOAD: unable to open file.";
        return;
    }
    try {
        fin >> reg[id[1] - '0'];
    } catch (MatrixException &ex) {
        std::cout << "LOAD: invalid file format.";
    }
    fin.close();
}

void print(Matrix reg[]) {
    std::string id;
    std::cin >> id;
    std::cout << reg[id[1] - '0'];
}

void add(Matrix reg[]) {
    std::string id1, id2;
    std::cin >> id1 >> id2;
    try {
        reg[id1[1] - '0'] += reg[id2[1] - '0'];
    } catch (MatrixException &ex) {
        std::cout << ex.get() << '\n';
    }
}

void mul(Matrix reg[]) {
    std::string id1, id2;
    std::cin >> id1 >> id2;
    try {
        reg[id1[1] - '0'] *= reg[id2[1] - '0'];
    } catch (MatrixException &ex) {
        std::cout << ex.get() << '\n';
    }
}

void elem(Matrix reg[]) {
    std::string id;
    int row, col;
    std::cin >> id >> row >> col;
    try {
        int elem = reg[id[1] - '0'].get(row, col);
        std::cout << elem << '\n';
    } catch (MatrixException &ex) {
        std::cout << ex.get() << '\n';
    }
}

int main() {
    Matrix reg[NUMBER_REGS];
    std::string command;
    while (std::cin >> command) {
        try {
            if (command == "exit")
                exit(0);
            else if (command == "load")
                load(reg);
            else if (command == "print")
                print(reg);
            else if (command == "add")
                add(reg);
            else if (command == "mul")
                mul(reg);
            else if (command == "elem")
                elem(reg);
        } catch(std::bad_alloc) {
            std::cout <<"Unable to allocate memory.";
        }
    }
    return 0;
}