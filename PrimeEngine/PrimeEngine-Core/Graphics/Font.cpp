#include "Font.h"

namespace PrimeEngine { namespace Graphics {

	Font::Font()
		: Font("arial2.ttf", Color::white, 32)
	{

	}

	Font::Font(std::string _fontName, const Color& _color, int _size)
		: color(_color), size(_size)
	{
		atlas = ftgl::texture_atlas_new(512, 512, 2);
		font = texture_font_new_from_file(atlas, size, _fontName.c_str());
	}
}}