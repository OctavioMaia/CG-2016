#include "Figura.h"
#include <stdlib.h>



Figura::Figura(string fileName, string textF, int n,bool enableTexture) {
	fristTime = 1;
	nPontos = n;
	this->enableTexture = enableTexture;

	file = fileName;
	fileTexture = textF;

	posPontos = 0;
	posNormais = 0;
	posTexturas = 0;

	this->enableDiff = false;
	this->enableAmb = false;
	this->enableEmis = false;
	this->enableEspc = false;

	listaPontos = (float*)malloc(sizeof(float)* nPontos*3);
	normais = (float*)malloc(sizeof(float)*nPontos * 3);
	texturas = (float*)malloc(sizeof(float)*nPontos * 2);
}

void Figura::addPonto(double x, double y, double z) {
	listaPontos[posPontos++]=x;
	listaPontos[posPontos++]=y;
	listaPontos[posPontos++]=z;
}

void Figura::addNormal(float x, float y, float z)
{
	normais[posNormais++] = x;
	normais[posNormais++] = y;
	normais[posNormais++] = z;
}

void Figura::addTextur(float x, float y)
{
	texturas[posTexturas++] = x;
	texturas[posTexturas++] = y;
}

void Figura::setDiff(float r, float g, float b)
{
	this->diff[0] = r;
	this->diff[1] = g;
	this->diff[2] = b;
	this->diff[3] = 1.0;
	this->enableDiff = true;
}

void Figura::setAmb(float r, float g, float b)
{
	this->amb[0] = r;
	this->amb[1] = g;
	this->amb[2] = b;
	this->amb[3] = 1.0;
	this->enableAmb = true;
}

void Figura::setEmis(float r, float g, float b)
{
	this->emis[0] = r;
	this->emis[1] = g;
	this->emis[2] = b;
	this->emis[3] = 1.0;
	this->enableEmis = true;
}

void Figura::setEsp(float r, float g, float b)
{
	this->espc[0] = r;
	this->espc[1] = g;
	this->espc[2] = b;
	this->espc[3] = 1.0;
	this->enableEspc = true;
}

void Figura::setTextureFile(string file)
{
	this->fileTexture = file;
	this->enableTexture = true;
}

void Figura::loadImageTexture() {
	//imagem para altitude
	unsigned int t;
	ilGenImages(1, &t);
	ilBindImage(t);


	ilLoadImage((ILstring)this->fileTexture.c_str());
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	unsigned char* imageData = ilGetData();

	glGenTextures(1, &textID);

	glBindTexture(GL_TEXTURE_2D, textID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
}

void Figura::drawFigureArrays() {

	if (this->fristTime==1) {
		this->fristTime = 0;
		glGenBuffers(3, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, posPontos*sizeof(float), listaPontos, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, posNormais*sizeof(float), normais, GL_STATIC_DRAW);

		if (enableTexture) {
			loadImageTexture();
			glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
			glBufferData(GL_ARRAY_BUFFER, posTexturas * sizeof(float), texturas, GL_STATIC_DRAW);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	if (enableTexture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textID);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	} 
	if (enableAmb)  { glMaterialfv(GL_FRONT, GL_AMBIENT, amb); }
	if (enableDiff) { glMaterialfv(GL_FRONT, GL_DIFFUSE, diff); }
	if (enableEmis) { glMaterialfv(GL_FRONT, GL_EMISSION, emis); }
	if (enableEspc) { glMaterialfv(GL_FRONT, GL_SPECULAR, espc); }
	
	
	glDrawArrays(GL_TRIANGLES, 0, nPontos);

	//colocar sem texturas
	glBindTexture(GL_TEXTURE_2D, 0);
}