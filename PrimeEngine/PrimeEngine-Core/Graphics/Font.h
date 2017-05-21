#ifndef PRIME_ENGINE
#define PRIME_ENGINE

#include <Core/Math.h>
#include <DllExport.h>
#include <freetype-gl\freetype-gl.h>
#include <string>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Font
	{
	public:
		int size;
		Math::Vector4 color;
		ftgl::texture_atlas_t* atlas;
		ftgl::texture_font_t* font;

		Font::Font();
		Font(std::string _fontName, Math::Vector4 _color, int _size);
	};
}}

#endif
