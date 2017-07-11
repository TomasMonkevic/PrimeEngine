#pragma once

#include <DllExport.h>
#include <Components\Component.h>
#include <Math\Math.h>
#include <vector>

namespace PrimeEngine {

	class Transform;

	class PRIMEENGINEAPI GameObject 
	{
	private:
		std::vector<Component> _components;
		//transform component is mandatory
	public:
		void Init(); //create transform component
		GameObject();
		GameObject(const Math::Vector3& position);

		void AddComponent(const Component& component); //generic
		void GetComponent(); //should be generic
		void GetComponents(); //should be generic

		Transform& Transform();
	};
}