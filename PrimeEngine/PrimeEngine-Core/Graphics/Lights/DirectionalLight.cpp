#include "DirectionalLight.h"

namespace PrimeEngine { namespace Graphics { namespace Lights {

	DirectionalLight::DirectionalLight(const Color& color, float intensity)
		: Light(color, intensity)
	{

	}

	void DirectionalLight::Enable(Shader& shader, unsigned i) const
	{
		shader.SetUniform("directionalLight.color", _color);
		shader.SetUniform("directionalLight.intensity", _intensity);
		shader.SetUniform("directionalLight.direction", GetTransform().Forward());
	}

} } }