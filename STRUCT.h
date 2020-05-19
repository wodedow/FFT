#ifndef STRUCT
#define STRUCT
#include <complex>
struct Matrix {
	double** elem;
	int rows;
	int cols;
};

struct Array {
	double* elem;
	int length;
};

struct Matrixc {
	complex<double>** elem;
	int rows;
	int cols;
};

struct Arrayc {
	complex<double>* elem;
	int length;
};

#pragma once
#endif