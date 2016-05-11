#include "Scene.h"

Scene::Scene()
{
}

void Scene::apply(float timePerFrame)
{
	
	for (int i = 0; i < lights.size(); i++) {
		glEnable(GL_LIGHT0 + i);
		lights[i].apply(i);
	}
	for each (Referencial ref in refs)
	{
		ref.apply(timePerFrame);
	}

	for (int i = 0; i < lights.size(); i++) {
		glDisable(GL_LIGHT0 + i);
	}

}

void Scene::addReferencial(Referencial ref)
{
	this->refs.push_back(ref);
}

void Scene::addLight(Light l)
{
	this->lights.push_back(l);
}
