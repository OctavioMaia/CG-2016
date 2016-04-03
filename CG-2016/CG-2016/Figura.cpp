#include "Figura.h"
#include <stdlib.h>

GLuint buffers[1];

Figura::Figura(string fileName, int n) {
	file = fileName;
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
/*
void Figura::drawFigureArrays() {
	

	cout << "1";

	glGenBuffers(1, buffers);

	cout << "2";

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

	cout << "3";

	glBufferData(GL_ARRAY_BUFFER, nPontos*sizeof(double)*3, listafloat, GL_STATIC_DRAW);

	cout << "4";

	cout << "5";

	glVertexPointer(3, GL_FLOAT, 0, 0);


	cout << "6";
	glDrawArrays(GL_TRIANGLES, 0, nPontos*3);


}

*/