#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <cstring>
#include <fstream>
#include <vector>


enum employees {
    DEVELOPER = 1, SALES_MANAGER = 2
};

// =================================Employee===========================================
class Employee {
public:
    Employee() = default;

    virtual int salary() const = 0;

    virtual std::istream &readText(std::istream &is) = 0;

    virtual std::ostream &printText(std::ostream &os) const = 0;

    virtual std::ifstream &readBinary(std::ifstream &is) = 0;

    virtual std::ofstream &printBinary(std::ofstream &os) const = 0;

    virtual ~Employee() = default;
};

std::istream &operator>>(std::istream &is, Employee &employee);

std::ostream &operator<<(std::ostream &os, const Employee &employee);

std::ifstream &operator>>(std::ifstream &is, Employee &employee);

std::ofstream &operator<<(std::ofstream &os, const Employee &employee);

// ==================================Developer=============================================
class Developer : public Employee {
public:
    Developer() = default;

    int salary() const override {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }

    std::istream &readText(std::istream &is) override;

    std::ostream &printText(std::ostream &os) const override;

    std::ifstream &readBinary(std::ifstream &is) override;

    std::ofstream &printBinary(std::ofstream &os) const override;

    ~Developer() override = default;

private:
    std::string _name;
    int32_t _base_salary;
    bool _has_bonus;
};

// =================================SalesManager================================================
class SalesManager : public Employee {
public:
    SalesManager() = default;

    int salary() const override {
        return _base_salary + _sold_nm * _price * 0.01;
    }

    std::istream &readText(std::istream &is) override;

    std::ostream &printText(std::ostream &os) const override;

    std::ifstream &readBinary(std::ifstream &is) override;

    std::ofstream &printBinary(std::ofstream &os) const override;

    ~SalesManager() override = default;

private:
    std::string _name;
    int32_t _base_salary;
    int32_t _sold_nm, _price;
};

// =====================================EmployeesArray=============================================
class EmployeesArray {
public:
    EmployeesArray() = default;

    void add(Employee *employee);

    int32_t total_salary() const;

    std::ostream &printText(std::ostream &os) const;

    std::ifstream &readBinary(std::ifstream &is);

    std::ofstream &printBinary(std::ofstream &os) const;

    ~EmployeesArray();

private:
    std::vector<Employee *> _employees;
    int32_t _size = 0;
};

std::ostream &operator<<(std::ostream &os, const EmployeesArray &arr);

std::ifstream &operator>>(std::ifstream &is, EmployeesArray &arr);

std::ofstream &operator<<(std::ofstream &os, const EmployeesArray &arr);

#endif
