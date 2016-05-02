#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <catch.hpp>

SCENARIO("Matrix init", "[init]") 
{
	GIVEN("The number of rows and columns") 
	{
		auto rows = 3;
		auto columns = 4;
		WHEN("Create instansce of Matrix") 
		{
			Matrix<int> A(rows, columns);
			Matrix<int> B(rows*2+columns,columns*2+rows);
			Matrix<int> C;
			THEN("The number of rows and columns must be preserved") 
			{
				REQUIRE(A.get_count_row() == rows);
				REQUIRE(A.get_count_column() == columns);
				REQUIRE(B.get_count_row() == 2*rows+columns);
				REQUIRE(B.get_count_column() == 2*columns+rows);
				REQUIRE(C.get_count_row() == 0);
				REQUIRE(C.get_count_column() == 0);
			}
		}
	}
}
/*
SCENARIO("Matrix operator >>", "[Fill]") 
{
	std::ifstream input("A.txt");
	Matrix<int> A(2, 2);
	REQUIRE( input >> A );
	REQUIRE( A[0][0] == 2 );
	REQUIRE( A[0][1] == 3 );
	REQUIRE( A[1][0] == 2 );
	REQUIRE( A[1][1] == 1 );
}
SCENARIO("Matrix operator <<", "[out]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	std::ifstream("A.txt") >> A;
	fstream out; 
	out.open("out.txt");
	REQUIRE(out << A);
	std::ifstream("out.txt") >> B;
	out.close();
	REQUIRE(A==B);
}
SCENARIO("Matrix operator +", "[addition]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	Matrix<int> expected(2, 2);
	Matrix<int> result(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("B.txt") >> B;
	std::ifstream("A+B.txt") >> result;
	expected=A+B;
	REQUIRE(expected==result);
}
SCENARIO("Matrix operator -", "[subtraction]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	Matrix<int> expected(2, 2);
	Matrix<int> result(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("B.txt") >> B;
	std::ifstream("A-B.txt") >> result;
	expected=A-B;
	REQUIRE(expected==result);
}
SCENARIO("Matrix operator *", "[multiplication]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	Matrix<int> expected(2, 2);
	Matrix<int> result(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("B.txt") >> B;
	std::ifstream("AxB.txt") >> result;
	expected=A*B;
	REQUIRE(expected==result);
}
SCENARIO("Matrix operator [](int)", "[row]") 
{
	Matrix<int> A(2, 2);
	std::ifstream("A.txt") >> A;
	int* row = A[1];
	REQUIRE(row[0]==2);
	REQUIRE(row[1]==1);
}
SCENARIO("Matrix operator ==", "[comparison]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("A.txt") >> B;
	REQUIRE(A==B);
}
SCENARIO("Exception fill", "[fillerror]")
{
	bool flagBadA=false, flagBadB=false;
	bool flagA=false, flagB=false;
	Matrix<int> A(3, 2);
	Matrix<int> B(2, 2);
	try {
		std::ifstream("A.txt") >> A;
	}
	catch (FillException &ex) {
		flagA = true;
	}
	catch (MatrixException &ex) {
		flagBadA = true;
	}
	REQUIRE(flagA);
	REQUIRE(!flagBadA);
	try {
		std::ifstream("404.txt") >> A;
	}
	catch (FillException &ex) {
		flagB = true;
	}
	catch (MatrixException &ex) {
		flagBadB = true;
	}
	REQUIRE(flagB);
	REQUIRE(!flagBadB);
}
SCENARIO("Exception empty", "[emptyerror]")
{
	bool flagBad=false;
	bool flag=false;
	Matrix<int> A;
	try {
	int* row = A[0];
	}
	catch (EmptyException &ex) {
		flag = true;
	}
	catch (MatrixException &ex) {
		flagBad = true;
	}
	REQUIRE(flag);
	REQUIRE(!flagBad);
}
SCENARIO("Exception row's index", "[indexerror]")
{
	bool flagBad=false;
	bool flag=false;
	Matrix<int> A(2, 2);
	std::ifstream("A.txt") >> A;
	try {
	int* row = A[404];
	}
	catch (RowException &ex) {
		flag = true;
	}
	catch (MatrixException &ex) {
		flagBad = true;
	}
	REQUIRE(flag);
	REQUIRE(!flagBad);
}
SCENARIO("Exception size", "[sizerror]")
{
	bool flagBad=false;
	bool flag=false;
	Matrix<int> A(2, 2);
	Matrix<int> B(3, 3);
	try {
		A+B;
	}
	catch (SizeException &ex) {
		flag = true;
	}
	catch (MatrixException &ex) {
		flagBad = true;
	}
	REQUIRE(flag);
	REQUIRE(!flagBad);
}
SCENARIO("Exception size for *", "[sizerror1]")
{
	bool flagBad=false;
	bool flag=false;
	Matrix<int> A(2, 2);
	Matrix<int> B(3, 3);
	try {
		A*B;
	}
	catch (SizeException1 &ex) {
		flag = true;
	}
	catch (MatrixException &ex) {
		flagBad = true;
	}
	REQUIRE(flag);
	REQUIRE(!flagBad);
}
SCENARIO("Template test", "[Ttest]") 
{
	Matrix<short> Ashort(2, 2);
	Matrix<short> Bshort(2, 2);
	Matrix<short> expectedshort(2, 2);
	Matrix<short> resultshort(2, 2);
	std::ifstream("A.txt") >> Ashort;
	std::ifstream("B.txt") >> Bshort;
	std::ifstream("AxB.txt") >> resultshort;
	expectedshort=Ashort*Bshort;
	REQUIRE(expectedshort==resultshort);
	
	Matrix<long> Along(2, 2);
	Matrix<long> Blong(2, 2);
	Matrix<long> expectedlong(2, 2);
	Matrix<long> resultlong(2, 2);
	std::ifstream("A.txt") >> Along;
	std::ifstream("B.txt") >> Blong;
	std::ifstream("AxB.txt") >> resultlong;
	expectedlong=Along*Blong;
	REQUIRE(expectedlong==resultlong);
	
	Matrix<long long> Along_long(2, 2);
	Matrix<long long> Blong_long(2, 2);
	Matrix<long long> expectedlong_long(2, 2);
	Matrix<long long> resultlong_long(2, 2);
	std::ifstream("A.txt") >> Along_long;
	std::ifstream("B.txt") >> Blong_long;
	std::ifstream("AxB.txt") >> resultlong_long;
	expectedlong_long=Along_long*Blong_long;
	REQUIRE(expectedlong_long==resultlong_long);
	
	Matrix<double> Adouble(2, 2);
	Matrix<double> Bdouble(2, 2);
	Matrix<double> expecteddouble(2, 2);
	Matrix<double> resultdouble(2, 2);
	std::ifstream("A.txt") >> Adouble;
	std::ifstream("B.txt") >> Bdouble;
	std::ifstream("AxB.txt") >> resultdouble;
	expecteddouble=Adouble*Bdouble;
	REQUIRE(expecteddouble==resultdouble);
	
	Matrix<long double> Along_double(2, 2);
	Matrix<long double> Blong_double(2, 2);
	Matrix<long double> expectedlong_double(2, 2);
	Matrix<long double> resultlong_double(2, 2);
	std::ifstream("A.txt") >> Along_double;
	std::ifstream("B.txt") >> Blong_double;
	std::ifstream("AxB.txt") >> resultlong_double;
	expectedlong_double=Along_double*Blong_double;
	REQUIRE(expectedlong_double==resultlong_double);
	
	Matrix<float> Afloat(2, 2);
	Matrix<float> Bfloat(2, 2);
	Matrix<float> expectedfloat(2, 2);
	Matrix<float> resultfloat(2, 2);
	std::ifstream("A.txt") >> Afloat;
	std::ifstream("B.txt") >> Bfloat;
	std::ifstream("AxB.txt") >> resultfloat;
	expectedfloat=Afloat*Bfloat;
	REQUIRE(expectedfloat==resultfloat);
	
	Matrix<char> Achar(1, 1);
	Matrix<char> Bchar(1, 1);
	Matrix<char> expectedchar(1, 1);
	std::ifstream("A.txt") >> Achar;
	std::ifstream("B.txt") >> Bchar;
	expectedchar=Achar+Bchar;
	REQUIRE( expectedchar[0][0] == 'c' );
}
*/