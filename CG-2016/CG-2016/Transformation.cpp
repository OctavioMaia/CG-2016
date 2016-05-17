#include "Transformation.h"



Transformation::Transformation()
{
}

Transformation::Transformation(int type) {
	this->type = type;
}

int Transformation::getType() {
	return this->type;
}

