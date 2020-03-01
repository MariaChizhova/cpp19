#ifndef LAB_14_MATRIX_H
#define LAB_14_MATRIX_H

#include <iostream>
#include <cstddef>
#include <vector>

class Matrix {
public:
    Matrix(size_t rows = 0, size_t cols = 0);

    Matrix operator+(const Matrix &m) const;

    Matrix &operator+=(const Matrix &m);

    Matrix operator*(const Matrix &m) const;

    Matrix &operator*=(const Matrix &m);

    size_t get(size_t i, size_t j) const;

    friend std::istream &operator>>(std::istream &fin, Matrix &matrix);

    friend std::ostream &operator<<(std::ostream &fout, const Matrix &matrix);

    ~Matrix() = default;

private:
    std::vector<std::vector<int>> data_;
    size_t rows_, cols_;
};

class MatrixException : public std::exception {
public:
    MatrixException(const char *message = "None") : message(message) {};

    const char *get() const;

private:
    const char *message;
};

#endif

