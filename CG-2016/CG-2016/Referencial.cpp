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

void Referencial::addFilho(Referencial f) { filhos.push_back(f); }

void Referencial::apply() {
	translacao.Apply();
	rotacao.Apply();
	escala.Apply();
}
void Referencial::resetGlReferncial() { ; }
Escala Referencial::getEscala() { return escala; }
Translacao Referencial::getTranslacao() { return translacao; }
Rotacao Referencial::getRotacao() { return rotacao; }
vector<Referencial> Referencial::getFilhos() { return filhos; }
