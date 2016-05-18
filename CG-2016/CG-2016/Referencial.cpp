#include "Referencial.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"


Referencial::Referencial() {
	for (int i=0; i < SIZETRANSF; i++) { transformations[i] = NULL; }
}

void Referencial::addTransformation(Transformation t)
{
	int i = 0;
	for (; transformations[i] != NULL && i < SIZETRANSF; i++);
	if (i < SIZETRANSF && transformations[i] == NULL) {
		transformations[i] = t;
	}	
}


void Referencial::setFilhos(vector<Referencial> f) { filhos=f; }
void Referencial::setFiguras(vector<Figura> f) { figuras=f; }

void Referencial::addFilho(Referencial f) { filhos.push_back(f); }
void Referencial::addFigura(Figura f) { figuras.push_back(f); }

void Referencial::apply(float timePerFrame) {

	glPushMatrix();

	for (int i = 0; i < SIZETRANSF && transformations[i]!=NULL; i++) {
		switch (transformations[i]->type)
		{
			case TRANSLACAO: { Translacao  &t = (Translacao&)(transformations[i]->transl); t.Apply(500, timePerFrame); break; }
			case ROTACAO: { Rotacao  &r = (Rotacao&)(transformations[i]->rot); r.Apply(500, timePerFrame); break; }
			case ESCALA: { Escala &e = (Escala&)(transformations[i]->scale); e.Apply(500, timePerFrame); break; }
		default:
			break;
		}
	}

	glPushMatrix();

	for(int i=0; i<(figuras.size());i++){
		figuras[i].drawFigureArrays();
	}

	glPopMatrix();
	for(int i=0;i<(filhos.size());i++){
		filhos[i].apply(timePerFrame);
		
	}
	glPopMatrix();
	
}
vector<Referencial> Referencial::getFilhos() { return filhos; }
vector<Figura> Referencial::getFiguras() { return figuras; }
