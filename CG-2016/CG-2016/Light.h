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
	string type;
	float posX;
	float posY;
	float posZ;
	GLfloat amb[4] = { 1.0, 1.0, 1.0 };
	GLfloat diff[4] = { 1.0, 1.0, 1.0 };
	;
public:
	Light();

	void apply(int light);

	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
	void setType(string t);

	void setAmb(float r, float g, float b);
	void setDiff(float r, float g, float b);
};

#endif // LIGHT
