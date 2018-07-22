#pragma once

#include <Math/Math.h>
#include <DllExport.h>
#include <freetype-gl/freetype-gl.h>
#include "Color.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Font
	{
	public:
		int size;
		Color color;
		ftgl::texture_atlas_t* atlas;
		ftgl::texture_font_t* font;

		Font();
		Font(const char* _fontName, const Color& _color, int _size);
	};
}}
