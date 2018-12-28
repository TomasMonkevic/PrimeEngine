#include "Color.h"
#include <Utilities/Log.h>

namespace PrimeEngine { namespace Graphics {

	Color::Color(float r, float g, float b, float a) :
		_r(r), _g(g), _b(b), _a(a)
	{

	}

	Color::Color(int r, int g, int b, int a)
	{
		_r = float(r / 255.0f);
		_g = float(g / 255.0f);
		_b = float(b / 255.0f);
		_a = float(a / 255.0f);
	}

	Color::Color(unsigned int hex)
	{
		unsigned r = hex & 0xFF;
		hex >>= 8;
		unsigned g = hex & 0xFF;
		hex >>= 8;
		unsigned b = hex & 0xFF;
		hex >>= 8;
		unsigned a = hex & 0xFF;
		_r = float(r / 255.0f);
		_g = float(g / 255.0f);
		_b = float(b / 255.0f);
		_a = float(a / 255.0f);
	}

	const unsigned Color::ToColor32() const
	{
		unsigned r = unsigned(_r * 255.0f);
		unsigned g = unsigned(_g * 255.0f);
		unsigned b = unsigned(_b * 255.0f);
		unsigned a = unsigned(_a * 255.0f);
		
		//does endianess matter?
		return (a << 8 * 3) | (b << 8 * 2) | (g << 8 * 1) | r;
	}
}}