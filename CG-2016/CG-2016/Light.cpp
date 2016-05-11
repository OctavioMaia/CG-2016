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
	GLfloat pos[] = { posX,posY,posZ };
	glLightfv(GL_LIGHT0 + light, GL_POSITION, pos);
}

void Light::setPosX(float x) { this->posX = x; }
void Light::setPosY(float y) { this->posY = y; }
void Light::setPosZ(float z) { this->posZ = z; }
void Light::setType(string t) { this->type = t; }
