#include "Figura.h"
#include <stdlib.h>



Figura::Figura(string fileName, int n) {
	fristTime = 1;
	file = fileName;
	listafloat = (float*)malloc(sizeof(float)* n*3);
	nPontos = n;
	pos = 0;
}

void Figura::addPonto(double x, double y, double z) {
	listaPontos.push_back(Ponto::Ponto(x, y, z));
	listafloat[pos++]=x;
	listafloat[pos++]=y;
	listafloat[pos++]=z;
}

void Figura::addColor(double r, double g, double b) {
	listaCores.push_back(Color::Color(r, g, b));
}

Ponto Figura::getP(int position) {
	return listaPontos[position];
}

Color Figura::getC(int position) {
	return listaCores[position];
}

int Figura::gerarCores() {
	int i;
	for (i = 0; i < (nPontos / 3); i++) {
		listaCores.push_back(Color::Color((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX)));
	}
	return i;
}

void Figura::drawFigure(bool multiColor) {
	if (multiColor==false) {
		for (int i = 0; i < nPontos; i = i + 3) {
			glBegin(GL_TRIANGLES);
			glVertex3d(listaPontos[i].getx(), listaPontos[i].gety(), listaPontos[i].getz());
			glVertex3d(listaPontos[i + 1].getx(), listaPontos[i + 1].gety(), listaPontos[i + 1].getz());
			glVertex3d(listaPontos[i + 2].getx(), listaPontos[i + 2].gety(), listaPontos[i + 2].getz());
			glEnd();
		}
	}
	else {
		for (int i = 0, j = 0; i < nPontos; i = i + 3, j++) {
			glBegin(GL_TRIANGLES);
			glColor3d(listaCores[j].getr(), listaCores[j].getg(), listaCores[j].getb());
			glVertex3d(listaPontos[i].getx(), listaPontos[i].gety(), listaPontos[i].getz());
			glVertex3d(listaPontos[i + 1].getx(), listaPontos[i + 1].gety(), listaPontos[i + 1].getz());
			glVertex3d(listaPontos[i + 2].getx(), listaPontos[i + 2].gety(), listaPontos[i + 2].getz());
			glEnd();
		}
	}
}

void Figura::drawFigureArrays() {
	
	if (fristTime==1) {
		glGenBuffers(1, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, pos*sizeof(float), listafloat, GL_STATIC_DRAW);
		//free(listafloat);
		fristTime = 0;
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, nPontos);


}