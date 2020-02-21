#include <Graphics/Font.h>

#include <Utilities/Log.h>
#include <Utilities/FileUtils.h>

namespace PrimeEngine { namespace Graphics {

	Font::Font()
		: Font("arial2.ttf", Color::White(), 32)
	{

	}

	Font::Font(const char* _fontName, const Color& _color, int _size)
		: size(_size), color(_color)
	{
		atlas = ftgl::texture_atlas_new(1024, 1024, 2); //TODO remove hard coded values
#ifdef PE_ANDROID
		ByteArray data = ReadFileBytes(_fontName);
		font = texture_font_new_from_memory(atlas, size, data.data.get(), data.size);
#else
        font = texture_font_new_from_file(atlas, size, _fontName);
#endif
		if(font == nullptr)
		{
			PRIME_WARNING(_fontName, " not loaded!\n");
		}
	}
}}