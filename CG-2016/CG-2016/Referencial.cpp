#include "Referencial.h"


Referencial::Referencial() {
	escala=Escala::Escala();
	translacao=Translacao::Translacao();
	rotacao=Rotacao::Rotacao();
}

Referencial::Referencial(Escala e, Translacao t, Rotacao r) {
	escala = e;
	translacao = t;
	rotacao = r;
}

void Referencial::setEscala(Escala e) { escala = e; }
void Referencial::setTranslacao(Translacao t) { translacao = t; }
void Referencial::setRotacao(Rotacao r) { rotacao = r; }
void Referencial::setFilhos(vector<Referencial> f) { filhos=f; }
void Referencial::setFiguras(vector<Figura> f) { figuras=f; }

void Referencial::addFilho(Referencial f) { filhos.push_back(f); }
void Referencial::addFigura(Figura f) { figuras.push_back(f); }

void Referencial::apply(float timePerFrame) {

	glPushMatrix();

	translacao.Apply(500,timePerFrame);
	escala.Apply();
	rotacao.Apply(timePerFrame);

	
	for(int i=0; i<(figuras.size());i++){
		figuras[i].drawFigureArrays();
	}
	for(int i=0;i<(filhos.size());i++){
		filhos[i].apply(timePerFrame);
		
	}
	glPopMatrix();
	
}
void Referencial::resetGlReferncial() { glPopMatrix();}
Escala Referencial::getEscala() { return escala; }
Translacao Referencial::getTranslacao() { return translacao; }
Rotacao Referencial::getRotacao() { return rotacao; }
vector<Referencial> Referencial::getFilhos() { return filhos; }
vector<Figura> Referencial::getFiguras() { return figuras; }
