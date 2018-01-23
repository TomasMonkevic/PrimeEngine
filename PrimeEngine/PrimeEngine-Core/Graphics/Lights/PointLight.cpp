#include "PointLight.h"

namespace PrimeEngine { namespace Graphics { namespace Lights {

	PointLight::PointLight(const Color& color, float intensity, float range)
		: Light(color,intensity), _range(range)
	{
	}

	void PointLight::Enable(Shader& shader, unsigned i) const
	{
		char buffer[64];
		sprintf_s(buffer, 64, "lights[%i].position", i);
		shader.SetUniform(buffer, GetTransform().Position);

		sprintf_s(buffer, 64, "lights[%i].color", i);
		shader.SetUniform(buffer, _color);

		sprintf_s(buffer, 64, "lights[%i].intensity", i);
		shader.SetUniform(buffer, _intensity);

		sprintf_s(buffer, 64, "lights[%i].range", i);
		shader.SetUniform(buffer, _range);
	}

} } }