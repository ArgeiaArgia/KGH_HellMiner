#include "Scene.h"
#include "Defines.h"

Scene::~Scene()
{
	for (auto& obj : objects)
	{
		SAFE_DELETE(obj);
	}
	objects.clear();
}

void Scene::Init()
{
	for (auto& obj : objects) 
	{
		obj->Init();
	}
}

void Scene::Update()
{
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

void Scene::Render() const
{
	for (auto obj : objects)
	{
		obj->Render();
	}
}
