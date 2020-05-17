#pragma once

#include "Component.h"
#include <DllExport.h>

namespace PrimeEngine {

	class PRIMEENGINEAPI Behaviour : public Component
	{
	protected:
		Behaviour()
		{
			AddType<Behaviour>();
		}

	public:
		virtual void Awake() {};
		virtual void Start() {};
		virtual void Update(float deltaTime) {};
	};
}