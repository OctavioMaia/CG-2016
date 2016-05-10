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
	GLuint buffers[1];
	int fristTime;
	string file;
	int nPontos;
	vector<Ponto> listaPontos;
	
	float* listafloat;
	int pos;
	//luzes e texturas
	GLfloat diff[4];
	float* normais;
	int posNormais;
	float* texturas;
	int posTexturas;

public:
	Figura(string fileName, int n);

	void addPonto(double x, double y, double z);
	void addColor(double r, double g, double b);

	void addNormal(float x,float y, float z);
	void addTextur(float x, float y);

	Ponto getP(int position);
	Color getC(int position);

	int gerarCores();

	void drawFigure(bool multiColor);
	void drawFigureArrays();
};
#endif