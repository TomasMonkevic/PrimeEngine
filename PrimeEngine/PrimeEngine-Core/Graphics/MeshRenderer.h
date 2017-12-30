#pragma once

#include "../Components/Component.h"
#include "Mesh.h"
#include "Shader\Shader.h"
#include "../GameObject.h"
#include "Camera.h"

namespace PrimeEngine { namespace Graphics {
	
	//TODO later derive from renderable
	class PRIMEENGINEAPI MeshRenderer : public Component
	{
	private:
		Mesh* _mesh;
		//TODO later change to a material component
		Shader* _material;
	public:
		MeshRenderer(Mesh* mesh, Shader* shader);
		virtual ~MeshRenderer();

		void Draw(const Camera& camera);
		Component* Copy() override;
	};
}}
