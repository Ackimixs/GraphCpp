#include "../include/Matrix.h"

Matrix::M::M(int size) : _size({size, size}) {
    this->_m = new int * [size];
    for (int i = 0; i < size; i++) {
        this->_m[i] = new int[size];
        for (int j = 0; j < size; j++) {
            this->_m[i][j] = 0;
        }
    }
}

Matrix::M::M(std::pair<int, int> size) : _size(size) {
    this->_m = new int * [size.first];
    for (int i = 0; i < size.first; i++) {
        this->_m[i] = new int[size.second];
        for (int j = 0; j < size.second; j++) {
            this->_m[i][j] = 0;
        }
    }
}

Matrix::M::M(const M &matrix) {
    this->_size = matrix.size();
    this->_m = new int * [this->_size.first];
    for (int i = 0; i < this->_size.first; i++) {
        this->_m[i] = new int[this->_size.second];
        for (int j = 0; j < this->_size.second; j++) {
            this->_m[i][j] = matrix(i, j);
        }
    }
}

Matrix::M::~M() {
    for (int i = 0; i < this->_size.first; i++) {
        delete[] this->_m[i];
    }
    delete[] this->_m;
}

void Matrix::M::set(int row, int col, int value) {
    if (row < 0 || row > this->size().first) {
        throw std::invalid_argument("row params must be between 0 and the number of row");
    }

    else if (col < 0 || col > this->size().second) {
        throw std::invalid_argument("col params must be between 0 and the number of col");
    } else {
        this->_m[row][col] = value;
    }
}

std::pair<int, int> Matrix::M::size() const {
    return this->_size;
}

int Matrix::M::operator()(int row, int col) const {
    return this->_m[row][col];
}

void Matrix::M::operator()(int row, int col, int value) {
    this->_m[row][col] += value;
}

void Matrix::M::operator+=(const M &matrix) {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator += -- _size of both matrix must be the same !");
    } else {
        for (int i = 0; i < this->size().first; i++) {
            for (int j = 0; j < this->size().second; j++) {
                this->_m[i][j] += matrix(i, j);
            }
        }
    }
}

void Matrix::M::operator-=(const M &matrix) {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator -= -- _size of both matrix must be the same !");
    } else {
        for (int i = 0; i < this->size().first; i++) {
            for (int j = 0; j < this->size().second; j++) {
                this->_m[i][j] -= matrix(i, j);
            }
        }
    }
}

void Matrix::M::operator*=(const M &matrix) {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("Impossible to use *= on matrix, when both don't have same size, use 'm1 * m2' instead");
    }

    M temp(*this);

    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            this->_m[i][j] = 0;
            for (int k = 0; k < this->size().first; k++) {
                this->_m[i][j] += (temp(i, k) * matrix(k, j));
            }
        }
    }
}

void Matrix::M::operator*=(int value) {
    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            this->_m[i][j] *= value;
        }
    }
}

Matrix::M Matrix::M::operator+(const M &matrix) const {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator += -- _size of both matrix must be the same !");
    }

    M m(this->size());

    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            int value = this->_m[i][j] + matrix(i, j);
            m(i, j, value);
        }
    }

    return m;
}

Matrix::M Matrix::M::operator-(const M &matrix) const {
    if (this->size() != matrix.size()) {
        throw std::invalid_argument("matrix operator += -- _size of both matrix must be the same !");
    }

    M m(this->size());

    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            int value = this->_m[i][j] - matrix(i, j);
            m(i, j, value);
        }
    }

    return m;
}

Matrix::M Matrix::M::operator*(const M &matrix) const {
    if (this->size().second != matrix.size().first) {
        throw std::invalid_argument("the number of col of the first matrix must be the number of row of the second matrix !");
    }

    M temp({this->size().first, matrix.size().second});

    for (int i = 0; i < temp.size().first; i++) {
        for (int j = 0; j < temp.size().second; j++) {
            for (int k = 0; k < this->size().second; k++) {
                int value = (this->_m[i][k] * matrix(k, j));
                temp(i, j, value);
            }
        }
    }

    return temp;
}

Matrix::M Matrix::M::operator*(int value) const {
    M m(this->size());

    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            int v = this->_m[i][j] * value;
            m.set(i, j, v);
        }
    }

    return m;
}

bool Matrix::M::operator==(const M &matrix) const {
    if (this->size() != matrix.size()) {
        return false;
    }

    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            if (this->_m[i][j] != matrix(i, j)) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::M::operator!=(const M &matrix) const {
    return !((*this) == matrix);
}

void Matrix::M::print() {
    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            std::cout << this->_m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix::M Matrix::M::power(const M& matrix, int value) {
    if (value == 0) return M::identityMatrix(matrix.size().first);

    if (value == 1) return matrix;

    if (value % 2 == 0) {
        return M::power(matrix * matrix, value / 2);
    } else {
        return matrix * M::power(matrix * matrix, (value-1) / 2);
    }
}

void Matrix::M::operator^=(int value) const {
    M temp = M::power((*this), value);

    for (int i = 0; i < this->size().first; i++) {
        for (int j = 0; j < this->size().second; j++) {
            this->_m[i][j] = temp(i, j);
        }
    }
}

Matrix::M Matrix::M::operator^(int value) const {
    return M::power((*this), value);
}

Matrix::M& Matrix::M::operator=(const M &matrix) {
    if (this != &matrix) {
        for (int i = 0; i < this->_size.first; i++) {
            delete[] this->_m[i];
        }
        delete[] this->_m;

        this->_size = matrix.size();
        this->_m = new int * [this->_size.first];
        for (int i = 0; i < this->_size.first; i++) {
            this->_m[i] = new int[this->_size.second];
            for (int j = 0; j < this->_size.second; j++) {
                this->_m[i][j] = matrix(i, j);
            }
        }
    }

    return *this;
}

Matrix::M Matrix::M::identityMatrix(int n) {
    M temp(n);

    for (int i = 0; i < temp.size().first; i++) {
        temp.set(i, i, 1);
    }

    return temp;
}
