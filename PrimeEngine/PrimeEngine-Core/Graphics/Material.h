#pragma once

#include "Shader\Shader.h"
#include "Camera.h"
#include <GameObject.h>
#include "Color.h"
#include "Texture.h"
#include <DllExport.h>
#include "Lights\Light.h"

namespace PrimeEngine { namespace Graphics {
	
	class MeshRenderer;
	using namespace PrimeEngine::Math;
	using namespace Lights;

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
		void Enable(const Camera& camera, const GameObject& gameObject, const std::vector<Light*>& lights) const;
		void Disable() const;
		Material(const char* shaderSource, Texture* diffMap, Texture* specMap, const Color& color, float smoothness);

	public:
		Material(const char* shaderSource, const Color& color = Color::white);
		Material(const char* shaderSource, Texture* diffMap, Texture* specMap = nullptr);
		~Material();

		inline Color& DiffuseColor() { return _diffuseColor; }
		inline const Color DiffuseColor() const { return _diffuseColor; }

		inline float& Smoothness() { return _smoothness; }
		inline const float Smoothness() const { return _smoothness; }
	};

} }