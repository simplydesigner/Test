#include <iostream>
#include <fstream>
#include <cstring>
#include "MatrixException.h"

using namespace std;

template<class A>
class Matrix {
public:
    Matrix();

    Matrix(int a, int b);

    Matrix(const Matrix &matrix);

    ~Matrix();

    void print() const;

    int get_count_row() const;

    int get_count_column() const;

    int get_element(int index1, int index2) const;

    void create_matrix_from_file(ifstream &);

    Matrix operator+(const Matrix &matrix) const;

    void operator=(const Matrix &matrix);

    Matrix operator*(const Matrix &matrix) const;

    const A *operator[](int) const;

    bool is_empty() const;

    void create_matrix(int n, int m);

    bool operator==(const Matrix &);

    template<class U>
    friend istream &operator>>(istream &input, Matrix<U> &matr);

    template<class U>
    friend ostream &operator<<(ostream &os, Matrix<U> &temp);

private:
    A **array;
    int count_row;
    int count_column;
};

template<class A>
Matrix<A>::Matrix() :
        array(NULL),
        count_row(0),
        count_column(0) { }

template<class A>
Matrix<A>::Matrix(int a, int b) {
    create_matrix(a, b);
}

template<class A>
Matrix<A>::Matrix(const Matrix &matrix) :
        count_row(matrix.count_row),
        count_column(matrix.count_column) {

    array = new int *[count_row];

    for (int i = 0; i < count_row; ++i) {
        array[i] = new int[count_column];
        for (int j = 0; j < count_column; ++j) {
            array[i][j] = matrix.array[i][j];
        }
    }
}

template<class A>
Matrix<A>::~Matrix() {
    if (array != NULL) {
        for (int i = 0; i < count_row; i++) {
            delete[] array[i];
        }
        delete[] array;
    }
}

template<class A>
int Matrix<A>::get_count_row() const {
    return count_row;
}

template<class A>
int Matrix<A>::get_count_column() const {
    return count_column;
}

template<class A>
int Matrix<A>::get_element(int index1, int index2) const {
    try {
        if (index1 >= count_row || index2 >= count_column || index1 < 0 || index2 < 0) {
            MatrixExceptionOutOfRange tmp;
            throw tmp;
        }
    } catch (MatrixException &tmp) {
        tmp.exception();
    }

}

template<class A>
void Matrix<A>::print() const {
    for (int i = 0; i < count_row; ++i) {
        for (int j = 0; j < count_column; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

template<class A>
bool Matrix<A>::is_empty() const {
    if (count_row == 0 && count_column == 0)
        return true;
    else false;
}

template<class A>
void Matrix<A>::create_matrix(int n, int m) {
    count_row = n;
    count_column = m;
    array = new int *[count_row];

    for (int i = 0; i < count_row; ++i) {
        array[i] = new int[count_column];
    }
}

template<class A>
void Matrix<A>::create_matrix_from_file(ifstream &file) {
    try {
        if (!file.is_open()) {
            MatrixExceptionFileOpen tmp;
            throw tmp;
        }
    } catch (MatrixExceptionFileOpen &tmp) {
        tmp.exception();
    }
    int n, m;
    file >> n;
    file >> m;
    create_matrix(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            file >> array[i][j];
        }
    }
    file.clear();
    file.seekg(0, ios::beg);
}

template<class A>
Matrix<A> Matrix<A>::operator+(const Matrix<A> &matrix) const {
    Matrix<A> c;
    try {
        if (count_column != matrix.count_column && count_row != matrix.count_row) {
            MatrixExceptionNotEqual tmp;
            throw tmp;
        }
    } catch (MatrixExceptionNotEqual &tmp) {
        tmp.exception();
    }
    c.create_matrix(count_row, count_column);
    for (int i = 0; i < count_row; ++i) {
        for (int j = 0; j < count_column; ++j) {
            c.array[i][j] = matrix.array[i][j] + array[i][j];
        }
    }
    return c;
}

template<class A>
Matrix<A> Matrix<A>::operator*(const Matrix<A> &matrix) const {
    Matrix<A> c;
    try {
        if (count_column != matrix.count_row) {
            MatrixExceptionNotEqual tmp;
            throw tmp;
        }
    } catch (MatrixExceptionNotEqual &tmp) {
        tmp.exception();
    }

    c.create_matrix(count_row, matrix.count_column);
    for (int l = 0; l < matrix.count_column; ++l) {
        for (int i = 0; i < count_row; ++i) {
            int b = 0;
            for (int j = 0, k = 0; j < count_column; ++j, ++k) {
                b += array[i][j] * matrix.array[k][i];
            }
            c.array[i][l] = b;
        }
    }
    return c;
}

template<class A>
void Matrix<A>::operator=(const Matrix<A> &matrix) {
    count_row = matrix.count_row;
    count_column = matrix.count_column;

    create_matrix(count_row, count_column);
    for (int i = 0; i < count_row; ++i) {
        for (int j = 0; j < count_column; ++j) {
            array[i][j] = matrix.array[i][j];
        }
    }
}

template<class A>
const A *Matrix<A>::operator[](int index) const {
    try{
        if (index >= count_row || index < 0) {
            MatrixExceptionOutOfRange tmp;
            throw tmp;
        }
    } catch(MatrixExceptionOutOfRange &tmp) {
        tmp.exception();
    }
    return array[index];
}

template<class A>
bool Matrix<A>::operator==(const Matrix &matr) {
    if (count_row != matr.count_row || count_column != matr.count_column) {
        return false;
    }

    for (int i = 0; i < count_row; i++) {
        for (int j = 0; j < count_column; j++) {
            if (array[i][j] != matr.array[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template<class U>
ostream &operator<<(ostream &os, Matrix<U> &temp) {
    for (int i = 0; i < temp.count_row; ++i) {
        for (int j = 0; j < temp.count_column; ++j) {
            os << temp.array[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

template<class U>
istream &operator>>(istream &input, Matrix<U> &matr) {
    for (int i = 0; i < matr.count_row; i++) {
        for (int j = 0; j < matr.count_column; j++) {
            if(input >> matr.array[i][j]){
            }
        }
    }
    return input;
}
