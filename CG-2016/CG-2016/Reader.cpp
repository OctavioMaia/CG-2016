#include "Reader.h"

unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}
	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

void readModels(TiXmlElement* elem, Referencial* ref) {
	const char* filemodelo;
	TiXmlElement* elemFunc = elem->FirstChildElement("models");

	for (elemFunc = elemFunc->FirstChildElement("model"); elemFunc != NULL; elemFunc = elemFunc->NextSiblingElement()) {

		filemodelo = elemFunc->Attribute("file");

		vector<string> campos;
		string line;
		int nVertices;

		ifstream myfile(filemodelo);

		getline(myfile, line);
		nVertices = stoi(line);

		getline(myfile, line);
		split(line, campos, ';');
		int enablePoints = stoi(campos[0]);
		int enableNormals = stoi(campos[1]);
		int enableTextures = stoi(campos[2]);

		Figura fg = Figura::Figura(filemodelo, NULL, nVertices, false);

		for (int i = 0; i < nVertices; i++)
		{
			if (enablePoints == 1) {
				getline(myfile, line);
				campos.clear();
				split(line, campos, ';');
				fg.addPonto(stold(campos[0]), stold(campos[1]), stold(campos[2]));
			}
			
			if (enableNormals == 1) {
				getline(myfile, line);
				campos.clear();
				split(line, campos, ';');
				fg.addNormal(stof(campos[0]), stof(campos[1]), stof(campos[2]));
			}
			
			if (enableTextures == 1) {
				getline(myfile, line);
				campos.clear();
				split(line, campos, ';');
				fg.addTextur(stof(campos[0]), stof(campos[1]));
			}
			
		}


		if (const char* valeu = elemFunc->Attribute("texture")) {
			fg.setTextureFile(string(valeu));
		}
		else {
			//de futuro verificar se podem existir as outras componentes
			const char* diffR = elemFunc->Attribute("diffR");
			const char* diffG = elemFunc->Attribute("diffG");
			const char* diffB = elemFunc->Attribute("diffB");
			if(diffR && diffG && diffB){
				fg.setDiff(atof(diffR), atof(diffG), atof(diffB));
			}else{
				fg.setEnableLights(true);
			}
		}

		ref->addFigura(fg);

		myfile.close();

	}
}

void readTranslate(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;

	Translacao trans = Translacao::Translacao();

	if ((elem1 = elem->FirstChildElement("translate")) != NULL) {

		const char* valeu;

		if (valeu = elem1->Attribute("time")) {
			trans.setTime(atof(valeu));
		}

		TiXmlElement* elemPoint = elem1->FirstChildElement("point");
		for (; elemPoint != NULL; elemPoint = elemPoint->NextSiblingElement()) {
			Ponto p = Ponto::Ponto();

			if (valeu = elemPoint->Attribute("X")) {
				p.setX(atof(valeu));
			}

			if (valeu = elemPoint->Attribute("Y")) {
				p.setY(atof(valeu));
			}

			if (valeu = elemPoint->Attribute("Z")) {
				p.setZ(atof(valeu));
			}

			trans.addPoint(p);
		}

		ref->addTransformation(trans);
	}
}

void readScale(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;

	Escala scale = Escala::Escala();

	//<scale X = "0.5" Y = "0.5" Z = "0.5" / >

	if ((elem1 = elem->FirstChildElement("scale")) != NULL) {

		const char* valeu;

		if (valeu = elem1->Attribute("X")) {
			scale.setX(atof(valeu));
		}

		if (valeu = elem1->Attribute("Y")) {
			scale.setY(atof(valeu));
		}
		if (valeu = elem1->Attribute("Z")) {
			scale.setZ(atof(valeu));
		}
		ref->addTransformation(scale);
	}
}

void readRotate(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;

	//<rotate angle="45" axisX="0" axisY="1" axisZ="0" />
	Rotacao rot = Rotacao::Rotacao();

	if ((elem1 = elem->FirstChildElement("rotate")) != NULL) {
		const char* valeu;;

		if (valeu = elem1->Attribute("time")) {
			rot.setTime(atof(valeu));
		}

		if (valeu = elem1->Attribute("axisX")) {
			rot.setX(atof(valeu));
		}
		if (valeu = elem1->Attribute("axisY")) {
			rot.setY(atof(valeu));
		}
		if (valeu = elem1->Attribute("axisZ")) {
			rot.setZ(atof(valeu));
		}
		ref->addTransformation(rot);
	}

}

void readLights(TiXmlElement* elem, Scene* scene) {

	TiXmlElement* newElem = elem->FirstChildElement("lights");

	for (newElem = newElem->FirstChildElement("light"); newElem != NULL; newElem = newElem->NextSiblingElement()) {
		const char* valeu;

		Light light = Light::Light();

		if (valeu = newElem->Attribute("type")) {
			light.setType(string(valeu));
		}

		if (valeu = newElem->Attribute("posX")) {
			light.setPosX(atof(valeu));
		}
		if (valeu = newElem->Attribute("posY")) {
			light.setPosY(atof(valeu));
		}
		if (valeu = newElem->Attribute("posZ")) {
			light.setPosZ(atof(valeu));
		}
		scene->addLight(light);
	}

}

void loadElementChild(TiXmlElement* elem, Referencial* refPai) {

	TiXmlElement* elemFunc = elem;

	readTranslate(elemFunc, refPai);
	readRotate(elemFunc, refPai);
	readScale(elemFunc, refPai);
	readModels(elemFunc, refPai);

	for (elemFunc = elemFunc->FirstChildElement("group"); elemFunc != NULL; elemFunc = elemFunc->NextSiblingElement()) {
		Referencial refFilho = Referencial::Referencial();

		loadElementChild(elemFunc, &refFilho);

		refPai->addFilho(refFilho);
	}
}

Scene readFileXML(const char* file) {

	Scene princRef = Scene::Scene();

	TiXmlDocument doc;

	if (doc.LoadFile(file))
	{
		try
		{
			readLights(doc.FirstChildElement("scene"), &princRef);

			for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("group"); elem != NULL; elem = elem->NextSiblingElement()) {
				Referencial local = Referencial::Referencial();

				loadElementChild(elem, &local);

				princRef.addReferencial(local);
			}
		}
		catch (const std::exception&)
		{
			printf("Failed to load file \"%s\"\n", file);
		}
	}
	else
	{
		printf("Failed to open file \"%s\"\n", file);
	}
}

