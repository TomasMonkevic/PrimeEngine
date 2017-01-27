#ifndef PRIMEENGINE_SHADER
#define PRIMEENGINE_SHADER

#include <GL/glew.h>
#include "../Utilities/File.h"
#include "../DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Shader
	{
	private:
		//GLuint _shaderID;
		const char *_vertexShaderPath, *_fragmentShaderPath;
	public:
		GLuint _shaderID; //make readOnly
	private:
		GLuint LoadShader();
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void Enable() const;
		void Disable() const;
	};

}}
#endif // !PRIMEENGINE_SHADER