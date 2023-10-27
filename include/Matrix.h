#pragma once

#include <stdexcept>
#include <iostream>

class Matrix {
protected:
    int **_m;
    /**
     * @brief size of the matrix
     * first = row
     * second = col
     */
    std::pair<int, int> _size;

public:
    explicit Matrix(std::pair<int, int> size);

    explicit Matrix(int size);

    Matrix(const Matrix& matrix);

    /**
     * @brief utils function to elevate a matrix to a power
     * @param matrix matrix to power
     * @param value power value
     * @return matrix powered
     */
    static Matrix power(const Matrix& matrix, int value);

    ~Matrix();

    void add(int row, int col, int value);

    [[nodiscard]] std::pair<int, int> size() const;

    int operator()(int row, int col) const;

    void operator()(int row, int col, int value);

    void operator+=(const Matrix& matrix);

    void operator-=(const Matrix& matrix);

    /**
     * @bug not fully implemented with matrix that are not square
     * @param matrix
     */
    void operator*=(const Matrix& matrix);

    void operator*=(int value);

    void operator^=(int value) const;

    Matrix& operator=(const Matrix& matrix);

    Matrix operator+(const Matrix& matrix) const;

    Matrix operator-(const Matrix& matrix) const;

    Matrix operator*(const Matrix& matrix) const;

    Matrix operator*(int value) const;

    Matrix operator^(int value) const;

    bool operator==(const Matrix& matrix) const;

    bool operator!=(const Matrix& matrix) const;

    void print();
};