#include "Font.h"
#include "../Utilities/Log.h"
#include "../Utilities/File.h"

namespace PrimeEngine { namespace Graphics {

	Font::Font()
		: Font("arial2.ttf", Color::White(), 32)
	{

	}

	Font::Font(const char* _fontName, const Color& _color, int _size)
		: size(_size), color(_color)
	{
		atlas = ftgl::texture_atlas_new(512, 512, 2); //TODO remove hard coded values
#ifdef PE_ANDROID
		uint8_t* data;
		size_t len;
		File::ReadFileBytes(_fontName, &data, len);
		font = texture_font_new_from_memory(atlas, size, data, len);
		delete[] data;
#else
        font = texture_font_new_from_file(atlas, size, _fontName);
#endif
		if(font == nullptr)
		{
			PRIME_WARNING(_fontName, " not loaded!\n");
		}
	}
}}