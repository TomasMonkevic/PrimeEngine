#ifndef SIMPLE_RENDERER2D
#define SIMPLE_RENDERER2D

#include "Renderer2D.h"
#include <queue>
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI SimpleRenderer2D : public Renderer2D
	{
	private:
		std::queue<const Renderable2D*>* _renderQueue;
	public:
		SimpleRenderer2D();
		~SimpleRenderer2D();
		void Submit(const Renderable2D* renderable2D) override;
		void Flush() override;
	};
}}

#endif // !SIMPLE_RENDERER2D