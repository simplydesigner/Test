
#include "MatrixException.h"

void MatrixExceptionOutOfRange::exception() {
    cout << "Error: Out of Range\n";
}


void MatrixExceptionFileOpen::exception() {
    cout << "Error: File not is open\n";
}


void MatrixExceptionNotEqual::exception() {
    cout << "Error: Size not equal\n";
}


