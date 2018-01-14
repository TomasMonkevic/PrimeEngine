#pragma once

#include "Shader\Shader.h"
#include "Camera.h"
#include <GameObject.h>
#include "Color.h"
#include "Texture.h"
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {
	
	class MeshRenderer;
	using namespace PrimeEngine::Math;

	class PRIMEENGINEAPI Material
	{
		friend class MeshRenderer;
	private:
		Shader* _shader;
		Color _diffuseColor;
		Texture* _diffuseMap;
		Texture* _specularMap;
		float _smoothness;

	private:
		void Enable(const Camera& camera, const GameObject& gameObject) const;
		void Disable() const;
		Material(Texture* diffMap, Texture* specMap, const Color& color, float smoothness);

	public:
		Material(const Color& color = Color::white);
		Material(Texture* diffMap, Texture* specMap = nullptr);
		~Material();
	};

} }