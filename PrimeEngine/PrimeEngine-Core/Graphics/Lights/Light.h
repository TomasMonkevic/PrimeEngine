#pragma once

#include "../Color.h"
#include <DllExport.h>
#include <GameObject.h>

namespace PrimeEngine { namespace Graphics { namespace Lights {

	class PRIMEENGINEAPI Light : public GameObject
	{
	private:
		Color _color;
		float _intesity;
	public:
		virtual void Enable() const = 0;
	};

} } }