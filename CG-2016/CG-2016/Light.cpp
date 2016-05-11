#include "Light.h"

Light::Light()
{
	this->posX = 0.0;
	this->posY = 0.0;
	this->posZ = 0.0;
	this->type = "POINT";
}

void Light::apply(int light)
{
	GLfloat pos[4] = { posX,posY,posZ,0.0 };
	GLfloat amb[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat diff[4] = { 0.0, 1.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0 + light, GL_POSITION, pos);
	glLightfv(GL_LIGHT0 + light, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, diff);
}

void Light::setPosX(float x) { this->posX = x; }
void Light::setPosY(float y) { this->posY = y; }
void Light::setPosZ(float z) { this->posZ = z; }
void Light::setType(string t) { this->type = t; }
