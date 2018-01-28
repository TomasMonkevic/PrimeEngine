#pragma once

#include <GL\glew.h>
#include "..\DllExport.h"
#include <Math\Vector2.h>
#include "Color.h"

namespace PrimeEngine { namespace Graphics {

//!!!Not every PC supports 32 uniform textures in a shaderssss
#define MAX_TEXTURE_COUNT 32 //should be change dynamically
//glGetIntegerv() with parameters GL_MAX_FRAGMENT_UNIFORM_COMPONENTS and GL_MAX_FRAGMENT_UNIFORM_VECTORS

	class PRIMEENGINEAPI Texture
	{
	private:
		GLuint _Id;
		int _width, _height;
		const char* _path;

	private:
		GLuint Load();

	public:
		Texture(const Color& color); //creates 1x1 empty texture
		Texture(const char* path);
		~Texture();

		void Activate(unsigned i);
		void Bind() const;
		void Unbind() const;

		inline const Math::Vector2 GetSize() const { return Math::Vector2((float)_width, (float)_height); }
		inline const char* GetPath() const { return _path; }
		inline const GLuint GetId() const {	return _Id;	}
	};
}}