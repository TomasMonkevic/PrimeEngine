#ifndef PRIME_LAYER_H
#define PRIME_LAYER_H

#include <vector>
#include "../Camera.h"
#include "../Renderer2D.h"
#include "../BatchRenderer2D.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Layer
	{
	protected:
		Renderer2D* _renderer;
		std::vector<Renderable2D*>* _renderables;

	public:
		Camera* camera;

	protected:
		Layer(Renderer2D* renderer, Camera* _camera); //add without camera obj

	public:
		virtual ~Layer();

		void Submit(Renderable2D* renderable);
		void Remove(Renderable2D* renderable);
		void Render();
	};
}}

#endif // !PRIME_LAYER_H

