#include "GameObject.h"

namespace PrimeEngine {

	GameObject::GameObject() :
		GameObject(Math::Vector3::zero)
	{

	}

	GameObject::GameObject(const Math::Vector3& position)
	{
		_components = new std::vector<Component*>;
		(*_components).push_back(new Transform(position));
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < (*_components).size(); i++)
		{
			delete (*_components)[i];
		}
		delete _components;
	}
}