#pragma once

#include <DllExport.h>
//#include <Components\Component.h>
#include <Components\Transform.h>
#include <Math\Math.h>
#include <vector>
#include <Utilities\Log.h>

namespace PrimeEngine {

	class PRIMEENGINEAPI GameObject 
	{
	private:
		std::vector<Component*>* _components;
		//transform component is mandatory
	public:
		explicit GameObject();
		explicit GameObject(const Math::Vector3& position);
		~GameObject();

		//Takes control over components. Always use new
		void AddComponent(Component* component) //make move?
		{
			_components->push_back(component);
		}

		template<typename T>
		T* GetComponent() const
		{
			for (int i = 0; i < (*_components).size(); i++)
			{
				//PRIME_INFO(typeid(T).name(), " ", typeid(*((*_components)[i])).name(), "\n");
				if (typeid(T) == typeid(*((*_components)[i])))
				{
					//casting isn't good
					//change to a std casting
					return (T*)(*_components)[i];
				}
			}
			return NULL;
		}
		//void GetComponents(); //should be generic

		inline Transform& GetTransform()
		{
			//transform is always there at index 0
			//change to a std casting
			return *((Transform*)((*_components)[0]));
		}
	};
}