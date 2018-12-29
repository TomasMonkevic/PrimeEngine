#include "PointLight.h"
#include <Utilities/Utils.h>

namespace PrimeEngine { namespace Graphics { namespace Lights {

	PointLight::PointLight(const Color& color, float intensity, float range)
		: Light(color,intensity), _range(range)
	{
	}

	void PointLight::Enable(Shader& shader, unsigned i) const
	{
		char buffer[64];
		PrimeEngine::Sprintf(buffer, "lights[%i].position", i);
		shader.SetUniform(buffer, GetTransform().Position);

		PrimeEngine::Sprintf(buffer, "lights[%i].color", i);
		shader.SetUniform(buffer, _color);

		PrimeEngine::Sprintf(buffer, "lights[%i].intensity", i);
		shader.SetUniform(buffer, _intensity);

		PrimeEngine::Sprintf(buffer, "lights[%i].range", i);
		shader.SetUniform(buffer, _range);
	}

} } }