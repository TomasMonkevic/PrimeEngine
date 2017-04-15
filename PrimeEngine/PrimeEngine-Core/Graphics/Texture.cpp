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
		//unsigned pitch = 0;
		BYTE* image = LoadImage(_path, &_width, &_height);
		// Set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//GLenum colorType = pitch == 32 ? GL_BGRA : GL_BGR; //not sure if correct solution
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _width, 0, GL_BGRA, GL_UNSIGNED_BYTE, image); //doesn't work for every image format
		glBindTexture(GL_TEXTURE_2D, 0);
		glGenerateMipmap(GL_TEXTURE_2D);
		//delete[] image;
		//need to clean up image memory!!!!!!!!!!!!!
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