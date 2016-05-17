#include "Referencial.h"


Referencial::Referencial() {
}


void Referencial::addTransformation(Transformation t)
{
	this->transformations.push_back(t);
}

void Referencial::setFilhos(vector<Referencial> f) { filhos=f; }
void Referencial::setFiguras(vector<Figura> f) { figuras=f; }

void Referencial::addFilho(Referencial f) { filhos.push_back(f); }
void Referencial::addFigura(Figura f) { figuras.push_back(f); }

void Referencial::apply(float timePerFrame) {

	glPushMatrix();


	for (int i = 0; i < transformations.size(); i++) {
		switch (transformations[i].getType())
		{
			case 1: { Escala  &e = (Escala&)(transformations[i]); e.Apply(500, timePerFrame); break; }
			case 3: { Translacao  &t = (Translacao&)(transformations[i]); t.Apply(500, timePerFrame); break; }
			case 2: { Rotacao &r = (Rotacao&)(transformations[i]); r.Apply(500, timePerFrame); break; }
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
