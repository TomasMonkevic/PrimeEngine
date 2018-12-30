#include "PointLight.h"
#include <Utilities/Utils.h>

namespace PrimeEngine { namespace Graphics { namespace Lights {

	PointLight::PointLight(const Color& color, float intensity, float range)
		: Light(color,intensity), _range(range)
	{
	}

	void PointLight::Enable(Shader& shader, unsigned i) const
	{
		const int BUFFER_SIZE = 64;
		char buffer[BUFFER_SIZE];
		PrimeEngine::Sprintf(buffer, BUFFER_SIZE, "lights[%i].position", i);
		shader.SetUniform(buffer, GetTransform().Position);

		PrimeEngine::Sprintf(buffer, BUFFER_SIZE, "lights[%i].color", i);
		shader.SetUniform(buffer, _color);

		PrimeEngine::Sprintf(buffer, BUFFER_SIZE, "lights[%i].intensity", i);
		shader.SetUniform(buffer, _intensity);

		PrimeEngine::Sprintf(buffer, BUFFER_SIZE, "lights[%i].range", i);
		shader.SetUniform(buffer, _range);
	}

} } }