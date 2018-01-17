#pragma once

#include "../Color.h"
#include <Graphics\Shader\Shader.h>
#include <DllExport.h>
#include <GameObject.h>

namespace PrimeEngine { namespace Graphics { namespace Lights {

	class PRIMEENGINEAPI Light : public GameObject
	{
	protected:
		Color _color;
		float _intensity;
	public:
		Light(const Color& color, float intensity) //TODO move to CPP
			: _color(color), _intensity(intensity)
		{

		}
		virtual void Enable(Shader& shader, unsigned i) const = 0;
	};

} } }