#pragma once

#include <vector>
#include "../Camera.h"
#include "../Renderer2D.h"
#include "../BatchRenderer2D.h"
#include <Components\Object.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Layer
	{
	protected:
		Renderer2D* _renderer;
		std::vector<Object*>* _renderables;

	public:
		Camera* camera;

	protected:
		Layer(Renderer2D* renderer, Camera* _camera); //add without camera obj
		void Submit(Object* object);
		void Remove(Object* object);

	public:
		virtual ~Layer();
		void Render();
	};
}}

