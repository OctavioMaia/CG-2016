#include "Translacao.h"


Translacao::Translacao() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
Translacao::Translacao(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Translacao::setX(float x) { this->x = x; }
void Translacao::setY(float y) { this->y = y; }
void Translacao::setZ(float z) { this->z = z; }

float Translacao::getX() { return x; }
float Translacao::getY() { return y; }
float Translacao::getZ() { return z; }

void Translacao::Apply() { glTranslatef(x, y, z); }