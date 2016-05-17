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

void Ponto::setX(double x) { this->x = x; }
void Ponto::setY(double y) { this->y = y; }
void Ponto::setZ(double z) { this->z = z; }

void Ponto::printFile(ofstream& file, string sep, bool enl) {
	if (enl) {
		file << x << sep << y << sep << z << endl;
	}
	else {
		file << x << sep << y << sep << z;
	}

}

void Ponto::printFile2D(ofstream& file, string sep, bool enl) {
	if (enl) {
		file << x << sep << y << endl;
	}
	else {
		file << x << sep << y;
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

double Ponto::getXYZ(int pos) {
	
	if (pos == 0) { return x; }
	else
	{
		if (pos == 1) { return y; }
		else {
			return z;
		}
	}
}