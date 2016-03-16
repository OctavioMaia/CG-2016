#define _USE_MATH_DEFINES
#include <math.h>
#include "windows.h" 
#include <GL/glut.h>
#include <chrono>

#include "tinyxml.h"
#include "tinystr.h"

#include <iostream>
using namespace std;



void readTranslate(TiXmlElement* elem) {
	TiXmlElement* elem1;
	const char* teste;

	if ((elem1 = elem->FirstChildElement("translate")) != NULL) {

		cout << "translate\n";
		if (teste = elem1->Attribute("X")) {
			cout << "X=" << teste << "\n";
		}

		if (teste = elem1->Attribute("Y")) {
			cout << "Y=" << teste << "\n";
		}
		if (teste = elem1->Attribute("Z")) {
			cout << "Z=" << teste << "\n";
		}
		cout << "endTranslate\n";
	}
}


void readRotate(TiXmlElement* elem) {
	TiXmlElement* elem1;
	const char* teste;
	
	//<rotate angle="45" axisX="0" axisY="1" axisZ="0" />

	if ((elem1 = elem->FirstChildElement("rotate")) != NULL) {

		if (teste = elem1->Attribute("angle")) {
			cout << "angle=" << teste << "\n";
		}

		if (teste = elem1->Attribute("axisX")) {
			cout << "axisX=" << teste << "\n";
		}
		if (teste = elem1->Attribute("axisY")) {
			cout << "axisY=" << teste << "\n";
		}
		if (teste = elem1->Attribute("axisZ")) {
			cout << "axisZ=" << teste << "\n";
		}
	}

}


void loadElementChild(TiXmlElement* elem) {
	
	readTranslate(elem);
	readRotate(elem);

	for (elem= elem->FirstChildElement("group"); elem != NULL; elem = elem->NextSiblingElement()) {
		
		loadElementChild(elem);

	}
}


int main(int argc, char** argv) {

	char* pFilename = argv[1];


	TiXmlDocument doc;
	const char* file;

	if (doc.LoadFile(pFilename))
	{
		try
		{
			for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("group"); elem != NULL; elem = elem->NextSiblingElement()) {

			loadElementChild(elem);

			}
		}
		catch (const std::exception&)
		{
			cout << file << "\n";
			printf("Failed to load file \"%s\"\n", pFilename);
		}
	}
	else
	{
		printf("Failed to open file \"%s\"\n", pFilename);
	}
}