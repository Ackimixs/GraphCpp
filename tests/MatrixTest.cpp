#include "../include/Matrix.hpp"

#include <gtest/gtest.h>

struct SimpleMatrix : public ::testing::Test {
    Matrix::M<int> m;
    SimpleMatrix() : m(s(2, 2)) {
        m.set(0, 0, 1);
        m.set(0, 1, 2);
        m.set(1, 0, 3);
        m.set(1, 1, 4);
    }
};

// ----------------- TESTING ADD --------------

TEST_F(SimpleMatrix, add) {

    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            2, 4,
            6, 8
    };

    res = data2;

    ASSERT_EQ(res, (m + secondMatrix));
}

TEST_F(SimpleMatrix, addEqual) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            2, 4,
            6, 8
    };

    res = data2;

    m += secondMatrix;

    ASSERT_EQ(res, m);
}

// ----------------- TESTING SUB --------------

TEST_F(SimpleMatrix, sub) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            0, 0,
            0,0
    };

    res = data2;

    ASSERT_EQ(res, (m - secondMatrix));
}

TEST_F(SimpleMatrix, subEqual) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            0, 0,
            0, 0
    };

    res = data2;

    m -= secondMatrix;

    ASSERT_EQ(res, m);
}

// ----------------- TESTING MATRIX MULTIPLICATION --------------

TEST_F(SimpleMatrix, mul) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            7, 10,
            15, 22
    };

    res = data2;

    ASSERT_EQ(res, (m * secondMatrix));
}

TEST_F(SimpleMatrix, mulEqual) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            7, 10,
            15, 22
    };

    res = data2;

    m *= secondMatrix;

    ASSERT_EQ(res, m);
}

TEST_F(SimpleMatrix, mulValue) {
    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            2, 4,
            6, 8
    };

    res = data2;

    ASSERT_EQ(res, (m * 2));
}

TEST_F(SimpleMatrix, mulValueEqual) {
    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            2, 4,
            6, 8
    };

    res = data2;

    m *= 2;

    ASSERT_EQ(res, m);
}

TEST_F(SimpleMatrix, checkIdentity) {
    Matrix::M<int> ide = Matrix::M<int>::identityMatrix(2);

    ASSERT_EQ(m * ide, m);
}

TEST(Matrix, mulNotSameSize) {
    Matrix::M<int> m(s(4, 2));

    int data[] = {
            0, 1,
            2, 3,
            4, 5,
            6, 7
    };

    m = data;

    Matrix::M<int> m2(s(2, 3));

    int data2[] = {
            20, 15, 2,
            0, 4, 61
    };

    m2 = data2;

    Matrix::M m3 = m * m2;

    Matrix::M<int> res(s(4, 3));

    int data3[] = {
            0, 4, 61,
            40, 42, 187,
            80, 80, 313,
            120, 118, 439
    };

    res = data3;

    ASSERT_EQ(m3, res);
}

// ----------------- TESTING POWER --------------

TEST_F(SimpleMatrix, power) {
    Matrix::M<int> res(s(2, 2));

    int data2[] = {
            37, 54,
            81, 118
    };

    res = data2;

    ASSERT_EQ(res, (m ^ 3));
}

TEST_F(SimpleMatrix, powerEqual) {
    Matrix::M<int> res(s(2, 2));

    int data[] = {
            37, 54,
            81, 118
    };

    res = data;

    m ^= 3;

    ASSERT_EQ(res, m);
}

// ----------------- TESTING EQUAL --------------

TEST_F(SimpleMatrix, equal) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 4
    };

    secondMatrix = data;

    ASSERT_EQ(m, secondMatrix);
}

TEST_F(SimpleMatrix, notEqual) {
    Matrix::M<int> secondMatrix(s(2, 2));

    int data[] = {
            1, 2,
            3, 5
    };

    secondMatrix = data;

    ASSERT_NE(m, secondMatrix);
}

// ----------------- TESTING COPY --------------

TEST_F(SimpleMatrix, copy) {
    Matrix::M secondMatrix(m);

    ASSERT_EQ(m, secondMatrix);
}

TEST_F(SimpleMatrix, copy_equal) {
    Matrix::M<int> secondMatrix(s(2, 2));

    secondMatrix = m;

    ASSERT_EQ(m, secondMatrix);
}