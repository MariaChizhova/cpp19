#include <iostream>
#include <fstream>
#include <cassert>
#include "../include/bin_manip.h"
#include "../include/employees.h"

int main() {
    EmployeesArray array;
    std::string instruction;
    while (std::cin >> instruction) {
        if (instruction == "exit") return 0;
        if (instruction == "load") {
            std::string filename;
            std::cin >> filename;
            std::ifstream fin(filename, std::ios::binary);
            fin >> array;
            fin.close();
        } else if (instruction == "save") {
            std::string filename;
            std::cin >> filename;
            std::ofstream fout(filename, std::ofstream::binary);
            fout << array;
            fout.close();
        } else if (instruction == "add") {
            int32_t type;
            std::cin >> type;
            Employee *employee = nullptr;
            if (type == DEVELOPER)
                employee = new Developer;
            else if (type == SALES_MANAGER)
                employee = new SalesManager;
            std::cin >> (*employee);
            assert(employee != nullptr);
            array.add(employee);
        } else if (instruction == "list")
            std::cout << array;
        else
            std::cout << "Unknown command" << '\n';
    }
    return 0;
}
