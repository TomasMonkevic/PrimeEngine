#pragma once

#include <Graphics/Camera.h>
#include <GameObject.h>
#include <Graphics/Lights/Light.h>
#include <DllExport.h>

namespace PrimeEngine {

	using namespace Graphics;
	using namespace Lights;
	using std::vector;

	class PRIMEENGINEAPI Scene
	{
	private:
		Camera* const _camera;
		vector<GameObject*>* _gameObjects;
		vector<Light*>* _lights;

	public:
		Scene(Camera* const camera);
		~Scene();

		void Add(GameObject* gameObject);
		void Add(Light* light);
		void Remove();
		void Get();

		void Update();
		void Render();
	};
}