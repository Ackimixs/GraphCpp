#pragma once

#include "utils.h"

namespace Matrix {
    class M {
    protected:
        int **_m;
        /**
         * @brief size of the matrix
         * first = row
         * second = col
         */
        std::pair<int, int> _size;

    public:
        M(std::pair<int, int> size);

        M(int size);

        M(const Matrix::M& matrix);

        /**
         * @brief utils function to elevate a matrix to a power
         * @param matrix matrix to power
         * @param value power value
         * @return matrix powered
         */
        static M power(const M& matrix, int value);

        static M identityMatrix(int n);

        ~M();

        void set(int row, int col, int value);

        virtual std::pair<int, int> size() const;

        int operator()(int row, int col) const;

        void operator()(int row, int col, int value);

        void operator+=(const M& matrix);

        void operator-=(const M& matrix);

        void operator*=(const M& matrix);

        void operator*=(int value);

        void operator^=(int value) const;

        M& operator=(const M& matrix);

        M operator+(const M& matrix) const;

        M operator-(const M& matrix) const;

        M operator*(const M& matrix) const;

        M operator*(int value) const;

        M operator^(int value) const;

        bool operator==(const M& matrix) const;

        bool operator!=(const M& matrix) const;

        virtual void print();
    };
}