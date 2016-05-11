#ifndef ESCALA_H
#define ESCALA_H

#include "Transformation.h"
#include <GL\glew.h>
#include <GL/glut.h>
using namespace std;


class Escala : public Transformation
{
private:
	float x;
	float y;
	float z;

	;

public:
	Escala();
	Escala(float value);
	Escala(float x, float y, float z);

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setAll(float value);


	float getX();
	float getY();
	float getZ();
	void Apply();

};
#endif