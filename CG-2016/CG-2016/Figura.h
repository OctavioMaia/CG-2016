#ifndef FIGURA_H
#define FIGURA_H

#include "Ponto.h"
#include "Color.h"
#include <GL/glut.h>

using namespace std;

class Figura
{
private:
	string file;
	int nPontos;
	vector<Ponto> listaPontos;
	vector<Color> listaCores;

public:
	Figura(string fileName, int n);

	void addPonto(double x, double y, double z);
	void addColor(double r, double g, double b);

	Ponto getP(int position);
	Color getC(int position);

	int gerarCores();

	void drawFigure(bool multiColor);
};
#endif