#include "matrix.h"

Matrix::Matrix(size_t rows_, size_t cols_) : rows_(rows_), cols_(cols_) {
   if (!rows_ || !cols_)
       return;
   data_ = std::vector<std::vector<int>>(rows_, std::vector<int>(cols_, 0));
}

Matrix Matrix::operator+(const Matrix &m) const {
    if (rows_ != m.rows_ || cols_ != m.cols_)
        throw MatrixException("ADD: dimensions do not match.");
    Matrix sum(rows_, cols_);
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            sum.data_[i][j] = data_[i][j] + m.data_[i][j];
    return sum;
}

Matrix &Matrix::operator+=(const Matrix &m) {
    return *this = *this + m;
}

Matrix Matrix::operator*(const Matrix &m) const {
    if (cols_ != m.rows_)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix mul(rows_, m.cols_);
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < m.cols_; j++)
            for (size_t k = 0; k < cols_; k++)
                mul.data_[i][j] += data_[i][k] * m.data_[k][j];
    return mul;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    return *this = *this * m;
}

size_t Matrix::get(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_)
        throw MatrixException("ACCESS: bad index.");
    return data_[i][j];
}

std::istream &operator>>(std::istream &fin, Matrix &matrix) {
    size_t rows, cols, value;
    if (!(fin >> rows) || !(fin >> cols))
       throw MatrixException("LOAD: invalid file format.");
    matrix = Matrix(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
           if (!(fin >> value))
               throw MatrixException("LOAD: invalid file format.");
           else
                matrix.data_[i][j] = value;
        }
    }
    return fin;
}

std::ostream &operator<<(std::ostream &fout, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.rows_; i++) {
        for (size_t j = 0; j < matrix.cols_; j++)
            fout << matrix.data_[i][j] << ' ';
        fout << '\n';
    }
    return fout;
}

const char *MatrixException::get() const {
    return message;
}