#pragma once

#include <DllExport.h>
#include <typeinfo>

namespace PrimeEngine {

	class GameObject;

	class PRIMEENGINEAPI Component
	{
		friend class GameObject;
	private:
		GameObject* _gameObject;
		std::size_t _typeHash;
	protected:
		Component() {}
	public:
		virtual ~Component() 
		{
		}

		inline const std::size_t GetType() const
		{
			return _typeHash;
		}
		inline GameObject* const GetGameObject() const
		{
			return _gameObject;
		}
	};
}
