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

		if (!myfile) {
			cout << "Não foi possivel encontrar o ficheiro " << filemodelo << endl;
			break;
		}

		getline(myfile, line);
		split(line, campos, ';');
		int enablePoints = stoi(campos[0]);
		int enableNormals = stoi(campos[1]);
		int enableTextures = stoi(campos[2]);

		getline(myfile, line);
		nVertices = stoi(line);

		Figura fg = Figura::Figura(filemodelo, "", nVertices, false);

		for (int i = 0; i < nVertices; i++)
		{
			if (enablePoints == 1) {
				getline(myfile, line);
				campos.clear();
				split(line, campos, ';');
				if (campos.size()==3) {
					fg.addPonto(stold(campos[0]), stold(campos[1]), stold(campos[2]));
				}
				
			}

			if (enableNormals == 1) {
				getline(myfile, line);
				campos.clear();
				split(line, campos, ';');
				if (campos.size()==3){
					fg.addNormal(stof(campos[0]), stof(campos[1]), stof(campos[2]));
				}
			}

			if (enableTextures == 1) {
				getline(myfile, line);
				campos.clear();
				split(line, campos, ';');
				if (campos.size()==2) {
					fg.addTextur(stof(campos[0]), stof(campos[1]));
				}
			}

		}

		if (const char* valeu = elemFunc->Attribute("texture")) {
			fg.setTextureFile(string(valeu));
		}

		//de futuro verificar se podem existir as outras componentes
		const char* diffR = elemFunc->Attribute("diffR");
		const char* diffG = elemFunc->Attribute("diffG");
		const char* diffB = elemFunc->Attribute("diffB");
		if (diffR && diffG && diffB) {
			fg.setDiff(atof(diffR), atof(diffG), atof(diffB));
		}
		//de futuro verificar se podem existir as outras componentes
		const char* ambR = elemFunc->Attribute("ambR");
		const char* ambG = elemFunc->Attribute("ambG");
		const char* ambB = elemFunc->Attribute("ambB");
		if (ambR && ambG && ambB) {
			fg.setAmb(atof(ambR), atof(ambG), atof(ambB));
		}
		//de futuro verificar se podem existir as outras componentes
		const char* emisR = elemFunc->Attribute("emisR");
		const char* emisG = elemFunc->Attribute("emisG");
		const char* emisB = elemFunc->Attribute("emisB");
		if (emisR && emisG && emisB) {
			fg.setEmis(atof(diffR), atof(diffG), atof(diffB));
		}
		//de futuro verificar se podem existir as outras componentes
		const char* espcR = elemFunc->Attribute("espcR");
		const char* espcG = elemFunc->Attribute("espcG");
		const char* espcB = elemFunc->Attribute("espcB");
		if (espcR && espcG && espcB) {
			fg.setEsp(atof(espcR), atof(espcG), atof(espcB));
		}

		ref->addFigura(fg);

		myfile.close();
	}
}

void readTranslate(TiXmlElement* elem, Referencial* ref) {
	
	TiXmlElement* elem1;
	Translacao trans1 = Translacao::Translacao();

	if ((elem1 = elem->FirstChildElement("translate")) != NULL) {
		const char* valeu;

		if (valeu = elem1->Attribute("time")) {
			trans1.setTime(atof(valeu));

			TiXmlElement* elemPoint = elem1->FirstChildElement("point");
			if (elemPoint != NULL) {
				for (; elemPoint != NULL; elemPoint = elemPoint->NextSiblingElement()) {
					Ponto p = Ponto::Ponto();

					if (valeu = elemPoint->Attribute("X")) { p.setX(atof(valeu)); }
					if (valeu = elemPoint->Attribute("Y")) { p.setY(atof(valeu)); }
					if (valeu = elemPoint->Attribute("Z")) { p.setZ(atof(valeu)); }
					trans1.addPoint(p);
				}
			}
		}else{
			Ponto p = Ponto::Ponto();
			if (valeu = elem1->Attribute("X")) { p.setX(atof(valeu)); }
			if (valeu = elem1->Attribute("Y")) { p.setY(atof(valeu)); }
			if (valeu = elem1->Attribute("Z")) { p.setZ(atof(valeu)); }
			trans1.setTrans(p);
		}
		Transformation t = (Transformation)malloc(sizeof(struct transformation));
		t->type = TRANSLACAO;
		t->transl = trans1;

		ref->addTransformation(t);
	}
}

void readScale(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;
	Escala scale = Escala::Escala();

	if ((elem1 = elem->FirstChildElement("scale")) != NULL) {
		const char* valeu;

		if (valeu = elem1->Attribute("X")) { scale.setX(atof(valeu)); }
		if (valeu = elem1->Attribute("Y")) { scale.setY(atof(valeu)); }
		if (valeu = elem1->Attribute("Z")) {	scale.setZ(atof(valeu)); }

		Transformation t = (Transformation)malloc(sizeof(struct transformation));
		t->type = ESCALA;
		t->scale = scale;
		ref->addTransformation(t);
	}
}

void readRotate(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;
	Rotacao rot = Rotacao::Rotacao();

	if ((elem1 = elem->FirstChildElement("rotate")) != NULL) {
		const char* valeu;;
		if (valeu = elem1->Attribute("time")) { rot.setTime(atof(valeu)); }
		if (valeu = elem1->Attribute("axisX")) { rot.setX(atof(valeu)); }
		if (valeu = elem1->Attribute("axisY")) { rot.setY(atof(valeu)); }
		if (valeu = elem1->Attribute("axisZ")) { rot.setZ(atof(valeu)); }

		Transformation t = (Transformation)malloc(sizeof(struct transformation));
		t->type = ROTACAO;
		t->rot = rot;
		ref->addTransformation(t);
	}

}

void readLights(TiXmlElement* elem, Scene* scene) {

	TiXmlElement* newElem = elem;

	for (newElem = newElem->FirstChildElement("light"); newElem != NULL; newElem = newElem->NextSiblingElement()) {

		const char* valeu;

		Light light = Light::Light();
		if (valeu = newElem->Attribute("posX")) { light.setPosX(atof(valeu)); }
		if (valeu = newElem->Attribute("posY")) { light.setPosY(atof(valeu)); }
		if (valeu = newElem->Attribute("posZ")) { light.setPosZ(atof(valeu)); }
		if (valeu = newElem->Attribute("type")) { light.setType(string(valeu)); }

		//componente difusa
		const char* diffR = newElem->Attribute("diffR");
		const char* diffG = newElem->Attribute("diffG");
		const char* diffB = newElem->Attribute("diffB");
		if (diffR && diffG && diffB) {
			light.setDiff(atof(diffR), atof(diffG), atof(diffB));
		}
		//componente ambiente
		const char* ambR = newElem->Attribute("ambR");
		const char* ambG = newElem->Attribute("ambG");
		const char* ambB = newElem->Attribute("ambB");
		if (ambR && ambG && ambB) {
			light.setAmb(atof(ambR), atof(ambG), atof(ambB));
		}
		//componente emissiva
		const char* emisR = newElem->Attribute("emisR");
		const char* emisG = newElem->Attribute("emisG");
		const char* emisB = newElem->Attribute("emisB");
		if (emisR && emisG && emisB) {
			light.setEmis(atof(diffR), atof(diffG), atof(diffB));
		}
		//componente especular
		const char* espcR = newElem->Attribute("espcR");
		const char* espcG = newElem->Attribute("espcG");
		const char* espcB = newElem->Attribute("espcB");
		if (espcR && espcG && espcB) {
			light.setEspc(atof(espcR), atof(espcG), atof(espcB));
		}

		//spotLight
		if (strcmp(valeu, "SPOTLIGHT")) {
			const char* spotX = newElem->Attribute("spotX");
			const char* spotY = newElem->Attribute("spotY");
			const char* spotZ = newElem->Attribute("spotZ");
			const char* spotAngle = newElem->Attribute("spotAngle");
			if (spotX && spotY && spotZ) {
				light.setSpotDir(atof(spotX), atof(spotY), atof(spotZ), atof(spotAngle));
			}
		}
		scene->addLight(light);
	}

}

void loadElementChild(TiXmlElement* elem, Referencial* refPai) {

	TiXmlElement* elemFunc = elem;

	for (TiXmlElement* elemTrans = elem->FirstChildElement(); elemTrans != NULL;elemTrans = elemTrans->NextSiblingElement()) {
		if (!string(elemTrans->Value()).compare("translate")) { readTranslate(elemFunc, refPai); }
		if (!string(elemTrans->Value()).compare("rotate")) { readRotate(elemFunc, refPai); }
		if (!string(elemTrans->Value()).compare("scale")) {	readScale(elemFunc, refPai); }
		if (!string(elemTrans->Value()).compare("models")) { readModels(elemFunc, refPai); }
		if (!string(elemTrans->Value()).compare("group")) {
			Referencial refFilho = Referencial::Referencial();
			loadElementChild(elemTrans, &refFilho);
			refPai->addFilho(refFilho);
		}
	}
}

Scene readFileXML(const char* file) {

	Scene scene = Scene::Scene();

	TiXmlDocument doc;

	if (doc.LoadFile(file))
	{
		try
		{
			if (doc.FirstChildElement("scene")->FirstChildElement("lights") != NULL) {
				readLights(doc.FirstChildElement("scene")->FirstChildElement("lights"), &scene);
			}
			for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("group"); elem != NULL; elem = elem->NextSiblingElement()) {
				Referencial local = Referencial::Referencial();
				loadElementChild(elem, &local);
				scene.addReferencial(local);
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
	return scene;
}
