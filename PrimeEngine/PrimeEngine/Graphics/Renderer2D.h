#ifndef RENDERER2D
#define RENDERER2D

#include "Renderable2D.h"

namespace PrimeEngine { namespace Graphics {

	class Renderer2D
	{
	protected:
		virtual void Submit(const Renderable2D* renderable2D) = 0;
		virtual void Flush() = 0;
	};
}}

#endif // !RENDERER2D