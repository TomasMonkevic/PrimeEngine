#pragma once

#include <vector>
#include "../Camera.h"
#include "../Renderer2D.h"
#include "../BatchRenderer2D.h"
#include <Components/Object.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Layer
	{
	protected:
		Renderer2D* _renderer;
		std::vector<Object*>* _renderables;
		Shader* _shader;
		Camera* _camera;

	protected:
		Layer(Renderer2D* renderer, Shader* shader, Camera* camera); //add without camera obj
		void Submit(Object* object);
		void Remove(Object* object);

	public:
		virtual ~Layer();
		void Render();
	};
}}

