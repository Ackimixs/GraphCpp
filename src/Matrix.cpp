#include "../include/Matrix.h"

Matrix::Matrix(int size) : _size(size) {
    this->_m = new int * [size];
    for (int i = 0; i < size; i++) {
        this->_m[i] = new int[size];
        for (int j = 0; j < this->size(); j++) {
            this->_m[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < this->_size; i++) {
        delete[] this->_m[i];
    }
    delete[] this->_m;
}

void Matrix::add(int row, int col, int value) {
    if (row < 0 || row > this->size()) {
        throw std::invalid_argument("row params must be between 0 and _size");
    }

    else if (col < 0 || col > this->size()) {
        throw std::invalid_argument("col params must be between 0 and _size");
    } else {
        this->_m[row][col] = value;
    }
}

int Matrix::size() const {
    return this->_size;
}

int Matrix::operator()(int row, int col) const {
    return this->_m[row][col];
}

void Matrix::operator()(int row, int col, int value) {
    this->_m[row][col] += value;
}

void Matrix::operator+=(const Matrix &matrix) {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator += -- _size of both matrix must be the same !");
    } else {
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->size(); j++) {
                this->_m[i][j] += matrix(i, j);
            }
        }
    }
}

void Matrix::operator-=(const Matrix &matrix) {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator -= -- _size of both matrix must be the same !");
    } else {
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->size(); j++) {
                this->_m[i][j] -= matrix(i, j);
            }
        }
    }
}

void Matrix::operator*=(const Matrix &matrix) {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator *= -- _size of both matrix must be the same ! (real * matrix not implemented)");
    }

    Matrix temp(*this);

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            this->_m[i][j] = 0;
            for (int k = 0; k < this->size(); k++) {
                this->_m[i][j] += (temp(i, k) * matrix(k, j));
            }
        }
    }
}

void Matrix::operator*=(int value) {
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            this->_m[i][j] *= value;
        }
    }
}

Matrix Matrix::operator+(const Matrix &matrix) const {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator += -- _size of both matrix must be the same !");
    }

    Matrix m(this->size());

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            int value = this->_m[i][j] + matrix(i, j);
            m(i, j, value);
        }
    }

    return m;
}

Matrix Matrix::operator-(const Matrix &matrix) const {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator += -- _size of both matrix must be the same !");
    }

    Matrix m(this->size());

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            int value = this->_m[i][j] - matrix(i, j);
            m(i, j, value);
        }
    }

    return m;
}

Matrix Matrix::operator*(const Matrix &matrix) const {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator *= -- _size of both matrix must be the same ! (real * matrix not implemented)");
    }

    Matrix temp(this->size());

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            for (int k = 0; k < this->size(); k++) {
                int value = (this->_m[i][k] * matrix(k, j));
                temp(i, j, value);
            }
        }
    }

    return temp;

    /*
     *     for (int i = 0; i < this->_size(); i++) {
        for (int j = 0; j < this->_size(); j++) {
            this->_m[i][j] = 0;
            for (int k = 0; k < this->_size(); k++) {
                this->_m[i][j] += (temp(i, k) * matrix(k, j));
            }
        }
    }
     */
}

Matrix Matrix::operator*(int value) const {
    Matrix m(this->size());

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            int v = this->_m[i][j] * value;
            m.add(i, j, v);
        }
    }

    return m;
}

bool Matrix::operator==(const Matrix &matrix) const {
    if (this->size() != matrix.size()) {
        return false;
    }

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if (this->_m[i][j] != matrix(i, j)) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix &matrix) const {
    return !((*this) == matrix);
}

Matrix::Matrix(const Matrix &matrix) {
    this->_size = matrix.size();
    this->_m = new int * [this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_m[i] = new int[this->_size];
        for (int j = 0; j < this->_size; j++) {
            this->_m[i][j] = matrix(i, j);
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            std::cout << this->_m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::power(const Matrix& matrix, int value) {
    if (value == 1) return matrix;

    if (value % 2 == 0) {
        return Matrix::power(matrix * matrix, value / 2);
    } else {
        return matrix * Matrix::power(matrix * matrix, (value-1) / 2);
    }
}

void Matrix::operator^=(int value) const {
    Matrix temp = Matrix::power((*this), value);

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            this->_m[i][j] = temp(i, j);
        }
    }
}

Matrix Matrix::operator^(int value) const {
    return Matrix::power((*this), value);
}

Matrix& Matrix::operator=(const Matrix &matrix) {
    if (this != &matrix) {
        for (int i = 0; i < this->_size; i++) {
            delete[] this->_m[i];
        }
        delete[] this->_m;

        this->_size = matrix.size();
        this->_m = new int * [this->_size];
        for (int i = 0; i < this->_size; i++) {
            this->_m[i] = new int[this->_size];
            for (int j = 0; j < this->_size; j++) {
                this->_m[i][j] = matrix(i, j);
            }
        }
    }

    return *this;
}