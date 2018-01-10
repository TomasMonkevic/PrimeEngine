#pragma once

#include <Graphics\Camera.h>
#include <GameObject.h>
#include <DllExport.h>

namespace PrimeEngine {

	using namespace Graphics;
	using std::vector;

	class PRIMEENGINEAPI Scene
	{
	private:
		Camera* const _camera;
		vector<GameObject*>* _gameObjects;

	public:
		Scene(Camera* const camera);
		~Scene();

		void Add(GameObject* gameObject);
		void Remove();
		void Get();

		void Update();
		void Render();
	};
}