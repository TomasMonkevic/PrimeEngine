#ifndef RENDERER2D
#define RENDERER2D

#include "Renderable2D.h"
#include "..\DllExport.h"

struct VertexData
{
	PrimeEngine::Math::Vector3 position;
	PrimeEngine::Math::Vector4 color;
};

namespace PrimeEngine { namespace Graphics {


	class PRIMEENGINEAPI Renderer2D
	{
	public:
		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable2D) = 0;
		virtual void End() {}
		virtual void Flush() = 0;
	};
}}

#endif // !RENDERER2D