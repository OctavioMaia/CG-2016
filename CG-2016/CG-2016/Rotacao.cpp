#include "Rotacao.h"


Rotacao::Rotacao() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	angle = 0.0;
}
Rotacao::Rotacao(float x, float y,float z, float angle ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = angle;
}

void Rotacao::setX(float x) { this->x = x; }
void Rotacao::setY(float y) { this->y = y; }
void Rotacao::setZ(float z) { this->z = z; }
void Rotacao::setAngle(float angle) { this->angle = angle; }

float Rotacao::getX() { return x; }
float Rotacao::getY() { return y; }
float Rotacao::getZ() { return z; }
float Rotacao::getAngle() { return angle; }

void Rotacao::Apply() { glRotatef(angle, x, y, z); }