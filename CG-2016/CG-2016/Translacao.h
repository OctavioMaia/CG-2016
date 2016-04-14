#ifndef TRANSLACAO_H
#define TRANSLACAO_H

//#include <vector.h>
#include <GL/glut.h>
using namespace std;


class Translacao
{
private:
	float x;
	float y;
	float z;

public:
	Translacao();
	Translacao(float x, float y, float z);

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getX();
	float getY();
	float getZ();
	void Apply();

};
#endif