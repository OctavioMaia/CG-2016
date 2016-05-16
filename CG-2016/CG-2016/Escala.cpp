#include "Escala.h"



Escala::Escala() {
	x = 1.0;
	y = 1.0;
	z = 1.0;
}
Escala::Escala(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Escala::Escala(float value) {
	x = value;
	y = value;
	z = value;
}

void Escala::setX(float x) { this->x = x; }
void Escala::setY(float y) { this->y = y; }
void Escala::setZ(float z) { this->z = z; }
void Escala::setAll(float value) {
	x = value;
	y = value;
	z = value;
}

float Escala::getX() { return x; }
float Escala::getY() { return y; }
float Escala::getZ() { return z; }

void Escala::Apply(int tess, float timePerFrame) { glScalef(x, y, z); }