#pragma once

#include "Renderer2D.h"
#include <DllExport.h>
#include <Components\Component.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Renderable : public Component
	{
	protected:
		explicit Renderable()
		{
			AddType<Renderable>();
		}
	public:
		virtual void Submit(Renderer2D* renderer) const = 0;
	};
}}