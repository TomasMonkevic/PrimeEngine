#include "GameObject.h"
#include <Graphics\Sprite.h>

namespace PrimeEngine {

	GameObject::GameObject() :
		GameObject(Math::Vector3::zero)
	{

	}

	GameObject::GameObject(const Math::Vector3& position)
	{
		_components = new std::vector<Component*>;
		_children = new std::vector<GameObject*>;
		AddComponent(new Transform(position));
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < (*_components).size(); i++)
		{
			delete (*_components)[i];
		}
		delete _components;
		//also delete all children???
		delete _children;
	}

	void GameObject::Add(GameObject* child)
	{
		_children->push_back(child);
	}

	void GameObject::Submit(Graphics::Renderer2D* renderer) const
	{
		Graphics::Sprite* sprite = GetComponent<Graphics::Sprite>();
		if (sprite)
		{
			sprite->Submit(renderer);
		}
		//could be added a local position and a global. better for performance
		renderer->PushMatrix(GetTransform().GetModelMatrix());
		for (const GameObject* child : *_children)
		{
			child->Submit(renderer);
		}
		renderer->PopMatrix();
	}
}