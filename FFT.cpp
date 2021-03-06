#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> doublec;
const double pi = 3.1415926535;

struct Array {
	double* elem;
	int length;
};
struct Arrayc {
	doublec* elem;
	int length;
};
bool Init_Array(Array& array, int length) {
	array.elem = new double[length];
	array.length = length;
	return true;
}
bool Init_Arrayc(Arrayc& array, int length) {
	array.elem = new doublec[length];
	array.length = length;
	return true;
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
		memset(&arrayx, 0, sizeof(arrayx));
		memset(&arrayy, 0, sizeof(arrayy));
	}

	//cout << "Times++" << endl;

	return arrayz;
}

Arrayc IFFT(Arrayc array) {
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

		doublec nn(array.length);
		for (int k = 0; k < n; k++) {
			doublec gk(0.0);
			doublec hk(0.0);
			for (int j = 0; j < n; j++) {
				doublec ck(cos(2 * pi * j * k / n), sin(2 * pi * j * k / n));
				gk += arrayx.elem[j] * ck;
				hk += arrayy.elem[j] * ck;
			}

			doublec dk(cos(pi * k / n), sin(pi * k / n));
			arrayz.elem[k] = (gk + dk * hk) / nn;
			arrayz.elem[k + n] = (gk - dk * hk) / nn;
		}
		memset(&arrayx, 0, sizeof(arrayx));
		memset(&arrayy, 0, sizeof(arrayy));
	}

	//cout << "Times++" << endl;
	return arrayz;
}

int main() {
	Arrayc xn;
	int length = 64;
	Init_Arrayc(xn, length);
	for (int i = 0; i < length; i++) {
		xn.elem[i] = (i);
	}
	Arrayc yn;
	yn = FFT(xn);

	for (int i = 0; i < yn.length; i++) {
		if (abs(yn.elem[i]) < 1e-4) {
			cout << "(" << "0" << ", " << "0" << ")" << endl;
		}
		else if (abs(yn.elem[i].imag()) < 1e-4) {
			cout << "(" << yn.elem[i].real() << ", " << "0" << ")" << endl;
		}
		else {
			cout << "(" << yn.elem[i].real() << ", " << yn.elem[i].imag() << ")" << endl;
		}
	}

	Arrayc zn;
	zn = IFFT(yn);
	for (int i = 0; i < zn.length; i++) {
		if (abs(zn.elem[i]) < 1e-4) {
			cout << "(" << "0" << ", " << "0" << ")" << endl;
		}
		else if (abs(zn.elem[i].imag()) < 1e-4) {
			cout << "(" << yn.elem[i].real() << ", " << "0" << ")" << endl;
		}
		else {
			cout << "(" << yn.elem[i].real() << ", " << yn.elem[i].imag() << ")" << endl;
		}
	}

	return 1;
}