#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <GL\glut.h>
#include <string>

using namespace std;

class Light 
{
private:
	float posX;
	float posY;
	float posZ;
	string type;

public:
	Light();
	
	void apply();

	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
	void setType(string t);
};

#endif // LIGHT
