#ifndef ROTACAO_H
#define ROTACAO_H

//#include <vector.h>
#include <GL/glut.h>
using namespace std;


class Rotacao
{
private:
	float x;
	float y;
	float z;
	float time;
	;

public:
	Rotacao();
	Rotacao(float x, float y, float z, float time);

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setTime(float angle);

	float getX();
	float getY();
	float getZ();
	float getTime();
	void Apply(float time);

};
#endif