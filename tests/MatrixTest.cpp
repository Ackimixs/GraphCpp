#include <gtest/gtest.h>
#include "../include/Matrix.hpp"

struct SimpleMatrix : public ::testing::Test {
    Matrix::M<2, 2, int> m;
    SimpleMatrix() : m() {
        m.set(0, 0, 1);
        m.set(0, 1, 2);
        m.set(1, 0, 3);
        m.set(1, 1, 4);
    }
};

// ----------------- TESTING ADD --------------

TEST_F(SimpleMatrix, add) {

    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix::M<2, 2, int> res;

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    ASSERT_EQ(res, (m + secondMatrix));
}

TEST_F(SimpleMatrix, addEqual) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix::M<2, 2, int> res;

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    m += secondMatrix;

    ASSERT_EQ(res, m);
}

// ----------------- TESTING SUB --------------

TEST_F(SimpleMatrix, sub) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix::M<2, 2, int> res;

    res(0, 0, 0);
    res(0, 1, 0);
    res(1, 0, 0);
    res(1, 1, 0);

    ASSERT_EQ(res, (m - secondMatrix));
}

TEST_F(SimpleMatrix, subEqual) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix::M<2, 2, int> res;

    res(0, 0, 0);
    res(0, 1, 0);
    res(1, 0, 0);
    res(1, 1, 0);

    m -= secondMatrix;

    ASSERT_EQ(res, m);
}

// ----------------- TESTING MATRIX MULTIPLICATION --------------

TEST_F(SimpleMatrix, mul) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix::M<2, 2, int> res;

    res(0, 0, 7);
    res(0, 1, 10);
    res(1, 0, 15);
    res(1, 1, 22);

    ASSERT_EQ(res, (m * secondMatrix));
}

TEST_F(SimpleMatrix, mulEqual) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix::M<2, 2, int> res;

    res(0, 0, 7);
    res(0, 1, 10);
    res(1, 0, 15);
    res(1, 1, 22);

    m *= secondMatrix;

    ASSERT_EQ(res, m);
}

TEST_F(SimpleMatrix, mulValue) {
    Matrix::M<2, 2, int> res;

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    ASSERT_EQ(res, (m * 2));
}

TEST_F(SimpleMatrix, mulValueEqual) {
    Matrix::M<2, 2, int> res;

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    m *= 2;

    ASSERT_EQ(res, m);
}

TEST_F(SimpleMatrix, checkIdentity) {
    Matrix::M<2, 2, int> ide = Matrix::M<2, 2, int>::identityMatrix();

    ASSERT_EQ(m * ide, m);
}

TEST(Matrix, mulNotSameSize) {
    Matrix::M<4, 2, int> m;

    m.set(0, 0, 0);
    m.set(0, 1, 1);
    m.set(1, 0, 2);
    m.set(1, 1, 3);
    m.set(2, 0, 4);
    m.set(2, 1, 5);
    m.set(3, 0, 6);
    m.set(3, 1, 7);

    Matrix::M<2, 3, int> m2;

    m.set(0, 0, 20);
    m.set(0, 1, 15);
    m.set(0, 2, 2);
    m.set(1, 0, 0);
    m.set(1, 1, 4);
    m.set(1, 2, 61);

    Matrix::M m3 = m * m2;

    Matrix::M<4, 3, int> res;

    m.set(0, 0, 0);
    m.set(0, 1, 4);
    m.set(0, 2, 61);
    m.set(1, 0, 40);
    m.set(1, 1, 42);
    m.set(1, 2, 187);
    m.set(2, 0, 80);
    m.set(2, 1, 80);
    m.set(2, 2, 313);
    m.set(3, 0, 120);
    m.set(3, 1, 118);
    m.set(3, 2, 439);

    ASSERT_EQ(m3, res);
}

// ----------------- TESTING POWER --------------

TEST_F(SimpleMatrix, power) {
    Matrix::M<2, 2, int> res;

    res(0, 0, 37);
    res(0, 1, 54);
    res(1, 0, 81);
    res(1, 1, 118);

    ASSERT_EQ(res, (m ^ 3));
}

TEST_F(SimpleMatrix, powerEqual) {
    Matrix::M<2, 2, int> res;

    res(0, 0, 37);
    res(0, 1, 54);
    res(1, 0, 81);
    res(1, 1, 118);

    m ^= 3;

    ASSERT_EQ(res, m);
}

// ----------------- TESTING EQUAL --------------

TEST_F(SimpleMatrix, equal) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    ASSERT_EQ(m, secondMatrix);
}

TEST_F(SimpleMatrix, notEqual) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 5);

    ASSERT_NE(m, secondMatrix);
}

// ----------------- TESTING COPY --------------

TEST_F(SimpleMatrix, copy) {
    Matrix::M secondMatrix(m);

    ASSERT_EQ(m, secondMatrix);
}

TEST_F(SimpleMatrix, copy_equal) {
    Matrix::M<2, 2, int> secondMatrix;

    secondMatrix = m;

    ASSERT_EQ(m, secondMatrix);
}