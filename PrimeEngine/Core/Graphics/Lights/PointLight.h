#pragma once

#include "Light.h"

namespace PrimeEngine { namespace Graphics { namespace Lights {

	class PRIMEENGINEAPI PointLight : public Light
	{
	private:
		float _range;

	public:
		PointLight(const Color& color, float intensity, float range);

		void Enable(Shader& shader, unsigned i) const override;
	};

} } }
