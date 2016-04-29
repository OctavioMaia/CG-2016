#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include "tinyxml.h"
#include "tinystr.h"
#include "Ponto.h"
#include "Patch.h"


#define AngC  M_PI / 180
using namespace std;

int mmin(int i1, int i2){
	if(i1<=i2) return i1;
	return i2;
}

std::vector<std::string> &msplit(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


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

void cone(double raio, double alt, int slices, int stacks, string nome) {
	ofstream opfile(nome);
	double starY = alt / 2.0;
	double yStep = alt / float(stacks);
	double startAngleSL = 0.0;
	double angleSLStep = 360 / (float)slices;
	Ponto p, centro;
	centro = Ponto::Ponto(0, -alt / 2.0, 0);
	vector<Ponto> ant;
	vector<Ponto> actual;
	int totpont = (stacks*(slices * 2) + slices) * 3; //tem fatas*flises cada uma tem 2 triangulos 
													  //depois mais fatias para a base
													  //cada triangulo sao 3 pontos
	opfile << totpont << endl;
	double trigAlt = (yStep * 0);
	double triRaio = (raio*trigAlt) / alt;
	double y = starY - trigAlt;
	startAngleSL = 0.0;// posicionar a fatia na 1
	for (int fatia = 0; fatia<slices; fatia++) {
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
		for (int fatia = 0; fatia<slices; fatia++) {
			double z = triRaio*sin(startAngleSL*AngC); //estava x
			double x = triRaio*cos(startAngleSL*AngC); //estava z
			startAngleSL += angleSLStep; //proximafatia
			p = Ponto::Ponto(x, y, z);
			actual.push_back(p);
		}

		for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias;
			printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat] );
			printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices],ant[fat] );
		}

		ant = std::move(actual);
		actual.clear();

	}

	for (int fat = 0; fat<slices; fat++) { //contruir a base
		printTriangulo(opfile, ant[fat], ant[(fat + 1) % slices], centro );
	}
	opfile.close();

}

void cilindro(double h, double r, int slices, string nome) {
	ofstream opfile(nome);
	double startsl = 0.0;
	double slStep = 360.0 / (double)slices;
	Ponto topCentro;
	Ponto downCentro;
	Ponto topP;
	Ponto downP;
	vector<Ponto> top;
	vector<Ponto> down;
	topCentro = Ponto::Ponto(0, h / 2.0, 0);
	downCentro = Ponto::Ponto(0, -h / 2.0, 0);
	/*pontos da base e topo * fatias da face 2 triangulps em cada*/ 
	int pontos = ((slices * 2) * 3) +( slices * 2 * 3);
	opfile << pontos << endl;
	for (int i = 0; i < slices; i++)
	{
		topP = Ponto::Ponto(r*cos(startsl*AngC), h / 2.0, r*sin(startsl*AngC));
		downP = Ponto::Ponto(r*cos(startsl*AngC), -h / 2.0, r*sin(startsl*AngC));
		top.push_back(topP);
		down.push_back(downP);
		startsl += slStep;

	}
	for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias;
		//printTriangulo(opfile, top[fat], down[fat], down[(fat + 1) % slices]);
		printTriangulo(opfile,down[(fat + 1) % slices], down[fat], top[fat]);
		printTriangulo(opfile, down[(fat + 1) % slices], top[fat], top[(fat + 1) % slices]);
	}


	for (int fat = 0; fat < slices; fat++) { //contruir a base
		printTriangulo(opfile, down[(fat + 1) % slices], downCentro,down[fat]);
	}
	for (int fat = 0; fat < slices; fat++) { //contruir a top
		printTriangulo(opfile, top[fat], topCentro, top[(fat + 1) % slices]);
	}
	opfile.close();
}

void esfera(double raio, int slices, int stacks, string nome) {
	ofstream opfile(nome);
	double angleSt = 90.0;
	double angleSl;
	double angleStepSl = 360.0 / (float)slices;
	double angleStepSt = 180.0 / (float)stacks;
	vector<Ponto> ant;
	vector<Ponto> actual;
	Ponto p;

	angleSl = 0.0;
	int totpont = (stacks*(slices * 2)) * 3; //tem fatas*flises cada uma tem 2 triangulos 
											 //pode ser preciso mais uma stack
											 //cada triangulo sao 3 pontos
	opfile << totpont << endl;
	//angle da st esta a 90 stack do topo 
	for (int fat = 0; fat <= slices; fat++) { //contruir cada ims das fastias
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
		for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias
			double x = raio * cos(angleSt*AngC) * cos(angleSl*AngC);

			double y = raio * sin(angleSt*AngC);
			double z = raio * cos(angleSt*AngC) * sin(angleSl*AngC);
			p = Ponto::Ponto(x, y, z);
			actual.push_back(p);
			angleSl += angleStepSl; //proxima fatia nesta camada
		}
		//ja tenho a camada atual e anterior prontas
		//associar os pontos e mandar-los para o ficheiro
		for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias;
			printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat]);
			printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices], ant[fat]);
		}
		//triangulos imprimidos
		//meter o ant =  atual e limpar o atual
		ant = std::move(actual);
		actual.clear();

	}

	opfile.close();
}

/*
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
		cout << "Failed to load file " << xmlName << ", file not exists." << endl << "nCreating file "<< xmlName << endl;
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

*/

void loadPatch(string source,vector<Patch>& paches, vector<Ponto>& pontos){
	ifstream file(source);
	string line;
	getline(file, line);
	int nPach = stoi(line);
	vector<string> campos;
	for (int i = 0; i < nPach; i++)
	{
		//vai buscar a linha daquele patch
		getline(file, line);
		Patch pa = Patch::Patch(line);
		paches.push_back(pa);

	}
	//linha com o total de pontos
	getline(file, line);
	int nPoint = stoi(line);
	for (int i = 0; i < nPoint; i++)
	{
		//vai buscar a linha daquel ponto e mete no array que contem os pontos
		getline(file, line);
		campos.clear();
		msplit(line, ',',campos);
		Ponto p = Ponto::Ponto(atof(campos[0].c_str()),atof(campos[1].c_str()),atof(campos[2].c_str()));
		pontos.push_back(p);

	}
	file.close();
}

//Funcça que dada uma curva de bezier calcula o ponto da mesma utilizando a formula
// bt = t^3*P3+
//	3*t^2*(1-t)*P2
//	3*(t*(1-t)^2)*P1
//	((1-t)^3)*P0     
Ponto bezieCurve(float t, Ponto p0,Ponto p1,Ponto p2,Ponto p3){
	float x=0,y=0,z=0;
	float uMent = 1.0-t;
	float t1,t2,t3,t4;
	t1=t*t*t;
	t2=3*(t*t)*uMent;
	t3=3*(t*(uMent*uMent));
	t4=uMent*uMent*uMent;
	x = t1*p3.getx()+t2*p2.getx()+t3*p1.getx()+t4*p0.getx();
	y = t1*p3.gety()+t2*p2.gety()+t3*p1.gety()+t4*p0.gety();
	z = t1*p3.getz()+t2*p2.getz()+t3*p1.getz()+t4*p0.getz();

	return Ponto::Ponto(x, y, z);
}


//esta funcçao cacula o ponto representado pelo patch de bezier
//caclula primeiro para as 4 curvas, obtem 4 pontos que fazem uma linha de bezier 
//e depois calcula o nuvo ponto para essa linha
Ponto bezieSurface(float u, float v, Patch p,vector<Ponto> pontos){
	vector<Ponto> calculados;

	for (int i = 0; i < 16; i+=4)
	{
		Ponto po = bezieCurve(u, pontos[p.getAt(i)],pontos[p.getAt(i+1)],pontos[p.getAt(i+2)],pontos[p.getAt(i+3)]);
		calculados.push_back(po);
	}
	return bezieCurve(v,calculados[0],calculados[1],calculados[2],calculados[3]);
}

int main(int argc, char *argv[]) {
	char* nome;
	vector<Patch> paches;
	vector<Ponto> pontos;
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
						if (!strcmp(argv[1], "cilindro") && argc == 7) {
							cout << "CILINDRO" << endl;
							cilindro(atof(argv[2]), atof(argv[3]), atoi(argv[4]), argv[5]);
							nome = argv[5];
						}
						else {
							if (!strcmp(argv[1], "patch") && argc == 5) {
								cout << "PATCH" << endl;
								string source = argv[2];
								int tess = atoi(argv[3]);
								string out = argv[4]; 
								loadPatch(source,paches,pontos);
								translateFromBezie(tess,out,paches,pontos);
								nome = argv[5];
							}
							else{
								
							cout << "Desconhecido" << endl;
							return 1;
						}
					}
				}
			}
		}
		}
		//updateXML(argv[argc-1], nome);
		return 0;
	}

	return 2;
}
