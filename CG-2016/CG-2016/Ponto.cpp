#include "Ponto.h"
Ponto::Ponto() {}

Ponto::Ponto(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}

double Ponto::getx() { return x; }
double Ponto::getz() { return z; }
double Ponto::gety() { return y; }

void Ponto::printFile(ofstream& file, string sep, bool enl) {
	if (enl) {
		file << x << sep << y << sep << z << endl;
	}
	else {
		file << x << sep << y << sep << z;
	}

}

void Ponto::printStdout(string sep, bool enl) {
	if (enl) {
		cout << x << sep << y << sep << z << endl;
	}
	else {
		cout << x << sep << y << sep << z;
	}

}