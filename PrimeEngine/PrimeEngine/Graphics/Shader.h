#ifndef PRIMEENGINE_SHADER
#define PRIMEENGINE_SHADER

#include <GL\glew.h>
#include "..\Utilities\File.h"
#include "..\Core\Math.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Shader
	{
	private:
		GLuint _shaderID;
		const char *_vertexShaderPath, *_fragmentShaderPath;
	public:

	private:
		GLuint LoadShader();
		GLint GetLocation(const GLchar* name) const;
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void SetUniform(const GLchar* name, const Math::Matrix4x4& matrix) const;

		void Enable() const;
		void Disable() const;
	};

}}
#endif // !PRIMEENGINE_SHADER