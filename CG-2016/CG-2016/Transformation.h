#pragma once
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"

#define TRANSLACAO 0
#define ROTACAO 1
#define ESCALA 2


typedef struct transformation {
	int type;
	union{
		Translacao transl;
		Rotacao rot;
		Escala scale;
	};
}*Transformation;

#endif