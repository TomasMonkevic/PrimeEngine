#pragma once

#include <Graphics\Renderer2D.h>

namespace PrimeEngine {

	class Object 
	{
	public:
		virtual ~Object() {}
		virtual void Submit(Graphics::Renderer2D* renderer) const = 0;
	};
}