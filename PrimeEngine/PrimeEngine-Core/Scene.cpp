#include "Scene.h"
#include <Graphics\MeshRenderer.h>

namespace PrimeEngine {

	Scene::Scene(Camera* const camera)
		: _camera(camera)
	{
		_gameObjects = new std::vector<GameObject*>;
	}

	Scene::~Scene()
	{
		for (int i = 0; i < _gameObjects->size(); i++)
		{
			delete (*_gameObjects)[i];
		}
		delete _gameObjects;
		delete _camera;
	}

	void Scene::Add(GameObject* gameObject)
	{
		_gameObjects->push_back(gameObject);
	}

	void Scene::Add(Light* light)
	{
		_lights->push_back(light);
	}

	void Scene::Update()
	{

	}

	//TODO currently will only work with 3d
	void Scene::Render()
	{
		for (const GameObject* gameObject : *_gameObjects)
		{
			MeshRenderer* renderable = gameObject->GetComponent<MeshRenderer>(); //change to renderable
			if (renderable)
			{
				renderable->Draw(*_camera);
			}
		}
	}
}