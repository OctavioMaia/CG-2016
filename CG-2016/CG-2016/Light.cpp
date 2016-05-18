#include "Light.h"

Light::Light()
{
	this->spotCUTOFF = 0.0;
	this->enableSpotLight = false;
	this->enableDiff = false;
	this->enableAmb = false;
	this->enableEmis = false;
	this->enableEspc = false;
}

void Light::apply(int light)
{
	glLightfv(GL_LIGHT0 + light, GL_POSITION, pos);
	if (enableAmb) {
		glLightfv(GL_LIGHT0 + light, GL_AMBIENT, amb);
	}
	if (enableDiff) {
		glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, diff);
	}
	if (enableEmis) {
		glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, emis);
	}
	if (enableEspc) {
		glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, espc);
	}
	if (enableSpotLight) {
		glLightfv(GL_LIGHT0 + light, GL_SPOT_DIRECTION, spotDir);
		glLightf(GL_LIGHT0 + light, GL_SPOT_CUTOFF, spotCUTOFF);
	}
}

void Light::setType(string t) { 
	if (t.compare("POINT")) {
		this->pos[3] = 1.0;
	}
	if (t.compare("DIRECTIONAL")) {
		this->pos[3] = 0.0;
	}
	if (t.compare("SPOTLIGHT")){
		this->pos[3] = 1.0;
	}
}
void Light::setPosX(float x) { this->pos[0] = x; }
void Light::setPosY(float y) { this->pos[1] = y; }
void Light::setPosZ(float z) { this->pos[2] = z; }

void Light::setAmb(float r, float g, float b)
{
	this->amb[0] = r;
	this->amb[1] = g;
	this->amb[2] = b;
	this->enableAmb = true;
}

void Light::setDiff(float r, float g, float b)
{
	this->diff[0] = r;
	this->diff[1] = g;
	this->diff[2] = b;
	this->enableDiff = true;
}

void Light::setEmis(float r, float g, float b)
{
	this->emis[0] = r;
	this->emis[1] = g;
	this->emis[2] = b;
	this->enableEmis = true;
}

void Light::setEspc(float r, float g, float b)
{
	this->espc[0] = r;
	this->espc[1] = g;
	this->espc[2] = b;
	this->enableEspc = true;
}

void Light::setSpotDir(float x, float y, float z, float angle)
{
	this->spotDir[0] = x;
	this->spotDir[1] = y;
	this->spotDir[2] = z;
	this->spotCUTOFF = angle;
	this->enableSpotLight = true;
}
