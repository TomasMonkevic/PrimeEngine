#include "Color.h"
#include <Utilities\Log.h>

namespace PrimeEngine { namespace Graphics {

	const Color Color::white = Color(1.0f, 1.0f, 1.0f);
	const Color Color::black = Color(0.0f, 0.0f, 0.0f);

	Color::Color(float r, float g, float b, float a) :
		_r(r), _g(g), _b(b), _a(a)
	{

	}

	Color::Color(unsigned r, unsigned g, unsigned b, unsigned a)
	{

	}

	Color::Color(const char* hexColor)
	{

	}

	const unsigned Color::ToColor32() const
	{
		unsigned r = _r * 255;
		unsigned g = _g * 255;
		unsigned b = _b * 255;
		unsigned a = _a * 255;
		
		//does endianess matter?
		return (a << 8 * 3) | (b << 8 * 2) | (g << 8 * 1) | r;
	}

}}