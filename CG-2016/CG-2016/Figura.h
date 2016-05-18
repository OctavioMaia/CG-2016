#ifndef FIGURA_H
#define FIGURA_H

#include "Ponto.h"
#include <IL\il.h>

#include <GL/glew.h>
#include <GL/glut.h>

#pragma comment(lib, "glew32.lib")

using namespace std;

class Figura
{
private:
	GLuint buffers[3];
	GLuint textID;
	int fristTime;
	int nPontos;
	bool enableTexture;

	string file;
	string fileTexture;

	GLfloat diff[3];
	GLfloat emis[3];
	GLfloat amb[3];
	GLfloat espc[3];

	bool enableDiff;
	bool enableEmis;
	bool enableAmb;
	bool enableEspc;

	float* listaPontos;
	int posPontos;
	float* normais;
	int posNormais;
	float* texturas;
	int posTexturas;

	void loadImageTexture();

	

public:
	Figura(string fileName, string textF, int n, bool enableTexture);

	void addPonto(double x, double y, double z);
	void addNormal(float x,float y, float z);
	void addTextur(float x, float y);

	void setDiff(float r, float g, float b);
	void setAmb(float r, float g, float b);
	void setEmis(float r, float g, float b);
	void setEsp(float r, float g, float b);
	void setTextureFile(string file);
	void drawFigureArrays();
};
#endif