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

	glLightfv(GL_LIGHT0 + light, GL_POSITION, pos);
	glLightfv(GL_LIGHT0 + light, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, diff);
}

void Light::setPosX(float x) { this->posX = x; }
void Light::setPosY(float y) { this->posY = y; }
void Light::setPosZ(float z) { this->posZ = z; }
void Light::setType(string t) { this->type = t; }

void Light::setAmb(float r, float g, float b)
{
	this->amb[0] = r;
	this->amb[1] = g;
	this->amb[2] = b;
}

void Light::setDiff(float r, float g, float b)
{
	this->diff[0] = r;
	this->diff[1] = g;
	this->diff[2] = b;
}
