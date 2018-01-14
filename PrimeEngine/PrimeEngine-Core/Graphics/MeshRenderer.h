#pragma once

#include "../Components/Component.h"
#include "Mesh.h"
#include "Shader\Shader.h"
#include "../GameObject.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"

namespace PrimeEngine { namespace Graphics {
	
	//TODO later derive from renderable
	class PRIMEENGINEAPI MeshRenderer : public Component
	{
	private:
		Mesh* _mesh;
		Material* _material;
	public:
		MeshRenderer(Mesh* mesh, Material* material);
		virtual ~MeshRenderer();

		void Draw(const Camera& camera);
		Component* Copy() override;
	};
}}
