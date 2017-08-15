#ifndef PRIME_TEXTURE
#define PRIME_TEXTURE

#include <GL\glew.h>
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

//!!!Not every PC supports 32 uniform textures in a shaderssss
#define MAX_TEXTURE_COUNT 8 //should be change dynamically
//glGetIntegerv() with parameters GL_MAX_FRAGMENT_UNIFORM_COMPONENTS and GL_MAX_FRAGMENT_UNIFORM_VECTORS

	class PRIMEENGINEAPI Texture
	{
	private:
		GLuint _Id;
		unsigned int _width, _height;
		const char* _path;

	private:
		GLuint Load();

	public:
		Texture(const char* path);
		~Texture();

		void Bind() const;
		void Unbind() const;

		inline const Math::Vector2 GetSize() const { return Math::Vector2(_width, _height); }
		inline const GLuint GetId() const {	return _Id;	}
	};
}}

#endif //!PRIME_TEXTURE
