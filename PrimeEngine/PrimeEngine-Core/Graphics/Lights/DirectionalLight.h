#pragma once

#include "Light.h"

namespace PrimeEngine { namespace Graphics { namespace Lights {

	using namespace PrimeEngine::Math;

	class PRIMEENGINEAPI DirectionalLight : public Light
	{
	public:
		DirectionalLight(const Color& color, float intensity);

		void Enable(Shader& shader, unsigned i) const override;
	};

} } }
