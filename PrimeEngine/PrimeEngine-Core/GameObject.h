#pragma once

#include <DllExport.h>
#include <Components\Transform.h>
#include <Math\Math.h>
#include <vector>
#include <Utilities\Log.h>
#include <Components\Object.h>

namespace PrimeEngine {

	class PRIMEENGINEAPI GameObject : public Object
	{
	private:
		std::vector<Component*>* _components;
		std::vector<GameObject*>* _children;
		//transform component is mandatory
	public:
		GameObject();
		GameObject(const Math::Vector3& position);
		GameObject(const GameObject& obj);

		virtual ~GameObject();

		void Add(GameObject* child);
		void Submit(Graphics::Renderer2D* renderer) const override;

		//Takes control over components. Always use new
		void AddComponent(Component* component) //make move?
		{
			component->_gameObject = this;
			_components->push_back(component);
		}

		template<typename T>
		T* GetComponent() const
		{
			for (int i = 0; i < (*_components).size(); i++)
			{
				if (_components->at(i)->IsOfType<T>())
				{
					return static_cast<T*>((*_components)[i]);
				}
			}
			return nullptr;
		}

		template<typename T>
		std::vector<T*> GetComponents() const
		{
			std::vector<T*> result;
			for (int i = 0; i < (*_components).size(); i++)
			{
				if (_components->at(i)->IsOfType<T>())
				{
					result.pop_back(static_cast<T*>((*_components)[i]));
				}
			}
			return result;
		}

		inline Transform& GetTransform() const
		{
			//transform is always there at index 0
			return static_cast<Transform&>(*_components->at(0));
		}
	};
}