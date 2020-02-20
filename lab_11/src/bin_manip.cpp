#include <fstream>
#include "../include/bin_manip.h"

const int BYTE = 8;

std::istream &read_bool::operator()(std::istream &is) const {
    char c;
    is.get(c);
    value = c;
    return is;
}

std::istream &operator>>(std::istream &is, read_bool r) {
    return r(is);
}

std::ostream &write_bool::operator()(std::ostream &os) const {
    os.put((unsigned char)value);
    return os;
}

std::ostream &operator<<(std::ostream &os, write_bool w) {
    return w(os);
}

// =======================================================================================

std::istream &read_le_int32::operator()(std::istream &is) const {
    unsigned char c;
    value = 0;
    for (int i = 0; i < 4; ++i) {
        is >> c;
        value |= c << (BYTE * i);
    }
    return is;
}

std::istream &operator>>(std::istream &is, read_le_int32 r) {
    return r(is);
}

std::ostream &write_le_int32::operator()(std::ostream &os) const {
    for (size_t i = 0; i < 4; ++i)
        os << (unsigned char) (value >> BYTE * i);
    return os;
}

std::ostream &operator<<(std::ostream &os, write_le_int32 w) {
    return w(os);
}

// =========================================================================================
std::istream &read_str::operator()(std::istream &is) const {
    char c;
    is >> c;
    value = "";
    while (c) {
        value.push_back(c);
        is.get(c);
    }
    return is;
}

std::istream &operator>>(std::istream &is, read_str r) {
    return r(is);
}


std::ostream &write_str::operator()(std::ostream &os) const {
    for (int i = 0; i < value.size(); ++i)
        os << value[i];
    return os << '\0';
}

std::ostream &operator<<(std::ostream &os, write_str w) {
    return w(os);
}