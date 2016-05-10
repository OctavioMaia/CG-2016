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
	GLuint buffers[2];
	int fristTime;
	int nPontos;
	bool enableTexture;

	string file;
	string fileTexture;
	unsigned int textID;

	GLfloat diff[4];
	GLfloat emiss[4];
	GLfloat amb[4];
	GLfloat espct[4];

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
	void setTextureFile(string file);
	void setEnableLights(bool enable);
	void drawFigureArrays();
};
#endif