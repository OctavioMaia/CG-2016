#include "Rotacao.h"

Rotacao::Rotacao() {
	x = 0.0;
	y = 1.0;
	z = 0.0;
	time = 0.0;
	localAngle = 0.0;
}
Rotacao::Rotacao(float x, float y,float z, float t ) {
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

void Rotacao::Apply(float timestep) {
	float angle;
	if (this->time == 0) {
		 angle = 0;
	}
	else {
		angle = (360.0*timestep) / time;
	}
	
	this->localAngle = this->localAngle + angle;
	glRotatef(localAngle,x,y,z);
}