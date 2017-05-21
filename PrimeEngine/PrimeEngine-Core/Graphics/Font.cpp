#include "Font.h"

namespace PrimeEngine { namespace Graphics {

	Font::Font()
		: Font("arial2.ttf", Math::Vector4::one, 32)
	{

	}

	Font::Font(std::string _fontName, Math::Vector4 _color, int _size)
		: color(_color), size(_size)
	{
		atlas = ftgl::texture_atlas_new(512, 512, 2);
		font = texture_font_new_from_file(atlas, size, _fontName.c_str());
	}
}}