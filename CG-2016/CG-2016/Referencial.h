#ifndef REFERENCIAL_H
#define REFERENCIAL_H

#include <vector>
#include "Transformation.h"
#include "Light.h"
#include "Escala.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Figura.h"


class Referencial
{
private:
	vector<Transformation> transformations;
	vector<Referencial> filhos;
	vector<Figura> figuras;

public:
	Referencial();

	void addTransformation(Transformation t);
	void setFilhos(vector<Referencial> f);
	void setFiguras(vector<Figura> f);

	void addFigura(Figura f);
	void addFilho(Referencial f);
	void apply(float timePerFrame);
	void resetGlReferncial();

	vector<Referencial> getFilhos();
	vector<Figura> getFiguras();

};
#endif