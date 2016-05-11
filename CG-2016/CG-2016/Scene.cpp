#include "Scene.h"

Scene::Scene()
{
}

void Scene::apply(float timePerFrame)
{
	for (int i = 0; i < lights.size(); i++) {
		lights[i].apply(i);
		glEnable(GL_LIGHT0 + i);
	}
	glEnable(GL_LIGHTING);
	for (int i = 0; i < refs.size(); i++) {
		refs[i].apply(timePerFrame);
	}
	/*for (int i = 0; i < lights.size(); i++) {
		glDisable(GL_LIGHT0 + i);
	}*/
}

void Scene::addReferencial(Referencial ref)
{
	this->refs.push_back(ref);
}

void Scene::addLight(Light l)
{
	this->lights.push_back(l);
}
