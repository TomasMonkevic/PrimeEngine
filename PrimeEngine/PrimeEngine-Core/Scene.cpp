#include "Scene.h"
#include <Graphics/MeshRenderer.h>

namespace PrimeEngine {

	Scene::Scene(Camera* const camera)
		: _camera(camera)
	{
		_gameObjects = new std::vector<GameObject*>;
		_lights = new std::vector<Light*>;
	}

	Scene::~Scene()
	{
		for (int i = 0; i < _gameObjects->size(); i++)
		{
			delete (*_gameObjects)[i];
		}
		delete _gameObjects;
		for (int i = 0; i < _lights->size(); i++)
		{
			delete (*_lights)[i];
		}
		delete _lights;
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
		//TODO this should be move to 3D renderer
		GlCall(glEnable(GL_DEPTH_TEST));
		for (const GameObject* gameObject : *_gameObjects)
		{
			MeshRenderer* renderable = gameObject->GetComponent<MeshRenderer>(); //change to renderable
			if (renderable)
			{
				renderable->Draw(*_camera, *_lights);
			}
		}
		GlCall(glDisable(GL_DEPTH_TEST));
	}
}