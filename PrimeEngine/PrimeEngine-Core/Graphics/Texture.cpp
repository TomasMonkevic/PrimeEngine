#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Utilities/Log.h"
#include "../Utilities/FileUtils.h"

namespace PrimeEngine { namespace Graphics {

	Texture::Texture(const Color& color) //TODO remove duplicate code
	{
		GlCall(glGenTextures(1, &_Id));

		GLubyte data[] = { color[0] * 255, color[1] * 255, color[2] * 255, color[3] * 255 };

		GlCall(glBindTexture(GL_TEXTURE_2D, _Id));

		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

		_width = 1;
		_height = 1;
	}

	Texture::Texture(const char* path)
		: _path(path)
	{
		_Id = Load();
	}

	Texture::~Texture()
	{
		Unbind();
		GlCall(glDeleteTextures(1, &_Id));
	}

	GLuint Texture::Load()
	{
		GLuint result;
		GlCall(glGenTextures(1, &result));
		GlCall(glBindTexture(GL_TEXTURE_2D, result));

		stbi_set_flip_vertically_on_load(1);
		ByteArray data = ReadFileBytes(_path);
		unsigned char* image = stbi_load_from_memory(data.data.get(), data.size, &_width, &_height, nullptr, 4);
		if(!image)
		{
			PRIME_WARNING(
				_path, " Width: ", _width, " Height:", _height, '\n',
				stbi_failure_reason(), " ", errno, '\n');
		}

		// Set the texture wrapping/filtering options (on the currently bound texture object)
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
		//glGenerateMipmap(GL_TEXTURE_2D);
		GlCall(glBindTexture(GL_TEXTURE_2D, 0));

		stbi_image_free(image);
		return result;
	}

	void Texture::Bind() const
	{
		GlCall(glBindTexture(GL_TEXTURE_2D, _Id));
	}

	void Texture::Activate(unsigned i)
	{
		GlCall(glActiveTexture(GL_TEXTURE0 + i));
	}

	void Texture::Unbind() const
	{
		GlCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

}}