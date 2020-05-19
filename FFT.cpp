#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> doublec;
const double pi = 3.1415926;

struct Array {
	double* elem;
	int length;
};
struct Arrayc {
	doublec* elem;
	int length;
};
bool Init_Array(Array& array,int length) {
	array.elem = new double[length];
	array.length = length;
	return true;
}
bool Init_Arrayc(Arrayc& array, int length) {
	array.elem = new doublec[length];
	array.length = length;
	return true;
}

bool FFT(Arrayc& array) {
	int m = (int)log2(array.length);
	int n = array.length / 2;
	
	if (n != 1) {
		Arrayc arrayx;
		Arrayc arrayy;
		Init_Arrayc(arrayx, n);
		Init_Arrayc(arrayy, n);
		for (int i = 0; i < n; i++) {
			arrayx.elem[i] = array.elem[2 * i];
			arrayy.elem[i] = array.elem[2 * i + 1];
		}
		FFT(arrayx);
		cout << "xTimes++" << endl;
		FFT(arrayy);
		cout << "yTimes++" << endl;

		for (int k = 0; k < n; k++) {
			doublec gk(0.0);
			doublec hk(0.0);
			for (int j = 0; j < n; j++) {
				doublec ck(cos(-2 * pi * j * k / n), sin(-2 * pi * j * k / n));
				gk += arrayx.elem[j] * ck;
				hk += arrayy.elem[j] * ck;
			}

			doublec dk(cos(-pi * k / n), sin(-pi * k / n));
			array.elem[k] = gk + dk * hk;
			array.elem[k + n] = gk - dk * hk;
		}
	}
	
	cout << "Times++" << endl;

	return true;
}

int main() {
	Arrayc xn;
	int size = 8;
	Init_Arrayc(xn, size);
	for (int i = 0; i < size; i++) {
		xn.elem[i] = (i);
	}

	FFT(xn);

	for (int i = 0; i < xn.length; i++) {
		cout << "(" << xn.elem[i].real() << ", " << xn.elem[i].imag() << ")  ";
	}

	return 1;
}