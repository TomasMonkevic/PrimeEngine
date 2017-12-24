#pragma once

#include <GL\glew.h>
#include <Utilities\File.h>
#include <Math/Math.h>
#include <DllExport.h>
#include <map>

#define VERSION_MACRO		"$version"
#define FRAGMENT_MACRO		"$fragment"
#define VERTEX_MACRO		"$vertex"
#define END_MACRO			"/$"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Shader
	{
	private:
		GLuint _shaderID;
		std::map<const GLchar*, GLint>* _uniformLocation;
	public:
		static const char* default;
	private:
		GLuint LoadShader(char* vertexSource, char* fragmentSource);
		GLint GetLocation(const GLchar* name);
		void ParseShaderFile(std::string& shaderFile, char** vertexSource, char** fragmentSource);
	public:
		Shader(const char* shaderFilePath, bool isSource = false);
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