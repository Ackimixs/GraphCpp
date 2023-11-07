#pragma once

#include "Utils.hpp"
#include "Logger.hpp"

#include <cstring>
#include <iostream>
#include <iomanip>

typedef struct {
    size_t row;
    size_t col;
} s;

namespace Matrix {

    template <typename T = int>
    class adjacentMatrix {
    protected:
        std::pair<T, T> *_m;

        size_t _size;

    public:

        adjacentMatrix(size_t size);

        adjacentMatrix(const std::vector<std::pair<T, T>>& vec);

        adjacentMatrix(const std::pair<T, T>* data);

        adjacentMatrix(const adjacentMatrix<T>& other);

        ~adjacentMatrix();

        size_t size() const;

        inline std::pair<T, T>& operator()(size_t row, size_t col);

        inline const std::pair<T, T>& operator()(size_t row, size_t col) const;

        inline void operator()(size_t row, size_t col, std::pair<T, T> value);

        virtual inline std::pair<T, T>& at(size_t row, size_t col);

        virtual inline const std::pair<T, T>& at(size_t row, size_t col) const;

        inline void set(size_t row, size_t col, const std::pair<T, T>& value);

        friend std::ostream& operator << (std::ostream& os, const adjacentMatrix<T>& matrix) {

            for(size_t i = 0; i < matrix.size().row; i++)
            {
                for(size_t j = 0; j < matrix.size().col; j++)
                {
                    os << std::setw(6) << matrix.at(i, j) << " ";
                }
                os << std::endl;
            }
            return os;
        };
    };

    /**
     * @brief Matrix of size MxN
     * @tparam R number of row
     * @tparam C number of col
     * @tparam T type of the matrix
     */
    template< typename T = int >
    class M {
    protected:
        T *_m;
        /**
         * @brief size of the matrix
         * first = row
         * second = col
         */
        s _size;

    public:
        M();

        M(s size);

        M(size_t row, size_t col);

        M(const M<T>& other);

        M(const std::vector<T>& vec);

        M(const T* data);

        M(const Matrix::adjacentMatrix<T>& adjMatrix);

        ~M();

        s size() const;

        static M power(const M& matrix, int value);

        static M identityMatrix(size_t size);

        inline T& operator()(size_t row, size_t col);
        inline const T& operator()(size_t row, size_t col) const;

        inline void operator()(size_t row, size_t col, T value);

        virtual inline T& at(size_t row, size_t col);

        virtual inline const T& at(size_t row, size_t col) const;

        inline void set(size_t row, size_t col, T value);

        M<T> operator*(const M<T> &other) const;

        M operator*(T v);

        M operator/(T v);

        M operator^(T v);

        inline M operator+(const M& other) const;
        inline M operator-(const M& other) const;


        void operator*=(const M<T> &other);

        void operator*=(T v);

        void operator/=(T v);

        void operator^=(T v);

        void operator+=(const M& other);
        void operator-=(const M& other);

        M& operator=(const M<T> &other);

        M& operator=(const T* data_array);
        M& operator=(const std::vector<T>& data_vec);

        M& operator=(const Matrix::adjacentMatrix<T>& adjMatrix);

        M& operator=(T v);
        void fill(T v);

        void zero();

        bool operator==(const M& other) const;
        bool operator==(M other);

        bool operator!=(const M& other) const;
        bool operator!=(M other);

        friend std::ostream& operator << (std::ostream& os, const M<T>& matrix) {

            for(size_t i = 0; i < matrix.size().row; i++)
            {
                for(size_t j = 0; j < matrix.size().col; j++)
                {
                    os << std::setw(6) << matrix.at(i, j) << " ";
                }
                os << std::endl;
            }
            return os;
        };
    };

}




template<typename T>
Matrix::M<T>::M() : _m(), _size(0) {}

template<typename T>
Matrix::M<T>::M(s size) : _size(size) {
    _m = new T[size.row * size.col];
    fill(0);
}

template<typename T>
Matrix::M<T>::M(size_t row, size_t col) : _size(s(row, col)) {
    _m = new T[row * col];
    fill(0);
}

template<typename T>
Matrix::M<T>::M(const Matrix::M<T>& other) : _size(other._size) {
    _m = new T[other.size().row * other.size().col];
    for (size_t i = 0; i < other.size().row * other.size().col; i++) {
        _m[i] = other._m[i];
    }
}

template<typename T>
s Matrix::M<T>::size() const {
    return _size;
}

template<typename T>
T &Matrix::M<T>::operator()(size_t row, size_t col) {
    return at(row, col);
}

template<typename T>
const T &Matrix::M<T>::operator()(size_t row, size_t col) const {
    return at(row, col);
}

template<typename T>
void Matrix::M<T>::operator()(size_t row, size_t col, T value) {
    return set(row, col, value);
}

template<typename T>
T &Matrix::M<T>::at(size_t row, size_t col) {
    if (row >= size().row || col >= size().col) {
        throw std::out_of_range("Matrix::M::at() -- index out of range !");
    }
    return _m[row * size().col + col];
}

template<typename T>
const T &Matrix::M<T>::at(size_t row, size_t col) const {
    if (row >= this->size().row || col >= this->size().col) {
        throw std::out_of_range("Matrix::M::at() -- index out of range !");
    }
    return _m[row * this->size().col + col];
}

template<typename T>
void Matrix::M<T>::set(size_t row, size_t col, T value) {
    _m[row * this->size().col + col] = value;
}

template<typename T>
Matrix::M <T> Matrix::M<T>::operator*(const Matrix::M<T> &other) const {
    Matrix::M<T> result(this->size().row, other.size().col);

    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < other.size().col; j++) {
            for (size_t k = 0; k < this->size().col; k++) {
                result(i, j) += at(i, k) * other(k, j);
            }
        }
    }

    return result;
}

template<typename T>
Matrix::M <T> Matrix::M<T>::operator*(T v) {
    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().col; j++) {
            at(i, j) *= v;
        }
    }

    return *this;
}

template<typename T>
Matrix::M <T> Matrix::M<T>::operator+(const Matrix::M<T> &other) const {
    Matrix::M<T> res(this->size().row, this->size().col);

    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().col; j++) {
            res.at(i, j) = this->at(i, j) + other.at(i, j);
        }
    }

    return res;
}

template<typename T>
Matrix::M<T> Matrix::M<T>::operator-(const Matrix::M<T> &other) const {
    Matrix::M<T> res(this->size().row, this->size().col);

    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().col; j++) {
            res.at(i, j) = this->at(i, j) - other.at(i, j);
        }
    }

    return res;
}

template<typename T>
void Matrix::M<T>::operator*=(const Matrix::M<T> &other) {
    if (this->size().row != other.size().row && this->size().col != other.size().col) {
        Logger::debug("can't use operator*= with different size matrix");
    }

    Matrix::M<T> temp = *this;

    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().col; j++) {
            this->set(i, j, 0);
            for (size_t k = 0; k < this->size().row; k++) {
                this->at(i, j) += (temp(i, k) * other(k, j));
            }
        }
    }
}

template<typename T>
void Matrix::M<T>::operator*=(T v) {
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        _m[i] *= v;
    }
}

template<typename T>
void Matrix::M<T>::operator+=(const Matrix::M<T> &other) {
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        _m[i] += other._m[i];
    }
}

template<typename T>
void Matrix::M<T>::operator-=(const Matrix::M<T> &other) {
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        _m[i] -= other._m[i];
    }
}

template<typename T>
Matrix::M<T>& Matrix::M<T>::operator=(const Matrix::M<T> &other) {
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        _m[i] = other._m[i];
    }


    //    memcpy(_m, other._m, sizeof(T) * other.size().row * other.size().col);
    return *this;
}

template<typename T>
Matrix::M<T>& Matrix::M<T>::operator=(T v) {
    this->fill(v);
    return *this;
}

template<typename T>
Matrix::M<T>& Matrix::M<T>::operator=(const T *data_array) {
    this->fill(0);
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        _m[i] = data_array[i];
    }
    return *this;
}

template<typename T>
Matrix::M<T>& Matrix::M<T>::operator=(const std::vector<T> &data_vec) {
    for (size_t i = 0; i < data_vec.size(); i++) {
        at(i / this->size().col, i % this->size().col) = data_vec[i];
    }
    return *this;
}

template<typename T>
Matrix::M<T> &Matrix::M<T>::operator=(const Matrix::adjacentMatrix<T> &adjMatrix) {
    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().row; j++) {
            at(i, j) = adjMatrix(i, j).first;
        }
    }
    return *this;
}

template<typename T>
void Matrix::M<T>::fill(T v) {
    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().col; j++) {
            at(i, j) = v;
        }
    }
}

template<typename T>
void Matrix::M<T>::zero() {
    fill(0);
}

template<typename T>
bool Matrix::M<T>::operator==(const Matrix::M<T> &other) const {
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        if (_m[i] != other._m[i]) return false;
    }
    return true;
}

template<typename T>
bool Matrix::M<T>::operator==(Matrix::M<T> other) {
    for (size_t i = 0; i < this->size().row * this->size().col; i++) {
        if (_m[i] != other._m[i]) return false;
    }
    return true;
}

template<typename T>
bool Matrix::M<T>::operator!=(const Matrix::M<T> &other) const {
    return !((*this) == other);
}

template<typename T>
bool Matrix::M<T>::operator!=(Matrix::M<T> other) {
    return !((*this) == other);
}

template<typename T>
Matrix::M<T> Matrix::M<T>::operator/(T v) {
    for (size_t i = 0; i < this->size().row; i++) {
        for (size_t j = 0; j < this->size().col; j++) {
            at(i, j) /= v;
        }
    }
}

template<typename T>
void Matrix::M<T>::operator/=(T v) {
    (*this) = (*this) / v;
}


template<typename T>
Matrix::M<T> Matrix::M<T>::power(const Matrix::M<T> &matrix, int value) {
    if (value == 0) return M::identityMatrix(matrix.size().row);

    if (value == 1) return matrix;

    if (value % 2 == 0) {
        return M::power(matrix * matrix, value / 2);
    } else {
        return matrix * M::power(matrix * matrix, (value-1) / 2);
    }
}

template<typename T>
Matrix::M<T> Matrix::M<T>::identityMatrix(size_t size) {
    Matrix::M<T> temp(size, size);
    temp.fill(0);
    for (size_t i = 0; i < size; i++) {
        temp(i, i, 1);
    }

    return temp;
}

template<typename T>
Matrix::M<T> Matrix::M<T>::operator^(T v) {
    return Matrix::M<T>::power((*this), v);
}

template<typename T>
void Matrix::M<T>::operator^=(T v) {
    (*this) = (*this) ^ v;
}

template<typename T>
Matrix::M<T>::M(const T *data) : _m() {
    (*this) = data;
}

template<typename T>
Matrix::M<T>::M(const Matrix::adjacentMatrix<T> &adjMatrix) {
    (*this) = adjMatrix;
}

template<typename T>
Matrix::M<T>::M(const std::vector<T> &vec) : _m() {
    (*this) = vec;
}

template<typename T>
Matrix::M<T>::~M() {}

template<typename T>
Matrix::adjacentMatrix<T>::adjacentMatrix(size_t size) : _size(size) {
    _m = new std::pair<T, T>[size * size];
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            at(i, j) = std::make_pair(0, 0);
        }
    }
}

template<typename T>
Matrix::adjacentMatrix<T>::adjacentMatrix(const std::pair<T, T> *data) {
    (*this) = data;
}

template<typename T>
Matrix::adjacentMatrix<T>::adjacentMatrix(const std::vector<std::pair<T, T>> &vec) {
    (*this) = vec;
}

template<typename T>
Matrix::adjacentMatrix<T>::~adjacentMatrix() = default;

template<typename T>
std::pair<T, T> &Matrix::adjacentMatrix<T>::operator()(size_t row, size_t col) {
    return at(row, col);
}

template<typename T>
const std::pair<T, T> &Matrix::adjacentMatrix<T>::operator()(size_t row, size_t col) const {
    return at(row, col);
}

template<typename T>
void Matrix::adjacentMatrix<T>::operator()(size_t row, size_t col, std::pair<T, T> value) {
    return set(row, col, value);
}

template<typename T>
Matrix::adjacentMatrix<T>::adjacentMatrix(const Matrix::adjacentMatrix<T> &other) {
    (*this) = other;
}

template<typename T>
std::pair<T, T> &Matrix::adjacentMatrix<T>::at(size_t row, size_t col) {
    if (row >= this->size() || col >= this->size()) {
        throw std::out_of_range("Matrix::adjacentMatrix::at() -- index out of range !");
    }
    return _m[row * this->size() + col];
}

template<typename T>
const std::pair<T, T> &Matrix::adjacentMatrix<T>::at(size_t row, size_t col) const {
    if (row >= this->size() || col >= this->size()) {
        throw std::out_of_range("Matrix::adjacentMatrix::at() -- index out of range !");
    }
    return _m[row * this->size() + col];
}

template<typename T>
void Matrix::adjacentMatrix<T>::set(size_t row, size_t col, const std::pair<T, T> &value) {
    _m[row * this->size() + col] = value;
}

template<typename T>
size_t Matrix::adjacentMatrix<T>::size() const {
    return _size;
}
