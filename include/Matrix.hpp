#pragma once

#include "Utils.hpp"

#include <cstring>
#include <iostream>
#include <iomanip>

namespace Matrix {

    template <size_t R, typename T = int>
    class adjacentMatrix {
    protected:
        std::pair<T, T> _m[R * R];

        struct {
            size_t row = R;
            size_t col = R;
        } _size;

    public:

        adjacentMatrix();

        adjacentMatrix(const std::vector<std::pair<T, T>>& vec);

        adjacentMatrix(const std::pair<T, T>* data);

        adjacentMatrix(const adjacentMatrix<R, T>& other);

        ~adjacentMatrix();

        inline std::pair<T, T>& operator()(size_t row, size_t col);

        inline const std::pair<T, T>& operator()(size_t row, size_t col) const;

        inline void operator()(size_t row, size_t col, std::pair<T, T> value);

        virtual inline std::pair<T, T>& at(size_t row, size_t col);

        virtual inline const std::pair<T, T>& at(size_t row, size_t col) const;

        inline void set(size_t row, size_t col, const std::pair<T, T>& value);

        friend std::ostream& operator << (std::ostream& os, const adjacentMatrix<R, T>& matrix) {

            for(size_t i = 0; i < R; i++)
            {
                for(size_t j = 0; j < R; j++)
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
    template< size_t R, size_t C, typename T = int >
    class M {
    protected:
        T _m[R * C];
        /**
         * @brief size of the matrix
         * first = row
         * second = col
         */
        struct {
            size_t row = R;
            size_t col = C;
        } _size;

    public:
        M();

        template< size_t P, size_t Q, typename U>
        M(const M<P, Q, U> &other);

        M(const std::vector<T>& vec);

        M(const T* data);

        M(const Matrix::adjacentMatrix<R, T>& adjMatrix);

        ~M();

        static M power(const M& matrix, int value);

        static M identityMatrix();

        inline T& operator()(size_t row, size_t col);
        inline const T& operator()(size_t row, size_t col) const;

        inline void operator()(size_t row, size_t col, T value);

        virtual inline T& at(size_t row, size_t col);

        virtual inline const T& at(size_t row, size_t col) const;

        inline void set(size_t row, size_t col, T value);

        template<size_t P>
        M<R, P, T> operator*(const M<C, P, T> &other) const;

        M operator*(T v);

        M operator/(T v);

        M operator^(T v);

        inline M operator+(const M& other) const;
        inline M operator-(const M& other) const;


        void operator*=(const M<R, C, T> &other);

        void operator*=(T v);

        void operator/=(T v);

        void operator^=(T v);

        void operator+=(const M& other);
        void operator-=(const M& other);

        M& operator=(const M<R, C, T> &other);

        M& operator=(const T* data_array);
        M& operator=(const std::vector<T>& data_vec);

        M& operator=(const Matrix::adjacentMatrix<R, T>& adjMatrix);

        M& operator=(T v);
        void fill(T v);

        void zero();

        bool operator==(const M& other) const;
        bool operator==(M other);

        bool operator!=(const M& other) const;
        bool operator!=(M other);

        friend std::ostream& operator << (std::ostream& os, const M<R, C, T>& matrix) {

            for(size_t i = 0; i < R; i++)
            {
                for(size_t j = 0; j < C; j++)
                {
                    os << std::setw(6) << matrix.at(i, j) << " ";
                }
                os << std::endl;
            }
            return os;
        };
    };
}




template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>::M() : _m() {
    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            at(i, j) = T();
        }
    }
}

template<size_t R, size_t C, typename T>
template<size_t P, size_t Q, typename U>
Matrix::M<R, C, T>::M(const Matrix::M<P, Q, U> &other) : _m() {
    (*this) = other;
}

template<size_t R, size_t C, typename T>
T &Matrix::M<R, C, T>::operator()(size_t row, size_t col) {
    return at(row, col);
}

template<size_t R, size_t C, typename T>
const T &Matrix::M<R, C, T>::operator()(size_t row, size_t col) const {
    return at(row, col);
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator()(size_t row, size_t col, T value) {
    return set(row, col, value);
}

template<size_t R, size_t C, typename T>
T &Matrix::M<R, C, T>::at(size_t row, size_t col) {
    if (row >= R || col >= C) {
        throw std::out_of_range("Matrix::M::at() -- index out of range !");
    }
    return _m[row * C + col];
}

template<size_t R, size_t C, typename T>
const T &Matrix::M<R, C, T>::at(size_t row, size_t col) const {
    if (row >= R || col >= C) {
        throw std::out_of_range("Matrix::M::at() -- index out of range !");
    }
    return _m[row * C + col];
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::set(size_t row, size_t col, T value) {
    _m[row * C + col] = value;
}

template<size_t R, size_t C, typename T>
template<size_t P>
Matrix::M <R, P, T> Matrix::M<R, C, T>::operator*(const Matrix::M<C, P, T> &other) const {
    Matrix::M<R, P, T> result;

    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < P; j++) {
            for (size_t k = 0; k < C; k++) {
                result(i, j) += at(i, k) * other(k, j);
            }
        }
    }

    return result;
}

template<size_t R, size_t C, typename T>
Matrix::M <R, C, T> Matrix::M<R, C, T>::operator*(T v) {
    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            at(i, j) *= v;
        }
    }

    return *this;
}

template<size_t R, size_t C, typename T>
Matrix::M <R, C, T> Matrix::M<R, C, T>::operator+(const Matrix::M<R, C, T> &other) const {
    Matrix::M<R, C, T> res;

    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            res.at(i, j) = this->at(i, j) + other.at(i, j);
        }
    }

    return res;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T> Matrix::M<R, C, T>::operator-(const Matrix::M<R, C, T> &other) const {
    Matrix::M<R, C, T> res;

    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            res.at(i, j) = this->at(i, j) - other.at(i, j);
        }
    }

    return res;
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator*=(const Matrix::M<R, C, T> &other) {
    Matrix::M<R, C, T> temp = *this;

    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            this->set(i, j, 0);
            for (size_t k = 0; k < R; k++) {
                this->at(i, j) += (temp(i, k) * other(k, j));
            }
        }
    }
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator*=(T v) {
    for (size_t i = 0; i < R * C; i++) {
        _m[i] *= v;
    }
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator+=(const Matrix::M<R, C, T> &other) {
    for (size_t i = 0; i < R * C; i++) {
        _m[i] += other._m[i];
    }
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator-=(const Matrix::M<R, C, T> &other) {
    for (size_t i = 0; i < R * C; i++) {
        _m[i] -= other._m[i];
    }
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>& Matrix::M<R, C, T>::operator=(const Matrix::M<R, C, T> &other) {
    memcpy(_m, other._m, sizeof(T) * R * C);
    return *this;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>& Matrix::M<R, C, T>::operator=(T v) {
    this->fill(v);
    return *this;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>& Matrix::M<R, C, T>::operator=(const T *data_array) {
    this->fill(0);
    for (size_t i = 0; i < R * C; i++) {
        _m[i] = data_array[i];
    }
    return *this;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>& Matrix::M<R, C, T>::operator=(const std::vector<T> &data_vec) {
    for (size_t i = 0; i < data_vec.size(); i++) {
        at(i / C, i % C) = data_vec[i];
    }
    return *this;
}

template<size_t R, size_t C, typename T>
Matrix::M <R, C, T> &Matrix::M<R, C, T>::operator=(const Matrix::adjacentMatrix<R, T> &adjMatrix) {
    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < R; j++) {
            at(i, j) = adjMatrix(i, j).first;
        }
    }
    return *this;
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::fill(T v) {
    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            at(i, j) = v;
        }
    }
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::zero() {
    fill(0);
}

template<size_t R, size_t C, typename T>
bool Matrix::M<R, C, T>::operator==(const Matrix::M<R, C, T> &other) const {
    for (size_t i = 0; i < R * C; i++) {
        if (_m[i] != other._m[i]) return false;
    }
    return true;
}

template<size_t R, size_t C, typename T>
bool Matrix::M<R, C, T>::operator==(Matrix::M<R, C, T> other) {
    for (size_t i = 0; i < R * C; i++) {
        if (_m[i] != other._m[i]) return false;
    }
    return true;
}

template<size_t R, size_t C, typename T>
bool Matrix::M<R, C, T>::operator!=(const Matrix::M<R, C, T> &other) const {
    return !((*this) == other);
}

template<size_t R, size_t C, typename T>
bool Matrix::M<R, C, T>::operator!=(Matrix::M<R, C, T> other) {
    return !((*this) == other);
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T> Matrix::M<R, C, T>::operator/(T v) {
    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < C; j++) {
            at(i, j) /= v;
        }
    }
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator/=(T v) {
    (*this) = (*this) / v;
}


template<size_t R, size_t C, typename T>
Matrix::M<R, C, T> Matrix::M<R, C, T>::power(const Matrix::M<R, C, T> &matrix, int value) {
    if (value == 0) return M::identityMatrix();

    if (value == 1) return matrix;

    if (value % 2 == 0) {
        return M::power(matrix * matrix, value / 2);
    } else {
        return matrix * M::power(matrix * matrix, (value-1) / 2);
    }
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T> Matrix::M<R, C, T>::identityMatrix() {
    Matrix::M<R, C, T> temp;
    temp.fill(0);
    for (size_t i = 0; i < R; i++) {
        temp(i, i, 1);
    }

    return temp;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T> Matrix::M<R, C, T>::operator^(T v) {
    return Matrix::M<R, C, T>::power((*this), v);
}

template<size_t R, size_t C, typename T>
void Matrix::M<R, C, T>::operator^=(T v) {
    (*this) = (*this) ^ v;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>::M(const T *data) : _m() {
    (*this) = data;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>::M(const Matrix::adjacentMatrix<R, T> &adjMatrix) {
    (*this) = adjMatrix;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>::M(const std::vector<T> &vec) : _m() {
    (*this) = vec;
}

template<size_t R, size_t C, typename T>
Matrix::M<R, C, T>::~M() {}

template<size_t R, typename T>
Matrix::adjacentMatrix<R, T>::adjacentMatrix() {
    for (size_t i = 0; i < R; i++) {
        for (size_t j = 0; j < R; j++) {
            at(i, j) = std::make_pair(0, 0);
        }
    }
}

template<size_t R, typename T>
Matrix::adjacentMatrix<R, T>::adjacentMatrix(const std::pair<T, T> *data) {
    (*this) = data;
}

template<size_t R, typename T>
Matrix::adjacentMatrix<R, T>::adjacentMatrix(const std::vector<std::pair<T, T>> &vec) {
    (*this) = vec;
}

template<size_t R, typename T>
Matrix::adjacentMatrix<R, T>::~adjacentMatrix() = default;

template<size_t R, typename T>
std::pair<T, T> &Matrix::adjacentMatrix<R, T>::operator()(size_t row, size_t col) {
    return at(row, col);
}

template<size_t R, typename T>
const std::pair<T, T> &Matrix::adjacentMatrix<R, T>::operator()(size_t row, size_t col) const {
    return at(row, col);
}

template<size_t R, typename T>
void Matrix::adjacentMatrix<R, T>::operator()(size_t row, size_t col, std::pair<T, T> value) {
    return set(row, col, value);
}

template<size_t R, typename T>
Matrix::adjacentMatrix<R, T>::adjacentMatrix(const Matrix::adjacentMatrix<R, T> &other) {
    (*this) = other;
}

template<size_t R, typename T>
std::pair<T, T> &Matrix::adjacentMatrix<R, T>::at(size_t row, size_t col) {
    if (row >= R || col >= R) {
        throw std::out_of_range("Matrix::adjacentMatrix::at() -- index out of range !");
    }
    return _m[row * R + col];
}

template<size_t R, typename T>
const std::pair<T, T> &Matrix::adjacentMatrix<R, T>::at(size_t row, size_t col) const {
    if (row >= R || col >= R) {
        throw std::out_of_range("Matrix::adjacentMatrix::at() -- index out of range !");
    }
    return _m[row * R + col];
}

template<size_t R, typename T>
void Matrix::adjacentMatrix<R, T>::set(size_t row, size_t col, const std::pair<T, T> &value) {
    _m[row * R + col] = value;
}
