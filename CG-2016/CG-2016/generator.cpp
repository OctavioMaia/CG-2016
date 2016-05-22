#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
//#include "tinyxml.h"
//#include "tinystr.h"
#include "Ponto.h"
#include "Patch.h"


#define AngC  M_PI / 180
using namespace std;

int mmin(int i1, int i2){
	if(i1<=i2) return i1;
	return i2;
}

Ponto normalize(Ponto vetor){
	double s = sqrt((vetor.getx()*vetor.getx())+ (vetor.gety()*vetor.gety())+ (vetor.getz()*vetor.getz()));
	//if(s==0) return Ponto::Ponto(0,0,0);
	return Ponto::Ponto(vetor.getx()/s,vetor.gety()/s,vetor.getz()/s);
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

void printTriangulo(ofstream& file, Ponto p1, Ponto p2, Ponto p3,Ponto n1, Ponto n2, Ponto n3) {
	p1.printFile(file, ";", true);
	n1.printFile(file, ";", true);
	p2.printFile(file, ";", true);
	n2.printFile(file, ";", true);
	p3.printFile(file, ";", true);
	n3.printFile(file, ";", true);
}
void printTriangulo(ofstream& file, Ponto p1, Ponto p2, Ponto p3,Ponto n1, Ponto n2, Ponto n3,Ponto t1, Ponto t2,Ponto t3) {
	p1.printFile(file, ";", true);
	n1.printFile(file, ";", true);
	t1.printFile2D(file, ";", true);

	p2.printFile(file, ";", true);
	n2.printFile(file, ";", true);
	t2.printFile2D(file, ";", true);

	p3.printFile(file, ";", true);
	n3.printFile(file, ";", true);
	t3.printFile2D(file, ";", true);
}

//verclasse para textura
void retangulo(ofstream& file, double xl, double y, double zl) {
	Ponto p1, p2, p3, p4,norm,t1,t2,t3,t4;

	//Vertices
	double p1x = (xl / 2.0);
	double p2x = p1x;
	double p3x = -p1x;
	double p4x = p3x;

	double p1z = (zl / 2.0);
	double p2z = -p1z;
	double p3z = p2z;
	double p4z = p1z;
	norm = Ponto::Ponto(0,1,0);
	p1 = Ponto::Ponto(p1x, y, p1z);
	p2 = Ponto::Ponto(p2x, y, p2z);
	p3 = Ponto::Ponto(p3x, y, p3z);
	p4 = Ponto::Ponto(p4x, y, p4z);

	t1=Ponto::Ponto(1,1,0);
	t2=Ponto::Ponto(1,0,0);
	t3=Ponto::Ponto(0,0,0);
	t4=Ponto::Ponto(0,1,0);

	printTriangulo(file, p1, p2, p3,norm,norm,norm,t1,t2,t3);
	
	printTriangulo(file, p3, p4, p1,norm,norm,norm,t3,t4,t1);
}

void plano(double leng, string nome) {
	ofstream opfile(nome);
	opfile << "1;1;1"<<endl;
	opfile << "6" << endl;
	retangulo(opfile, leng, 0, leng);
	opfile.close();
}

void box(double x, double y, double z, string nome) {
	ofstream opfile(nome);
	Ponto ps1, ps2, ps3, ps4, pi1, pi2, pi3, pi4;
	Ponto ns,ni,nd,ne,nf,nt;
	Ponto t1,t2,t3,t4;
	opfile << "1;1;1"<<endl;
	opfile << "36" << endl;
	ns=Ponto::Ponto(0,1,0);
	ni=Ponto::Ponto(0,-1,0);

	nd=Ponto::Ponto(1,0,0);
	ne=Ponto::Ponto(-1,0,0);

	nf=Ponto::Ponto(0,0,1);
	nt=Ponto::Ponto(0,0,-1);


	t1=Ponto::Ponto(1,1,0);
	t2=Ponto::Ponto(1,0,0);
	t3=Ponto::Ponto(0,0,0);
	t4=Ponto::Ponto(0,1,0);

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
	printTriangulo(opfile, ps1, ps2, ps3,ns,ns,ns,t2,t1,t4);
	printTriangulo(opfile, ps3, ps4, ps1,ns,ns,ns,t4,t3,t2);

	//Plano inferior X
	printTriangulo(opfile, pi1, pi3, pi2,ni,ni,ni,t1,t3,t2);
	printTriangulo(opfile, pi1, pi4, pi3,ni,ni,ni,t1,t4,t3);

	//Plano lateral dir X
	printTriangulo(opfile, ps2, ps1, pi1,nd,nd,nd,t1,t4,t3);
	printTriangulo(opfile, pi1, pi2, ps2,nd,nd,nd,t3,t2,t1);

	//Plano lat esq X
	printTriangulo(opfile, ps4, ps3, pi4,ne,ne,ne,t1,t4,t2);
	printTriangulo(opfile, ps3, pi3, pi4,ne,ne,ne,t4,t3,t2);

	//Plano frontal X
	printTriangulo(opfile, ps4, pi4, ps1,nf,nf,nf,t4,t3,t1);
	printTriangulo(opfile, ps1, pi4, pi1,nf,nf,nf,t1,t3,t2);

	//Plano traseiro
	printTriangulo(opfile, ps2, pi3, ps3,nt,nt,nt,t4,t2,t1);
	printTriangulo(opfile, pi3, ps2, pi2,nt,nt,nt,t2,t4,t3);

	opfile.close();
}

void cone(double raio, double alt, int slices, int stacks, string nome) {
	//
	ofstream opfile(nome);
	double starY = alt / 2.0;
	double yStep = alt / float(stacks);
	double startAngleSL = 0.0;
	double angleSLStep = 360 / (float)slices;
	Ponto p, centro,norm;
	Ponto normalDown;
	centro = Ponto::Ponto(0, -alt / 2.0, 0);
	normalDown = Ponto::Ponto(0, -1, 0);
	vector<Ponto> ant,antNorm;
	vector<Ponto> actual,actualNorm;
	vector<Ponto> textAnt,textActual;
	vector<Ponto> texturebase;
	int totpont = (stacks*(slices * 2) + slices) * 3; //tem fatas*flises cada uma tem 2 triangulos 
													  //depois mais fatias para a base
													  //cada triangulo sao 3 pontos
	Ponto centroDown = Ponto::Ponto(0.8125,0.1875,0);
	opfile << "1;1;1"<<endl;
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
		//normal
		Ponto aux = normalize(Ponto::Ponto(x,0,y));


		norm=Ponto::Ponto(aux.getx()*alt/raio,raio/alt,aux.getz()*alt/raio);
		ant.push_back(p);
		antNorm.push_back(norm);
		double textY = y + starY; //meter maior que 0
		textY = textY / alt;
		textY = textY*(1 - 0.375); //normaliza ente as dim do triangulo
		textY += 0.375; // faz offset
		Ponto textura = Ponto::Ponto(1-(fatia/(slices*1.0)), textY,0);
		textAnt.push_back(textura);
	}

	for (int stack = 1; stack <= stacks; stack++) {
		//double trigAlt = starY-(yStep*stack); //altura deste triagulozito
		trigAlt = (yStep*stack);
		//calsular a base deste pat ser semlante ao real
		triRaio = (raio*trigAlt) / alt;//meter ente 0 e 1
		y = starY - trigAlt; // altura dos postos desta stack é sempre a starY- altura deste triangulo
		startAngleSL = 0.0;// posicionar a fatia na 1
		for (int fatia = 0; fatia<slices; fatia++) {
			double z = triRaio*sin(startAngleSL*AngC); //estava x
			double x = triRaio*cos(startAngleSL*AngC); //estava z
			startAngleSL += angleSLStep; //proximafatia
			p = Ponto::Ponto(x, y, z);
			Ponto aux = normalize(Ponto::Ponto(x,0,y));
			norm=Ponto::Ponto(aux.getx()*alt/raio,raio/alt,aux.getz()*alt/raio);
			actual.push_back(p);
			actualNorm.push_back(norm);
			double textY = y + starY; //meter maior que 0
			textY = textY / alt; //meter ente 0 e 1
			textY = textY*(1 - 0.375); //normaliza ente as dim do triangulo
			textY += 0.375; // faz offset
			Ponto textura = Ponto::Ponto(1-(fatia/(slices*1.0)), textY,0);
			textActual.push_back(textura);
			
		}

		for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias;
			if (fat + 1 != slices) {
				printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat],
					antNorm[fat], actualNorm[(fat + 1) % slices], actualNorm[fat],
					textAnt[fat], textActual[(fat + 1) % slices], textActual[fat]);
				printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices], ant[fat],
					antNorm[(fat + 1) % slices], actualNorm[(fat + 1) % slices], antNorm[fat],
					textAnt[(fat + 1) % slices], textActual[(fat + 1) % slices], textAnt[fat]);
			}
			else {
				Ponto autalNext = textActual[(fat + 1) % slices];
				autalNext.setX(0);
				Ponto autalThis = textActual[fat % slices];
				autalThis.setX(1/ (slices*1.0));
				Ponto antNext = textAnt[(fat + 1) % slices];
				antNext.setX(0);
				Ponto antThis = textAnt[fat % slices];
				antThis.setX(1 / (slices*1.0));

				printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat],
					antNorm[fat], actualNorm[(fat + 1) % slices], actualNorm[fat],
					antThis, autalNext, autalThis);



				printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices], ant[fat],
					antNorm[(fat + 1) % slices], actualNorm[(fat + 1) % slices], antNorm[fat],
					antNext, autalThis, antThis);
			}
		}

		ant = std::move(actual);
		antNorm=std::move(actualNorm);
		actual.clear();
		actualNorm.clear();
		textAnt=std::move(textActual);
		textActual.clear();

	}

	for (int slice = 0; slice < slices; slice++) {
		Ponto texture = Ponto::Ponto((0.375 / 2) * cos(-angleSLStep*slice*AngC) + 0.8125, (0.375 / 2) * sin(-angleSLStep*slice*AngC) + 0.1875, 0);
		texturebase.push_back(texture);
	}

	for (int fat = 0; fat<slices; fat++) { //contruir a base
		double ang = fat*angleSLStep;
		double ang2 = ang+ angleSLStep;

		printTriangulo(opfile, ant[fat], ant[(fat + 1) % slices], centro,
			normalDown,normalDown,normalDown,
			texturebase[fat], texturebase[(fat + 1) % slices], centroDown);
	}
	opfile.close();

}


void cilindro(double h, double r, int slices, string nome) {
	ofstream opfile(nome);
	double startsl = 0.0;
	double slStep = 360.0 / (double)slices;
	Ponto topCentro;
	Ponto downCentro;
	Ponto topP,topN;
	Ponto downP,downN;
	Ponto topNorma,downNorma;
	vector<Ponto> top;
	vector<Ponto> down;
	vector<Ponto> topNorm;
	vector<Ponto> downNorm;
	// texturas
	vector<Ponto> textTop;
	vector<Ponto> textDown;
	vector<Ponto> textTampaC;
	vector<Ponto> textTampaB;
	Ponto textCTop = Ponto::Ponto(0.4375,0.1878,0);
	Ponto textCDown = Ponto::Ponto(0.8125,0.1875,0);


	topCentro = Ponto::Ponto(0, h / 2.0, 0);
	downCentro = Ponto::Ponto(0, -h / 2.0, 0);
	topNorma = Ponto::Ponto(0,1,0);
	downNorma = Ponto::Ponto(0,-1,0);
	/*pontos da base e topo * fatias da face 2 triangulps em cada*/ 
	int pontos = ((slices * 2) * 3) +( slices * 2 * 3);
	opfile << "1;1;1"<<endl;
	opfile << pontos << endl;
	for (int i = 0; i < slices; i++)
	{
		topP = Ponto::Ponto(r*cos(startsl*AngC), h / 2.0, r*sin(startsl*AngC));
		downP = Ponto::Ponto(r*cos(startsl*AngC), -h / 2.0, r*sin(startsl*AngC));
		topN = Ponto::Ponto(cos(startsl*AngC),0,sin(startsl*AngC));
		downN = Ponto::Ponto(cos(startsl*AngC),0, sin(startsl*AngC));
		
		Ponto topTampa = Ponto::Ponto((0.375/2) * cos(-startsl*AngC)+0.4375,(0.375 / 2) * sin(-startsl*AngC)+0.1875,0);
		Ponto downTampa = Ponto::Ponto((0.375/2) * cos(-startsl*AngC)+0.8125,(0.375 / 2) * sin(-startsl*AngC)+0.1875,0); 

		Ponto ladocima = Ponto::Ponto((slices-i) / (slices*1.0),1,0);
		Ponto ladobaixo = Ponto::Ponto((slices-i) / (slices*1.0),0.375,0);

		textTampaC.push_back(topTampa);
		textTampaB.push_back(downTampa);

		textTop.push_back(ladocima);
		textDown.push_back(ladobaixo);


		top.push_back(topP);
		down.push_back(downP);
		topNorm.push_back(topN);
		downNorm.push_back(downN);
		startsl += slStep;

	}
	for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias;
		//printTriangulo(opfile, top[fat], down[fat], down[(fat + 1) % slices]);
			printTriangulo(opfile, down[(fat + 1) % slices], down[fat], top[fat],
				downNorm[(fat + 1) % slices], downNorm[fat], topNorm[fat],
				textDown[(fat + 1) % slices], textDown[fat], textTop[fat]);
			printTriangulo(opfile, down[(fat + 1) % slices], top[fat], top[(fat + 1) % slices],
				downNorm[(fat + 1) % slices], topNorm[fat], topNorm[(fat + 1) % slices],
				textDown[(fat + 1) % slices], textTop[fat], textTop[(fat + 1) % slices]);

	}


	for (int fat = 0; fat < slices; fat++) { //contruir a base
		printTriangulo(opfile, down[(fat + 1) % slices], downCentro,down[fat],
			downNorma,downNorma,downNorma,
			textTampaB[(fat + 1) % slices], textCDown,textTampaB[fat]);
	}
	for (int fat = 0; fat < slices; fat++) { //contruir a top
		printTriangulo(opfile, top[fat], topCentro, top[(fat + 1) % slices],
			topNorma,topNorma,topNorma,
			textTampaC[fat], textCTop, textTampaC[(fat + 1) % slices]);
	}
	opfile.close();
}

void esfera(double raio, int slices, int stacks, string nome) {
	ofstream opfile(nome);
	double angleSt = 90.0;
	double angleSl;
	double angleStepSl = 360.0 / (float)slices;
	double angleStepSt = 180.0 / (float)stacks;
	double stepTextSl = 1 / (float)slices;
	double stepTextSt = 1 / (float)stacks;
	vector<Ponto> ant;
	vector<Ponto> actual;
	vector<Ponto> antNorm;
	vector<Ponto> actualNorm;
	vector<Ponto> textAnt;
	vector<Ponto> textActual;
	Ponto p, pN, text;

	angleSl = 0.0;
	int totpont = (stacks*(slices * 2)) * 3; //tem fatas*flises cada uma tem 2 triangulos 
											 //pode ser preciso mais uma stack
											 //cada triangulo sao 3 pontos
	opfile << "1;1;1" << endl;
	opfile << totpont << endl;
	//angle da st esta a 90 stack do topo 
	for (int fat = 0; fat <= slices; fat++) { //contruir cada ims das fastias
		double x = raio * cos(angleSt*AngC) * cos(angleSl*AngC); // estava x
		double y = raio * sin(angleSt*AngC);
		double z = raio * cos(angleSt*AngC) * sin(angleSl*AngC); // estava z

		double xN = cos(angleSt*AngC) * cos(angleSl*AngC); // estava x
		double yN = sin(angleSt*AngC);
		double zN = cos(angleSt*AngC) * sin(angleSl*AngC); // estava z

		text = Ponto((slices - fat)*stepTextSl, 1, 0); //y pode estar trocado com x
		textAnt.push_back(text);
		p = Ponto::Ponto(x, y, z);
		pN = Ponto::Ponto(xN, yN, zN);
		ant.push_back(p); //mete o ponto da stack anterior no ant
		antNorm.push_back(normalize(pN));
		angleSl += angleStepSl; //proxima fatia
	}
	//primeira camada ja tem os pontos todos gaudados em ante

	for (int stack = 1; stack<stacks + 1; stack++) {
		angleSl = 0.0; //volto ao inicio das fatias
		angleSt += angleStepSt; //proxima stack (pata baixo)
								//char str [80];
								//printf("Stack nuemro : %d\n angulo com XZ %f",stack, angleSt);
								//scanf ("%79s",str); 
		for (int fat = 0; fat <= slices; fat++) { //contruir cada ims das fastias
			double x = raio * cos(angleSt*AngC) * cos(angleSl*AngC);
			double y = raio * sin(angleSt*AngC);
			double z = raio * cos(angleSt*AngC) * sin(angleSl*AngC);
			double xN = cos(angleSt*AngC) * cos(angleSl*AngC);
			double yN = sin(angleSt*AngC);
			double zN = cos(angleSt*AngC) * sin(angleSl*AngC);

			pN = Ponto::Ponto(xN, yN, zN);
			text = Ponto((slices - fat)*stepTextSl, (stacks - stack)*stepTextSt, 0); //y pode estar trocado com x
			textActual.push_back(text);
			p = Ponto::Ponto(x, y, z);
			actual.push_back(p);
			actualNorm.push_back(normalize(pN));
			angleSl += angleStepSl; //proxima fatia nesta camada
		}
		//ja tenho a camada atual e anterior prontas
		//associar os pontos e mandar-los para o ficheiro
		for (int fat = 0; fat<slices; fat++) { //contruir cada ims das fastias;
											   //printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat]);
											   //printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat]);
			if (fat + 1 != slices) {
				printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat],
					antNorm[fat], actualNorm[(fat + 1) % slices], actualNorm[fat],
					textAnt[fat], textActual[(fat + 1) % slices], textActual[fat]);
				//printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices], ant[fat]);
				printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices], ant[fat],
					antNorm[(fat + 1) % slices], actualNorm[(fat + 1) % slices], antNorm[fat],
					textAnt[(fat + 1) % slices], textActual[(fat + 1) % slices], textAnt[fat]);
			}
			else {
				Ponto autalNext = textActual[(fat + 1) % slices];
				autalNext.setX(0);
				Ponto autalThis = textActual[fat % slices];
				autalThis.setX(stepTextSl);
				Ponto antNext = textAnt[(fat + 1) % slices];
				antNext.setX(0);
				Ponto antThis = textAnt[fat % slices];
				antThis.setX(stepTextSl);

				printTriangulo(opfile, ant[fat], actual[(fat + 1) % slices], actual[fat],
					antNorm[fat], actualNorm[(fat + 1) % slices], actualNorm[fat],
					antThis, autalNext, autalThis);



				printTriangulo(opfile, ant[(fat + 1) % slices], actual[(fat + 1) % slices], ant[fat],
					antNorm[(fat + 1) % slices], actualNorm[(fat + 1) % slices], antNorm[fat],
					antNext, autalThis, antThis);
			}
		}
		ant = std::move(actual);
		antNorm = std::move(actualNorm);
		textAnt = std::move(textActual);
		actual.clear();
		actualNorm.clear();
		textActual.clear();

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

Ponto bezieCurveD(float t, Ponto p0,Ponto p1,Ponto p2,Ponto p3){
	float x=0,y=0,z=0;
	float uMent = 1.0-t;
	float t1,t2,t3,t4;
	t1=3*t*t;
	t2= -3*t*(3*t-2);
	
	t3=3*uMent*(3*t-1);
	t4=-3*uMent*uMent;
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


Ponto crossProduct(Ponto u, Ponto v){
	float nx = u.gety()*v.getz()-u.getz()*v.gety();
	float ny = u.getz()*v.getx()-u.getx()*v.getz();
	float nz = u.getx()*v.gety()-u.gety()*v.getx();
	Ponto p = Ponto::Ponto(nx,ny,nz);
	return p;

}

Ponto dUBezier(float u, float v,Patch p, vector<Ponto>& pontos)
{ 
  vector<Ponto> calculados; 
   for (int i = 0; i < 16; i+=4) { 
   		Ponto po = bezieCurveD(u, pontos[p.getAt(i)],pontos[p.getAt(i+1)],pontos[p.getAt(i+2)],pontos[p.getAt(i+3)]);
		calculados.push_back(po);
   } 
 
   return bezieCurve(v,calculados[0],calculados[1],calculados[2],calculados[3]); 
} 
 
Ponto dVBezier(float u, float v,Patch p, vector<Ponto>& pontos)
{ 
    vector<Ponto> calculados;  
   for (int i = 0; i < 16; i+=4) { 
  		Ponto po = bezieCurve(u, pontos[p.getAt(i)],pontos[p.getAt(i+1)],pontos[p.getAt(i+2)],pontos[p.getAt(i+3)]);
		calculados.push_back(po);
   } 
 
   return bezieCurveD(v,calculados[0],calculados[1],calculados[2],calculados[3]); 
} 

Ponto bezieNormal(float u, float v, Patch p,vector<Ponto> pontos){
	Ponto du,dv;

	du = dUBezier(u,v,p,pontos);
	dv = dVBezier(u,v,p,pontos);;
	return normalize(crossProduct(du,dv));
}


//ºara um pactch vai calcular e imprimir todos os 
//triangulos que o formam, dado um numero de tesselation dejesada
//para cada iteraçap calclua 4 pontos devido à variaçao de u e de t, sendo casludades
//para u e t atualis e seguites em combinaçao dpeois imprime os dois triangulos
// formados pelos 4 pontos calculados 
void bezieToTriangles(int tess, int patchnum, ofstream& output,vector<Patch>& paches, vector<Ponto>& pontos){
	float step = 1.0/tess;
	float u,v,uNext,vNext;

	for (int i = 0; i < tess; i++)
	{
		u=i*step;
		uNext=(i+1)*step;
		for (int j = 0; j < tess; j++)
		{
			v=j*step;
			vNext=(j+1)*step;
			Ponto p1 = bezieSurface(u,v,paches[patchnum],pontos);
			Ponto n1 = bezieNormal(u,v,paches[patchnum],pontos);
			Ponto t1 = Ponto::Ponto(u,v,0);

			Ponto p2 = bezieSurface(u,vNext,paches[patchnum],pontos);
			Ponto n2 = bezieNormal(u,vNext,paches[patchnum],pontos);
			Ponto t2 = Ponto::Ponto(u,vNext,0);

			Ponto p3 = bezieSurface(uNext,v,paches[patchnum],pontos);
			Ponto n3 = bezieNormal(uNext,v,paches[patchnum],pontos);
			Ponto t3 = Ponto::Ponto(uNext,v,0);

			Ponto p4 = bezieSurface(uNext,vNext,paches[patchnum],pontos);
			Ponto n4 = bezieNormal(uNext,vNext,paches[patchnum],pontos);
			Ponto t4 = Ponto::Ponto(uNext,vNext,0);

			//printTriangulo(output,p1,p3,p4);
			//printTriangulo(output,p1,p4,p2);
			printTriangulo(output,p1,p3,p4,n1,n3,n4,t1,t3,t4);
			printTriangulo(output,p1,p4,p2,n1,n4,n2,t1,t4,t2);
		}
	}
}

void translateFromBezie(int tess, string fname,vector<Patch>& paches, vector<Ponto>& pontos){
	ofstream file(fname);

	int totpatch = paches.size();
	file << "1;1;1"<< endl;
	file << (totpatch*tess*tess * 2*3) << endl;
	for (int i = 0; i < totpatch; i++){
		bezieToTriangles(tess,i,file,paches,pontos);
	}
	file.close();
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
