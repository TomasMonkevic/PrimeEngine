#include "Font.h"

namespace PrimeEngine { namespace Graphics {

	Font::Font()
		: Font("arial2.ttf", Color::white, 32)
	{

	}

	Font::Font(const char* _fontName, const Color& _color, int _size)
		: color(_color), size(_size)
	{
		atlas = ftgl::texture_atlas_new(512, 512, 2); //TODO remove hard coded values
		font = texture_font_new_from_file(atlas, size, _fontName);
	}
}}