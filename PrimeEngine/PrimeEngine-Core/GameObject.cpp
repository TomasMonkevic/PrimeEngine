#include "GameObject.h"
#include <Graphics\Renderable.h>
#include <Graphics\Sprite.h>
#include <Graphics\Label.h>

namespace PrimeEngine {

	GameObject::GameObject() :
		GameObject(Math::Vector3::zero())
	{

	}

	GameObject::GameObject(const Math::Vector3& position)
	{
		_components = new std::vector<Component*>;
		_children = new std::vector<GameObject*>; //TODO should children be in gameObject
		AddComponent(new Transform(position));
	}

	GameObject::GameObject(const GameObject& obj)
	{
		_components = new std::vector<Component*>;
		_children = new std::vector<GameObject*>; //TODO should children be in gameObject
		for (int i = 0; i < obj._components->size(); i++) //for now only copy components
		{
			if (obj._components->at(i)->IsOfType<Transform>()) //TODO think about this ugly code
			{
				AddComponent(new Transform(*static_cast<Transform*>((*obj._components)[i])));
			}
			else if (obj._components->at(i)->IsOfType<Graphics::Sprite>())
			{
				AddComponent(new Graphics::Sprite(*static_cast<Graphics::Sprite*>((*obj._components)[i])));
			}
			else if (obj._components->at(i)->IsOfType<Graphics::Label>())
			{
				AddComponent(new Graphics::Label(*static_cast<Graphics::Label*>((*obj._components)[i])));
			}
		}
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < (*_components).size(); i++)
		{
			delete (*_components)[i];
		}
		delete _components;
		//TODO also delete all children???
		delete _children;
	}

	void GameObject::Add(GameObject* child)
	{
		_children->push_back(child);
	}

	void GameObject::Submit(Graphics::Renderer2D* renderer) const
	{
		Graphics::Renderable* sprite = GetComponent<Graphics::Renderable>();
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