#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace PrimeEngine { namespace Graphics {

	Texture::Texture(const Color& color) //TODO remove duplicate code
	{
		glGenTextures(1, &_Id);

		GLubyte data[] = { color[0] * 255, color[1] * 255, color[2] * 255, color[3] * 255 };

		glBindTexture(GL_TEXTURE_2D, _Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

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
		glDeleteTextures(1, &_Id);
	}

	GLuint Texture::Load()
	{
		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		unsigned char* image = stbi_load(_path, &_width, &_height, 0, 4);

		// Set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		//glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image);
		return result;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _Id);
	}

	void Texture::Activate(unsigned i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}}