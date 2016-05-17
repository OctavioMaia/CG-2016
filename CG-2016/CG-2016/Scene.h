#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Light.h"
#include "Referencial.h"

class Scene {
private:
	vector<Light> lights;
	vector<Referencial> refs;

public:
	Scene();
	void apply(float timePerFrame);
	void addReferencial(Referencial ref);
	void addLight(Light l);
};

#endif // !SCENE_H