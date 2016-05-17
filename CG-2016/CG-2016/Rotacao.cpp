#include "Rotacao.h"

#include <stdio.h>

int an = 0;
Rotacao::Rotacao() {
	Transformation(2);
	x = 0.0;
	y = 1.0;
	z = 0.0;
	time = 0.0;
	localAngle = 0.0;
}
Rotacao::Rotacao(float x, float y,float z, float t ) {
	Transformation(2);
	this->x = x;
	this->y = y;
	this->z = z;
	this->time = t;
}

void Rotacao::setX(float x) { this->x = x; }
void Rotacao::setY(float y) { this->y = y; }
void Rotacao::setZ(float z) { this->z = z; }
void Rotacao::setTime(float time) { this->time = time; }

float Rotacao::getX() { return x; }
float Rotacao::getY() { return y; }
float Rotacao::getZ() { return z; }
float Rotacao::getTime() { return time; }

void Rotacao::Apply(int tess, float timePerFrame) {
	float angle;
	if (this->time == 0) {
		 angle = 0;
	}
	else {
		angle = (360.0*timePerFrame) / (1.0/time);
	}
	
	this->localAngle += angle;

	glRotatef(localAngle,x,y,z);

}