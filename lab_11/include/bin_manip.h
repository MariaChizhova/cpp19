#ifndef BIN_MANIP_H
#define BIN_MANIP_H

#include <fstream>
#include <cstring>


// ==========================================================================================
class read_bool {
public:
    read_bool(bool &value_) : value(value_) {}

    std::istream &operator()(std::istream &is) const;

private:
    bool &value;
};

std::istream &operator>>(std::istream &is, read_bool r);

class write_bool {
public:
    write_bool(const bool value_) : value(value_) {}

    std::ostream &operator()(std::ostream &os) const;

private:
    bool value;
};

std::ostream &operator<<(std::ostream &os, write_bool w);

// =============================================================================================
class read_le_int32 {
public:
    read_le_int32(int32_t &value_) : value(value_) {}

    std::istream &operator()(std::istream &is) const;

private:
    int32_t &value;
};

std::istream &operator>>(std::istream &is, read_le_int32 r);

class write_le_int32 {
public:
    write_le_int32(const int32_t value_) : value(value_) {}

    std::ostream &operator()(std::ostream &os) const;

private:
    int32_t value;
};

std::ostream &operator<<(std::ostream &os, write_le_int32 w);

// ===================================================================================
class read_str {
public:
    read_str(std::string &value_) : value(value_) {}

    std::istream &operator()(std::istream &is) const;

private:
    std::string &value;
};

std::istream &operator>>(std::istream &is, read_str r);

class write_str {
public:
    write_str(const std::string &value_) : value(value_) {}

    std::ostream &operator()(std::ostream &os) const;

private:
    std::string value;
};

std::ostream &operator<<(std::ostream &os, write_str w);

#endif