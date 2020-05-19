#include <iostream>
#include <complex>
#include <math.h>

using namespace std;

const int M = 8;
const int N = 16;

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

int* swap(int j, int m) {
	int* a = new int[m];
	for (int i = 0; i < m; i++) {
		a[i] = 0;
	}

	for (int i = m - 1; i >= 0; i--) {
		a[i] = j % 2;
		j = j / 2;
		if (j == 0)
			break;
	}
	return a;
}

Matrixc Translate(Matrixc mat) {
	Matrixc matr;
	matr.cols = mat.rows;
	matr.rows = mat.cols;
	matr.elem = new complex<double> * [mat.cols];
	for (int i = 0; i < mat.cols; i++) {
		matr.elem[i] = new complex<double>[mat.rows];
	}

	for (int i = 0; i < matr.rows; i++) {
		for (int j = 0; j < matr.cols; j++) {
			matr.elem[i][j] = mat.elem[j][i];
		}
	}

	return matr;
}

template<typename T> complex<double>* FFT(T& arr) {
	
}

Matrixc FFT2(Matrix& img) {
	Matrixc imgg;
	imgg.rows = img.rows;
	imgg.cols = img.cols;

	for (int i = 0; i < M; i++) {
		imgg.elem[i]=FFT<double*>(img.elem[i]);
	}
	Matrixc imggg;
	imggg = Translate(imgg);
	Matrixc imgggg;
	imgggg.rows = imggg.rows;
	imgggg.cols = imggg.cols;

	for (int j = 0; j < N; j++) {
		imgggg.elem[j] = FFT<complex<double>*>(imggg.elem[j]);
	}
	imgg = Translate(imgggg);

	memset(&imggg, 0, sizeof(imggg));
	memset(&imgggg, 0, sizeof(imgggg));
	return imgg;
}

//int main() {
//	Matrix Img;
//	Img.rows = M;
//	Img.cols = N;
//	Matrixc Img_out;
//	Img_out = FFT2(Img);
//
//	return 1;
//}
