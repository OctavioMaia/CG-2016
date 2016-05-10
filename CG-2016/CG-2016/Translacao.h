#ifndef TRANSLACAO_H
#define TRANSLACAO_H


#include "Ponto.h"
#include <GL\glew.h>
#pragma comment(lib, "glew32.lib")
#include <vector>

using namespace std;


class Translacao : public Transformation
{
private:
	float time;
	vector<Ponto> points;
	bool flag;
	float* catmullVertex;
	GLuint buffersTranslate[1];
	float tpGlobal;

	void getCatmullRomPoint(float t, int *indices, float *res);
	void Translacao::getCatmullDerivatePoint(float t, int* indices, float *res);

public:
	Translacao();
	Translacao(float t);

	void setTime(float x);

	float getTime();

	void addPoint(Ponto p);

	void getGlobalCatmullRomPoint(float gt, float *res);

	void Translacao::getGlobalCatmullDerivatePoint(float gt, float* res);

	void Apply(int tess, float timePerFrame);

};
#endif