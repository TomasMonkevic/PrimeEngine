#include "SpotLight.h"
#include <Math/MathFunc.h>

using namespace PrimeEngine::Math;

namespace PrimeEngine { namespace Graphics { namespace Lights {

	SpotLight::SpotLight(const Color& color, float intensity, float angle, float range, float smoothEdge)
		: Light(color,intensity), _angle(angle), _range(range), _smoothEdge(smoothEdge)
	{
	}

	void SpotLight::Enable(Shader& shader, unsigned i) const
	{
		shader.SetUniform("spotLight.position", GetTransform().Position);
		shader.SetUniform("spotLight.direction", GetTransform().Forward());
		shader.SetUniform("spotLight.color", _color);
		shader.SetUniform("spotLight.intensity", _intensity);
		shader.SetUniform("spotLight.angle", (float)std::cos(ToRadians(_angle)));
		shader.SetUniform("spotLight.range", _range);
		shader.SetUniform("spotLight.smoothEdge", (float)std::cos(ToRadians(_angle + _smoothEdge)));
	}

} } }