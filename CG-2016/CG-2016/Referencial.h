#ifndef REFERENCIAL_H
#define REFERENCIAL_H

#include <vector>
#include "Escala.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Figura.h"
#include <GL/glut.h>
//using namespace std;


class Referencial
{
private:
	Escala escala;
	Translacao translacao;
	Rotacao rotacao;
	vector<Referencial> filhos;
	vector<Figura> figuras;

public:
	Referencial();
	Referencial(Escala e,Translacao t,Rotacao r);

	void setEscala(Escala e);
	void setTranslacao(Translacao t);
	void setRotacao(Rotacao r);
	void setFilhos(vector<Referencial> f);
	void setFiguras(vector<Figura> f);

	void addFigura(Figura f);
	void addFilho(Referencial f);
	void apply();
	void resetGlReferncial();

	Escala getEscala();
	Translacao getTranslacao();
	Rotacao getRotacao();
	vector<Referencial> getFilhos();
	vector<Figura> getFiguras();

};
#endif