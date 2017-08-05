#pragma once

#include <DllExport.h>
#include <GameObject.h>

namespace PrimeEngine { namespace UI {

	class PRIMEENGINEAPI UIObject : public Object
	{
	protected:
		GameObject* const _gameObject;
	protected:
		explicit UIObject() : _gameObject(new GameObject()) {}
		virtual ~UIObject() { delete _gameObject; }
	public:
		void Submit(Graphics::Renderer2D* renderer) const override { _gameObject->Submit(renderer); }
	};
}}