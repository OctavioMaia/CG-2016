#include "Escala.h"


Escala::Escala() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
Escala::Escala(float x, float y, float z) {
	x = x;
	y = y;
	z = z;
}
Escala::Escala(float value) {
	x = value;
	y = value;
	z = value;
}

void Escala::setX(float x) { x = x; }
void Escala::setY(float y) { y = y; }
void Escala::setZ(float z) { z = z; }
void Escala::setAll(float value) {
	x = value;
	y = value;
	z = value;
}

float Escala::getX() { return x; }
float Escala::getY() { return y; }
float Escala::getZ() { return z; }

void Escala::Apply() { glScalef(x, y, z); }