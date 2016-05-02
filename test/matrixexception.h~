#pragma once
#include <string>
using namespace std;
class MatrixException
{
public:
  MatrixException(string msg): msg(msg) {};
private:
  string msg;
};

class SizeException: public MatrixException 
{
public:
  SizeException(): MatrixException("Sizes don't match") {};
private:
  string msg;
};
class SizeException1: public MatrixException 
{
public:
  SizeException1(): MatrixException("Sizes don't match for *") {};
private:
  string msg;
};
class EmptyException: public MatrixException 
{
public:
  EmptyException(): MatrixException("Matrix empty") {};
private:
  string msg;
};
class FillException: public MatrixException 
{
public:
  FillException(): MatrixException("Fill error") {};
private:
  string msg;
};
class RowException: public MatrixException 
{
public:
  RowException(): MatrixException("Row's index") {};
private:
  string msg;
};
