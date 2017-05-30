#ifndef PRIME_SHADER
#define PRIME_SHADER

#include <GL\glew.h>
#include "..\Utilities\File.h"
#include <Math/Math.h>
#include "..\DllExport.h"
#include <map>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Shader
	{
	private:
		GLuint _shaderID;
		std::map<const GLchar*, GLint>* _uniformLocation;
		const char *_vertexShaderPath, *_fragmentShaderPath;
	public:

	private:
		GLuint LoadShader();
		GLint GetLocation(const GLchar* name);
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void SetUniform(const GLchar* name, const Math::Matrix4x4& matrix);
		void SetUniform(const GLchar* name, const Math::Vector4& vector4);
		void SetUniform(const GLchar* name, const Math::Vector3& vector3);
		void SetUniform(const GLchar* name, const Math::Vector2& vector2);
		void SetUniform(const GLchar* name, float value);
		void SetUniform(const GLchar* name, int value);
		void SetUniform(const GLchar* name, int values[], int size);


		void Enable() const;
		void Disable() const;
	};

}}
#endif // !PRIME_SHADER