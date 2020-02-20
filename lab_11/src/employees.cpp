#include <iostream>
#include <cassert>
#include "../include/bin_manip.h"
#include "../include/employees.h"

// =================================Employee===========================================
std::istream &operator>>(std::istream &is, Employee &employee) {
    return employee.readText(is);
}

std::ostream &operator<<(std::ostream &os, const Employee &employee) {
    return employee.printText(os);
}

std::ifstream &operator>>(std::ifstream &is, Employee &employee) {
    return employee.readBinary(is);
}

std::ofstream &operator<<(std::ofstream &os, const Employee &employee) {
    return employee.printBinary(os);
}

// ==================================Developer=============================================
std::istream &Developer::readText(std::istream &is) {
    return is >> _name >> _base_salary >> _has_bonus;
}

std::ostream &Developer::printText(std::ostream &os) const {
    os << "Developer" << '\n';
    os << "Name: " << _name << '\n';
    os << "Base Salary: " << _base_salary << '\n';
    return os << "Has bonus: " << (_has_bonus ? '+' : '-') << '\n';
}

std::ifstream &Developer::readBinary(std::ifstream &is) {
    is >> read_str(_name) >> read_le_int32(_base_salary) >> read_bool(_has_bonus);
    return is;
}

std::ofstream &Developer::printBinary(std::ofstream &os) const {
    os << write_le_int32(1) << write_str(_name) << write_le_int32(_base_salary) << write_bool(_has_bonus);
    return os;
}
// =============================================SalesManager=========================================
std::istream &SalesManager::readText(std::istream &is) {
    return is >> _name >> _base_salary >> _sold_nm >> _price;
}

std::ostream &SalesManager::printText(std::ostream &os) const {
    os << "Sales Manager" << '\n';
    os << "Name: " << _name << '\n';
    os << "Base Salary: " << _base_salary << '\n';
    os << "Sold items: " << _sold_nm << '\n';
    return os << "Item price: " << _price << '\n';
}

std::ifstream &SalesManager::readBinary(std::ifstream &is) {
    is >> read_str(_name) >> read_le_int32(_base_salary) >> read_le_int32(_sold_nm) >> read_le_int32(_price);
    return is;
}

std::ofstream &SalesManager::printBinary(std::ofstream &os) const {
    os << write_le_int32(2) << write_str(_name) << write_le_int32(_base_salary) << write_le_int32(_sold_nm)
       << write_le_int32(_price);
    return os;
}

// =====================================EmployeesArray=============================================

void EmployeesArray::add(Employee *employee) {
    _employees.push_back(employee);
    ++_size;
}

int32_t EmployeesArray::total_salary() const {
    int32_t salary_sum = 0;
    for (int i = 0; i < _size; ++i)
        salary_sum += _employees[i]->salary();
    return salary_sum;
}

std::ostream &EmployeesArray::printText(std::ostream &os) const {
    for (int i = 0; i < _size; ++i) {
        assert(_employees[i] != nullptr);
        os << i + 1 << ". " << (*_employees[i]);
    }
    os << "== Total salary: " << total_salary() << '\n' << '\n';
    return os;
}

std::ifstream &EmployeesArray::readBinary(std::ifstream &is) {
    int32_t _sizearray;
    is >> read_le_int32(_sizearray);
    for (int i = 0; i < _sizearray; ++i) {
        int32_t type;
        is >> read_le_int32(type);
        Employee *cur_employee;
        if (type == DEVELOPER)
            cur_employee = new Developer();
        if (type == SALES_MANAGER)
            cur_employee = new SalesManager();
        is >> (*cur_employee);
        add(cur_employee);
    }
    return is;
}

std::ofstream &EmployeesArray::printBinary(std::ofstream &os) const {
    os << write_le_int32(_size);
    for (int i = 0; i < _size; ++i)
        os << (*_employees[i]);
    return os;
}

std::ostream &operator<<(std::ostream &os, const EmployeesArray &array) {
    return array.printText(os);
}

std::ifstream &operator>>(std::ifstream &is, EmployeesArray &array) {
    return array.readBinary(is);
}

std::ofstream &operator<<(std::ofstream &os, const EmployeesArray &array) {
    return array.printBinary(os);
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; ++i)
        delete _employees[i];
}