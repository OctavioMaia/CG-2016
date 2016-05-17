#pragma once
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
class Transformation
{
private:
	int type;
public:
	Transformation();
	Transformation(int type);
	int getType();
};


#endif