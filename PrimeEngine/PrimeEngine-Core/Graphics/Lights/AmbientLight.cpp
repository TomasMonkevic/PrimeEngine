#include "AmbientLight.h"

namespace PrimeEngine { namespace Graphics { namespace Lights {

	AmbientLight::AmbientLight(const Color& color, float intensity)
		: Light(color,intensity)
	{
	}

	void AmbientLight::Enable(Shader& shader, unsigned i) const
	{
		shader.SetUniform("ambientLight.color", _color);
		shader.SetUniform("ambientLight.intensity", _intensity);
	}

} } }