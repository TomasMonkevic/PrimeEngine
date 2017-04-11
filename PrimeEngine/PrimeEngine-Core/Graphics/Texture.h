#ifndef PRIME_TEXTURE
#define PRIME_TEXTURE

#include <GL\glew.h>
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Texture
	{
	private:
		GLuint _Id;
		unsigned _width, _height;
		const char* _path;

	private:
		GLuint Load();

	public:
		Texture(const char* path);
		~Texture();

		void Bind() const;
		void Unbind() const;
	};
}}

#endif //!PRIME_TEXTURE
