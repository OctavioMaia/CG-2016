#pragma once
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Transformation
{
public:
	Transformation();
	virtual void  Apply(int tess, float timePerFrame);
};

#endif