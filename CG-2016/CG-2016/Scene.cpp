#include "Scene.h"

Scene::Scene()
{
}

void Scene::Apply(float timePerFrame)
{
	for each (Referencial ref in refs)
	{
		ref.apply(timePerFrame);
	}
}

void Scene::addReferencial(Referencial ref)
{
	this->refs.push_back(ref);
}

void Scene::addLights(Light l)
{
	this->lights.push_back(l);
}
