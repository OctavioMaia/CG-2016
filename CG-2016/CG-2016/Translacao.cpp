#include "Translacao.h"


float refere = 10;
Translacao::Translacao() {
	time = 0.0;
	flag = false;
	this->tpGlobal=0.0;
}

Translacao::Translacao(float time) {
	this->time = time;
	this->flag = false;
	this->tpGlobal=0.0;
}

void Translacao::setTime(float t) { this->time = t; }
float Translacao::getTime() { return this->time; }

void Translacao::addPoint(Ponto p) {
	points.push_back(p);
}

void getT(float t, float* res) {
	res[0] = t*t*t;
	res[1] = t*t;
	res[2] = t;
	res[3] = 1;
}

void getD(float t, float* res) {
	res[0] = 3 * t*t;
	res[1] = 2 * t;
	res[2] = 1;
	res[3] = 0;
}

void Translacao::getCatmullRomPoint(float t, int *indices, float *res) {

	// catmull-rom matrix
	float m[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
	{ 1.0f, -2.5f,  2.0f, -0.5f },
	{ -0.5f,  0.0f,  0.5f,  0.0f },
	{ 0.0f,  1.0f,  0.0f,  0.0f } };

	float form[4];
	float aux[4];

	getT(t, form);

	aux[0] = 0.0; aux[1] = 0.0; aux[2] = 0.0; aux[3] = 0.0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aux[j] += form[i] * m[i][j];
		}
	}

	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			res[i] += aux[j] * points[indices[j]].getXYZ(i);//coisa bonita no getXYZ
		}
	}
}

// given  global t, returns the point in the curve
void  Translacao::getGlobalCatmullRomPoint(float gt, float *res) {
	int POINT_COUNT = points.size();
	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

				   // indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
	indices[1] = (indices[0] + 1) % POINT_COUNT;
	indices[2] = (indices[1] + 1) % POINT_COUNT;
	indices[3] = (indices[2] + 1) % POINT_COUNT;

	getCatmullRomPoint(t, indices, res);
}

void Translacao::getCatmullDerivatePoint(float t, int* indices, float *res) {
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;

	float m[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
	{ 1.0f, -2.5f,  2.0f, -0.5f },
	{ -0.5f,  0.0f,  0.5f,  0.0f },
	{ 0.0f,  1.0f,  0.0f,  0.0f } };

	float form[4];
	float aux[4];

	getD(t, form);

	aux[0] = 0.0;
	aux[1] = 0.0;
	aux[2] = 0.0;
	aux[3] = 0.0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aux[i] += form[j] * m[j][i];
		}
	}

	res[0] = 0.0;
	res[1] = 0.0;
	res[2] = 0.0;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 4; j++) {
			res[i] += aux[j] * points[indices[j]].getXYZ(i);
		}
	}
}

void Translacao::getGlobalCatmullDerivatePoint(float gt, float* res) {
	int POINT_COUNT = points.size();

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment
				   // indices store the points
	int indices[4];

	indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
	indices[1] = (indices[0] + 1) % POINT_COUNT;
	indices[2] = (indices[1] + 1) % POINT_COUNT;
	indices[3] = (indices[2] + 1) % POINT_COUNT;

	getCatmullDerivatePoint(t, indices, res);
}

void productVetor(float* v1, float* v2, float* res) {
	int x = 0, y = 1, z = 2;
	res[x] = v1[y] * v2[z] - v1[z] * v2[y];
	res[y] = v1[z] * v2[x] - v1[x] * v2[z];
	res[z] = v1[x] * v2[y] - v1[y] * v2[x];
}

void normalizeVector(float* res) {
	float norm = sqrt(res[0] * res[0] + res[1] * res[1] + res[2] * res[2]);
	res[0] = res[0] / norm;
	res[1] = res[1] / norm;
	res[2] = res[2] / norm;
}

void Translacao::Apply(int tess, float timePerFrame) {

	this->tpGlobal += (timePerFrame*(1.0/this->time))/ 1;

	if  (points.size()>=4) {
		
		float step = 1.0 / tess;
		float val[3];
		int index = 0;

		if (!flag) {
			flag = true;
			this->catmullVertex = (float*)malloc(sizeof(float)*tess * 3);

			for (int passo = 0; passo < tess; passo++) {
				float gt = step*passo;
				getGlobalCatmullRomPoint(gt, val);
				catmullVertex[index++] = val[0];
				catmullVertex[index++] = val[1];
				catmullVertex[index++] = val[2];
			}

			glGenBuffers(1, buffersTranslate);
			glBindBuffer(GL_ARRAY_BUFFER, buffersTranslate[0]);
			glBufferData(GL_ARRAY_BUFFER, index*sizeof(float), catmullVertex, GL_STATIC_DRAW);

		}

		glBindBuffer(GL_ARRAY_BUFFER, buffersTranslate[0]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_LINE_LOOP, 0, tess);

	GLfloat* m = (GLfloat*)malloc(sizeof(GLfloat) * 16);

	for (int i = 0; i < 16; i++) {
		m[i] = 0.0;
	}

	m[15] = 1.0;

	float d[3];
	float up[3] = { 0.0f, 1.0f, 0.0f };
	float left[3];
	float res[3];

	if (this->tpGlobal == 0) {
		getGlobalCatmullRomPoint(this->tpGlobal, res);
		glTranslatef(res[0],res[1],res[2]);
	}else {
		getGlobalCatmullDerivatePoint(this->tpGlobal, d);
		getGlobalCatmullRomPoint(this->tpGlobal, res);

		normalizeVector(d);
		productVetor(up, d, left);
		normalizeVector(left);
		productVetor(d, left, up);

		int v = 0;
		for (int i = 0; i < 3; i++) {
			m[i] = left[i];
			m[4 + i] = up[i];
			m[8 + i] = d[i];
			m[12 + i] = res[i];
		}
		glMultMatrixf(m);
	}
	free(m);
}
	
	


}