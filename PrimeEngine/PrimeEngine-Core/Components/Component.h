#pragma once

#include <DllExport.h>

namespace PrimeEngine {

	class GameObject;

	class PRIMEENGINEAPI Component
	{
		friend class GameObject;
	private:
		GameObject* _gameObject;
	protected:
		Component() {}
	public:
		virtual ~Component() {}
		inline GameObject* const GetGameObject() const
		{
			return _gameObject;
		}
	};
}
