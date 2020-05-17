#pragma once

#include "Light.h"

namespace PrimeEngine { namespace Graphics { namespace Lights {

	class PRIMEENGINEAPI SpotLight : public Light
	{
	private:
		float _range;
		float _angle;
		float _smoothEdge;

	public:
		SpotLight(const Color& color, float intensity, float angle, float range, float smoothEdge);

		void Enable(Shader& shader, unsigned i) const override;
	};

} } }
