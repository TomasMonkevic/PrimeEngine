#pragma once

#ifdef PE_ANDROID
	#include <GLES3/gl31.h>
#else
	#include <GL/glew.h>
#endif
#include <Utilities/File.h>
#include <Math/Math.h>
#include <DllExport.h>
#include <map>
#include <Graphics/Color.h>

#define VERSION_MACRO		"$version"
#define FRAGMENT_MACRO		"$fragment"
#define VERTEX_MACRO		"$vertex"
#define END_MACRO			"/$"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Shader
	{
	private:
		GLuint _shaderID;
		std::map<std::string, GLint>* _uniformLocation;
	public:
		static const char* defaultShader;
		static const char* phong;
		static const char* glow;
		static const char* simplePhong;
	private:
		GLuint LoadShader(char* vertexSource, char* fragmentSource);
		GLint GetLocation(const std::string& name);
		void ParseShaderFile(std::string& shaderFile, char** vertexSource, char** fragmentSource);
	public:
		Shader(const char* shaderFilePath, bool isSource = false);
		~Shader();

		void SetUniform(const GLchar* name, const Math::Matrix4x4& matrix);
		void SetUniform(const GLchar* name, const Color& color);
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