#include <gtest/gtest.h>
#include "../include/Matrix.h"

struct SimpleMatrix : public ::testing::Test {
    Matrix m;
    SimpleMatrix() : m(2) {
        m.add(0, 0, 1);
        m.add(0, 1, 2);
        m.add(1, 0, 3);
        m.add(1, 1, 4);
    }
};

TEST_F(SimpleMatrix, add) {

    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix res(2);

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    ASSERT_TRUE(res == (m + secondMatrix));
}

TEST_F(SimpleMatrix, add_equal) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix res(2);

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    m += secondMatrix;

    ASSERT_TRUE(res == m);
}

TEST_F(SimpleMatrix, sub) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix res(2);

    res(0, 0, 0);
    res(0, 1, 0);
    res(1, 0, 0);
    res(1, 1, 0);

    ASSERT_TRUE(res == (m - secondMatrix));
}

TEST_F(SimpleMatrix, sub_equal) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix res(2);

    res(0, 0, 0);
    res(0, 1, 0);
    res(1, 0, 0);
    res(1, 1, 0);

    m -= secondMatrix;

    ASSERT_TRUE(res == m);
}

TEST_F(SimpleMatrix, mul) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix res(2);

    res(0, 0, 7);
    res(0, 1, 10);
    res(1, 0, 15);
    res(1, 1, 22);

    ASSERT_TRUE(res == (m * secondMatrix));
}

TEST_F(SimpleMatrix, mul_equal) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    Matrix res(2);

    res(0, 0, 7);
    res(0, 1, 10);
    res(1, 0, 15);
    res(1, 1, 22);

    m *= secondMatrix;

    ASSERT_TRUE(res == m);
}

TEST_F(SimpleMatrix, mul_value) {
    Matrix res(2);

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    ASSERT_TRUE(res == (m * 2));
}

TEST_F(SimpleMatrix, mul_value_equal) {
    Matrix res(2);

    res(0, 0, 2);
    res(0, 1, 4);
    res(1, 0, 6);
    res(1, 1, 8);

    m *= 2;

    ASSERT_TRUE(res == m);
}

TEST_F(SimpleMatrix, power) {
    Matrix res(2);

    res(0, 0, 37);
    res(0, 1, 54);
    res(1, 0, 81);
    res(1, 1, 118);

    ASSERT_TRUE(res == (m ^ 3));
}

TEST_F(SimpleMatrix, power_equal) {
    Matrix res(2);

    res(0, 0, 37);
    res(0, 1, 54);
    res(1, 0, 81);
    res(1, 1, 118);

    m ^= 3;

    ASSERT_TRUE(res == m);
}

TEST_F(SimpleMatrix, equal) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 4);

    ASSERT_TRUE(m == secondMatrix);
}

TEST_F(SimpleMatrix, not_equal) {
    Matrix secondMatrix(2);

    secondMatrix(0, 0, 1);
    secondMatrix(0, 1, 2);
    secondMatrix(1, 0, 3);
    secondMatrix(1, 1, 5);

    ASSERT_TRUE(m != secondMatrix);
}

TEST_F(SimpleMatrix, copy) {
    Matrix secondMatrix(m);

    ASSERT_TRUE(m == secondMatrix);
}

TEST_F(SimpleMatrix, copy_equal) {
    Matrix secondMatrix(2);

    secondMatrix = m;

    ASSERT_TRUE(m == secondMatrix);
}