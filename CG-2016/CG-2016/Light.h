#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <stdlib.h>

#include <GL\glew.h>
#include <GL\glut.h>
#include <string>

using namespace std;

class Light
{
private:
	GLfloat pos[4] = { 0.0,0.0,0.0,0.0 }; // por defenição a luz é direcional
	GLfloat spotDir[3];
	GLfloat amb[3];
	GLfloat diff[3];
	GLfloat espc[3];
	GLfloat emis[3];

	float spotCUTOFF;
	
	bool enableSpotLight;
	bool enableDiff;
	bool enableEmis;
	bool enableAmb;
	bool enableEspc;
public:
	Light();

	void apply(int light);

	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
	void setType(string t);

	void setAmb(float r, float g, float b);
	void setDiff(float r, float g, float b);
	void setEmis(float r, float g, float b);
	void setEspc(float r, float g, float b);

	void setSpotDir(float x, float y, float z, float angle);
};

#endif // LIGHT