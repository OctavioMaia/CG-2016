#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <iomanip>
#include "tinyxml.h"
#include "tinystr.h"
#include "Ponto.h"

#define AngC  M_PI / 180
using namespace std;

void printTriangulo(ofstream& file, Ponto p1, Ponto p2, Ponto p3) {
	p1.printFile(file, ";", true);
	p2.printFile(file, ";", true);
	p3.printFile(file, ";", true);
}

void retangulo(ofstream& file, double xl, double y, double zl) {
	Ponto p1, p2, p3, p4;

	//Vertices
	double p1x = (xl / 2.0);
	double p2x = p1x;
	double p3x = -p1x;
	double p4x = p3x;

	double p1z = (zl / 2.0);
	double p2z = -p1z;
	double p3z = p2z;
	double p4z = p1z;

	p1 = Ponto::Ponto(p1x, y, p1z);
	p2 = Ponto::Ponto(p2x, y, p2z);
	p3 = Ponto::Ponto(p3x, y, p3z);
	p4 = Ponto::Ponto(p4x, y, p4z);

	printTriangulo(file, p1, p2, p3);
	printTriangulo(file, p3, p4, p1);
}

void plano(double leng, string nome) {
	ofstream opfile(nome);
	opfile << "6" << endl;
	retangulo(opfile, leng, 0, leng);
	opfile.close();
}

void box(double x, double y, double z, string nome) {
	ofstream opfile(nome);
	Ponto ps1, ps2, ps3, ps4, pi1, pi2, pi3, pi4;
	opfile << "36" << endl;

	//Vertices plano superior
	ps1 = Ponto::Ponto(x / 2, y / 2, z / 2);
	ps2 = Ponto::Ponto(x / 2, y / 2, -z / 2);
	ps3 = Ponto::Ponto(-x / 2, y / 2, -z / 2);
	ps4 = Ponto::Ponto(-x / 2, y / 2, z / 2);

	//Vertices plano superior
	pi1 = Ponto::Ponto(x / 2, -y / 2, z / 2);
	pi2 = Ponto::Ponto(x / 2, -y / 2, -z / 2);
	pi3 = Ponto::Ponto(-x / 2, -y / 2, -z / 2);
	pi4 = Ponto::Ponto(-x / 2, -y / 2, z / 2);

	//Plano superior X
	printTriangulo(opfile, ps1, ps2, ps3);
	printTriangulo(opfile, ps3, ps4, ps1);

	//Plano inferior X
	printTriangulo(opfile, pi1, pi3, pi2);
	printTriangulo(opfile, pi1, pi4, pi3);

	//Plano lateral dir X
	printTriangulo(opfile, ps2, ps1, pi1);
	printTriangulo(opfile, pi1, pi2, ps2);

	//Plano lat esq X
	printTriangulo(opfile, ps4, ps3, pi4);
	printTriangulo(opfile, ps3, pi3, pi4);

	//Plano frontal X
	printTriangulo(opfile, ps4, pi4, ps1);
	printTriangulo(opfile, ps1, pi4, pi1);

	//Plano traseiro
	printTriangulo(opfile, ps2, pi3, ps3);
	printTriangulo(opfile, pi3, ps2, pi2);

	opfile.close();
}

void cone(double raio, double alt, int fatias, int stacks, string nome) {
	ofstream opfile(nome);
	double starY = alt / 2.0;
	double yStep = alt / float(stacks);
	double startAngleSL = 0.0;
	double angleSLStep = 360 / (float)fatias;
	Ponto p, centro;
	centro = Ponto::Ponto(0, -alt / 2.0, 0);
	vector<Ponto> ant;
	vector<Ponto> actual;
	int totpont = (stacks*(fatias * 2) + fatias) * 3; //tem fatas*flises cada uma tem 2 triangulos 
													  //depois mais fatias para a base
													  //cada triangulo sao 3 pontos
	opfile << totpont << endl;
	double trigAlt = (yStep * 0);
	double triRaio = (raio*trigAlt) / alt;
	double y = starY - trigAlt;
	startAngleSL = 0.0;// posicionar a fatia na 1
	for (int fatia = 0; fatia<fatias; fatia++) {
		double z = triRaio*sin(startAngleSL*AngC); //estava x
		double x = triRaio*cos(startAngleSL*AngC); // estava z
		startAngleSL += angleSLStep;
		p = Ponto::Ponto(x, y, z);
		//p.printFile(opfile,";",true);
		ant.push_back(p);
	}

	for (int stack = 1; stack <= stacks; stack++) {
		//double trigAlt = starY-(yStep*stack); //altura deste triagulozito
		trigAlt = (yStep*stack);
		//calsular a base deste pat ser semlante ao real
		triRaio = (raio*trigAlt) / alt;
		y = starY - trigAlt; // altura dos postos desta stack é sempre a starY- altura deste triangulo
		startAngleSL = 0.0;// posicionar a fatia na 1
		for (int fatia = 0; fatia<fatias; fatia++) {
			double z = triRaio*sin(startAngleSL*AngC); //estava x
			double x = triRaio*cos(startAngleSL*AngC); //estava z
			startAngleSL += angleSLStep; //proximafatia
			p = Ponto::Ponto(x, y, z);
			actual.push_back(p);
		}

		for (int fat = 0; fat<fatias; fat++) { //contruir cada ims das fastias;
			printTriangulo(opfile, ant[fat], actual[fat], actual[(fat + 1) % fatias]);
			printTriangulo(opfile, ant[(fat + 1) % fatias], ant[fat], actual[(fat + 1) % fatias]);
		}

		ant = std::move(actual);
		actual.clear();

	}

	for (int fat = 0; fat<fatias; fat++) { //contruir a base
		printTriangulo(opfile, ant[fat], centro, ant[(fat + 1) % fatias]);
	}
	opfile.close();

}

void esfera(double raio, int fatias, int stacks, string nome) {
	ofstream opfile(nome);
	double angleSt = 90.0;
	double angleSl;
	double angleStepSl = 360.0 / (float)fatias;
	double angleStepSt = 180.0 / (float)stacks;
	vector<Ponto> ant;
	vector<Ponto> actual;
	Ponto p;

	angleSl = 0.0;
	int totpont = (stacks*(fatias * 2)) * 3; //tem fatas*flises cada uma tem 2 triangulos 
											 //pode ser preciso mais uma stack
											 //cada triangulo sao 3 pontos
	opfile << totpont << endl;
	//angle da st esta a 90 stack do topo 
	for (int fat = 0; fat <= fatias; fat++) { //contruir cada ims das fastias
		double x = raio * cos(angleSt*AngC) * cos(angleSl*AngC); // estava x
		double y = raio * sin(angleSt*AngC);
		double z = raio * cos(angleSt*AngC) * sin(angleSl*AngC); // estava z
		p = Ponto::Ponto(x, y, z);
		ant.push_back(p); //mete o ponto da stack anterior no ant
		angleSl += angleStepSl; //proxima fatia
	}
	//primeira camada ja tem os pontos todos gaudados em ante

	for (int stack = 1; stack<stacks + 1; stack++) {
		angleSl = 0.0; //volto ao inicio das fatias
		angleSt += angleStepSt; //proxima stack (pata baixo)
								//char str [80];
								//printf("Stack nuemro : %d\n angulo com XZ %f",stack, angleSt);
								//scanf ("%79s",str); 
		for (int fat = 0; fat<fatias; fat++) { //contruir cada ims das fastias
			double x = raio * cos(angleSt*AngC) * cos(angleSl*AngC);

			double y = raio * sin(angleSt*AngC);
			double z = raio * cos(angleSt*AngC) * sin(angleSl*AngC);
			p = Ponto::Ponto(x, y, z);
			actual.push_back(p);
			angleSl += angleStepSl; //proxima fatia nesta camada
		}
		//ja tenho a camada atual e anterior prontas
		//associar os pontos e mandar-los para o ficheiro
		for (int fat = 0; fat<fatias; fat++) { //contruir cada ims das fastias;
			printTriangulo(opfile, ant[fat], actual[fat], actual[(fat + 1) % fatias]);
			printTriangulo(opfile, ant[(fat + 1) % fatias], ant[fat], actual[(fat + 1) % fatias]);
		}
		//triangulos imprimidos
		//meter o ant =  atual e limpar o atual
		ant = std::move(actual);
		actual.clear();

	}

	opfile.close();
}


void updateXML(char* xmlName, char* modeloName) {
	TiXmlDocument doc;
	if (doc.LoadFile(xmlName))
	{
		TiXmlElement* modelo;
		TiXmlElement* element = doc.FirstChildElement("scene");

		const char* file;
		bool same = false;

		for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("model"); elem != NULL; elem = elem->NextSiblingElement()) {

			file = elem->Attribute("file");

			if (!strcmp(modeloName, file)) {
				same = true;
			}
		}
		if (!same) {
			modelo = new TiXmlElement("model");
			modelo->SetAttribute("file", modeloName);

			element->LinkEndChild(modelo);
			doc.SaveFile(xmlName);
		}
	}
	else
	{
		printf("Failed to load file %s , file not exists.\nCreating file teste1.xml...\n", xmlName);

		TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "utf-8", "");
		doc.LinkEndChild(decl);

		TiXmlElement * scene;
		scene = new TiXmlElement("scene");

		TiXmlElement * model;
		model = new TiXmlElement("model");
		model->SetAttribute("file", modeloName);
		scene->LinkEndChild(model);
		
		doc.LinkEndChild(scene);

		doc.SaveFile(xmlName);
	}
}

int main(int argc, char *argv[]) {
	char* nome;
	if (argc>1) {
		if (!strcmp(argv[1], "plano") && argc == 5) {
			cout << "PLANO" << endl;
			plano(atof(argv[2]), argv[3]);
			nome = argv[3];
		}
		else {
			if (!strcmp(argv[1], "esfera") && argc == 7) {
				cout << "ESFERA" << endl;
				esfera(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
				nome = argv[5];
			}
			else {
				if (!strcmp(argv[1], "box") && argc == 7) {
					cout << "BOX" << endl;
					box(atof(argv[2]), atof(argv[3]), atof(argv[4]), argv[5]);
					nome = argv[5];
				}
				else {
					if (!strcmp(argv[1], "cone") && argc == 8) {
						cout << "CONE" << endl;
						cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
						nome = argv[6];
					}
					else {
						printf("Desconhecido\n");
						return 1;
					}
				}
			}
		}
		updateXML(argv[argc-1], nome);
		return 0;
	}

	return 2;
}
