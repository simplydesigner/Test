//
// Created by magomed on 13.04.16.
//

#ifndef MATRIX_MATRIXEXCEPTION_H
#define MATRIX_MATRIXEXCEPTION_H

#include <iostream>

using namespace std;

class MatrixException {
public:
    virtual void exception() = 0;
    virtual ~MatrixException();
};

class MatrixExceptionOutOfRange: public MatrixException {
public:
    void exception();
};

class MatrixExceptionFileOpen: public MatrixException {
public:
    void exception();
};

class MatrixExceptionNotEqual: public MatrixException {
public:
    void exception();
};


MatrixException::~MatrixException() {}

void MatrixExceptionOutOfRange::exception() {
    cout << "Error: Out of Range\n";
}


void MatrixExceptionFileOpen::exception() {
    cout << "Error: File not is open\n";
}


void MatrixExceptionNotEqual::exception() {
    cout << "Error: Size not equal\n";
}

#endif //MATRIX_MATRIXEXCEPTION_H

