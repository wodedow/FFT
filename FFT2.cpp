#include <iostream>
#include <complex>

using namespace std;
typedef complex<double> doublec;
const double pi = 3.1415926;

const int M = 4;
const int N = 8;

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
	doublec** elem;
	int rows;
	int cols;
};
struct Arrayc {
	doublec* elem;
	int length;
};

bool Init_Arrayc(Arrayc& array, int length) {
	array.elem = new doublec[length];
	array.length = length;
	return true;
}

bool Init_Matrixc(Matrixc& matrix, int rows, int cols) {
	matrix.rows = rows;
	matrix.cols = cols;
	matrix.elem = new doublec * [rows];
	for (int i = 0; i < rows; i++) {
		matrix.elem[i] = new doublec[cols];
	}
	return true;
}

Matrixc Translate(Matrixc mat) {
	Matrixc matr;
	matr.cols = mat.rows;
	matr.rows = mat.cols;
	matr.elem = new doublec * [mat.cols];
	for (int i = 0; i < mat.cols; i++) {
		matr.elem[i] = new doublec[mat.rows];
	}

	for (int i = 0; i < matr.rows; i++) {
		for (int j = 0; j < matr.cols; j++) {
			matr.elem[i][j] = mat.elem[j][i];
		}
	}

	return matr;
}

Arrayc Arr2Arrayc(doublec* img, int length) {
	Arrayc iimg;
	Init_Arrayc(iimg, length);
	for (int i = 0; i < length; i++) {
		iimg.elem[i] = img[i];
	}
	return iimg;
}

doublec* Arrc2Array(Arrayc iimg, int length) {
	doublec* img;
	img = new doublec[length];
	for (int i = 0; i < length; i++) {
		img[i] = iimg.elem[i];
	}
	return img;
}

Arrayc FFT(Arrayc array) {
	int m = (int)log2(array.length);
	int n = array.length / 2;

	Arrayc arrayz;
	Init_Arrayc(arrayz, array.length);

	if (n != 0) {
		Arrayc arrayx;
		Arrayc arrayy;

		Init_Arrayc(arrayx, n);
		Init_Arrayc(arrayy, n);
		for (int i = 0; i < n; i++) {
			arrayx.elem[i] = array.elem[2 * i];
			arrayy.elem[i] = array.elem[2 * i + 1];
		}
		Arrayc arrayxx = FFT(arrayx);
		//cout << "xTimes++" << endl;
		Arrayc arrayyy = FFT(arrayy);
		//cout << "yTimes++" << endl;

		for (int k = 0; k < n; k++) {
			doublec gk(0.0);
			doublec hk(0.0);
			for (int j = 0; j < n; j++) {
				doublec ck(cos(-2 * pi * j * k / n), sin(-2 * pi * j * k / n));
				gk += arrayx.elem[j] * ck;
				hk += arrayy.elem[j] * ck;
			}

			doublec dk(cos(-pi * k / n), sin(-pi * k / n));
			arrayz.elem[k] = gk + dk * hk;
			arrayz.elem[k + n] = gk - dk * hk;
		}
	}

	return arrayz;
}

Matrixc FFT2(Matrixc img) {
	Matrixc imgg;
	Init_Matrixc(imgg, img.rows, img.cols);

	for (int i = 0; i < M; i++) {
		Arrayc iimg = FFT(Arr2Arrayc(img.elem[i], img.cols));
		imgg.elem[i] = Arrc2Array(iimg, img.cols);
	}
	Matrixc imggg;
	imggg = Translate(imgg);
	Matrixc imgggg;
	Init_Matrixc(imgggg, imggg.rows, imggg.cols);

	for (int j = 0; j < N; j++) {
		Arrayc iiimg = FFT(Arr2Arrayc(imggg.elem[j], imggg.cols));
		imgggg.elem[j] = Arrc2Array(iiimg, imggg.cols);
	}
	Matrixc iimgg = Translate(imgggg);

	memset(&imgg, 0, sizeof(imgg));
	memset(&imggg, 0, sizeof(imggg));
	memset(&imgggg, 0, sizeof(imgggg));
	return iimgg;
}

int main() {
	Matrixc Img;
	Init_Matrixc(Img, M, N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int p = i * N + j;
			Img.elem[i][j] = (p);
		}
	}

	Matrixc Img_out;
	Img_out = FFT2(Img);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (abs(Img_out.elem[i][j]) < 1e-4) {
				cout << "(" << "0" << ", " << "0" << ")" << endl;
			}
			else {
				cout << "(" << Img_out.elem[i][j].real() << ", " << Img_out.elem[i][j].imag() << ")" << endl;
			}
		}
	}

	return 1;
}
