#pragma once

#include <DllExport.h>
#include <vector>
#include <typeinfo>

namespace PrimeEngine {

	class GameObject;

	class PRIMEENGINEAPI Component
	{
		friend class GameObject;
	private:
		GameObject* _gameObject = NULL;
		std::vector<std::size_t>* _types;
	protected:
		Component() 
		{
			_types = new std::vector<std::size_t>();
		}

		Component(const Component& right) //TODO should be explicit?
		{
			_gameObject = right._gameObject;
			_types = new std::vector<std::size_t>(); //TODO copy constructor in vector???
			for (unsigned i = 0; i < right._types->size(); i++)
			{
				_types->push_back(right._types->at(i));
			}
		}

		template<typename T>
		void AddType()
		{
			_types->push_back(typeid(T).hash_code());
		}

	public:

		virtual ~Component() 
		{
			delete _types;
		}

		template<typename T>
		const std::size_t IsOfType() const
		{
			for (unsigned i = 0; i < _types->size(); i++)
			{
				if (_types->at(i) == typeid(T).hash_code())
				{
					return true;
				}
			}
			return false;
		}

		inline GameObject* const GetGameObject() const
		{
			return _gameObject;
		}

		//inline const Transform& Transform() const
		//{
		//	return _gameObject->GetTransform();
		//}

		virtual Component* Copy() = 0;
	};
}
