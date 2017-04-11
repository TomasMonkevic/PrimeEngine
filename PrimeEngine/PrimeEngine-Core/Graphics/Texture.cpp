#include "Texture.h"
#include "..\Utilities\ImageLoader.h"

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
		// Set the texture wrapping/filtering options (on the currently bound texture object)
		BYTE* image = LoadImage(_path, &_width, &_height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _width, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);
		//glGenerateMipmap(GL_TEXTURE_2D);
		//delete image;
		return result;
	}

	void Texture::Bind() const
	{
		glActiveTexture(GL_TEXTURE0); //temps
		glBindTexture(GL_TEXTURE_2D, _Id);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}}