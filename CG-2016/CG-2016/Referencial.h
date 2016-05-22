#ifndef REFERENCIAL_H
#define REFERENCIAL_H

#include <vector>
#include "Transformation.h"
#include "Light.h"
#include "Figura.h"


#define SIZETRANSF 10 

class Referencial
{
private:

	Transformation  transformations[SIZETRANSF];
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

	vector<Referencial> getFilhos();
	vector<Figura> getFiguras();

};
#endif