#ifndef FIGURA_H
#define FIGURA_H

#include "Ponto.h"
#include "Color.h"

#include <GL/glew.h>
#include <GL/glut.h>




#pragma comment(lib, "glew32.lib")

using namespace std;

class Figura
{
private:
	string file;
	int nPontos;
	vector<Ponto> listaPontos;
	vector<Color> listaCores;
	double listafloat[7200];
	int pos;

public:
	Figura(string fileName, int n);

	void addPonto(double x, double y, double z);
	void addColor(double r, double g, double b);

	Ponto getP(int position);
	Color getC(int position);

	int gerarCores();

	void drawFigure(bool multiColor);
	void drawFigureArrays();
};
#endif