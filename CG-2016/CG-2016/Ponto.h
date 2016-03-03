#ifndef PONTO_H
#define PONTO_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ponto
{
private: double x, z, y;

public:
	Ponto();
	Ponto(double xx, double yy, double zz);

	double getx();
	double getz();
	double gety();

	void printFile(ofstream& file, string sep, bool enl);
	void printStdout(string sep, bool enl);

};

#endif