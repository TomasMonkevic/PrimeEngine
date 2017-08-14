#include "Texture.h"
#include "..\Utilities\ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace PrimeEngine { namespace Graphics {

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

		BYTE* image = LoadImage(_path, &_width, &_height);
		//int n;
		//unsigned char *data = stbi_load(_path, &_width, &_height, &n, 0);
		// Set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);
		glGenerateMipmap(GL_TEXTURE_2D);

		delete[] image;
		//stbi_image_free(data);
		return result;
	}

	void Texture::Bind() const
	{
		//glActiveTexture(GL_TEXTURE0); //temps
		glBindTexture(GL_TEXTURE_2D, _Id);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}}