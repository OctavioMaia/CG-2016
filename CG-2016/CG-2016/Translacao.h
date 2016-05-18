#ifndef TRANSLACAO_H
#define TRANSLACAO_H


#include "Ponto.h"
#include <GL\glew.h>
#pragma comment(lib, "glew32.lib")
#include <vector>

using namespace std;


class Translacao
{
private:
	int nPontos;
	Ponto points[100];
	GLuint buffersTranslate[1];
	float* catmullVertex;
	float tpGlobal;
	float time;
	bool flag;
	
	void getCatmullRomPoint(float t, int *indices, float *res);
	void getCatmullDerivatePoint(float t, int* indices, float *res);

public:
	Translacao();
	Translacao(float t);

	void setTime(float x);
	float getTime();
	void addPoint(Ponto p);
	void getGlobalCatmullRomPoint(float gt, float *res);
	void getGlobalCatmullDerivatePoint(float gt, float* res);
	void Apply(int tess, float timePerFrame);

};
#endif