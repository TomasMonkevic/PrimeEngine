#include "Shader.h"
#include <Utilities/Log.h>

namespace PrimeEngine { namespace Graphics {

#ifdef PE_ANDROID
	const char* Shader::defaultShader =
	#include "Source/Android/Default.pesl"
	;

	const char* Shader::phong =
	#include "Source/Android/Phong.pesl"
	;

	const char* Shader::glow =
	#include "Source/Android/Glow.pesl"
	;

	const char* Shader::simplePhong =
	#include "Source/Android/SimplePhong.pesl"
	;
#else
	const char* Shader::defaultShader =
	#include "Source/Desktop/Default.pesl"
	;

	const char* Shader::phong =
	#include "Source/Desktop/Phong.pesl"
	;

	const char* Shader::glow =
	#include "Source/Desktop/Glow.pesl"
	;

	const char* Shader::simplePhong =
	#include "Source/Desktop/SimplePhong.pesl"
	;
#endif

	Shader::Shader(const char* shaderFile, bool isSource)
	{
		_uniformLocation = new std::map<std::string, GLint>;

		std::string shaderFileString = isSource ? shaderFile : PrimeEngine::ReadFileString(shaderFile);
		char* vertexSource = NULL;
		char* fragmentSource = NULL;
		ParseShaderFile(shaderFileString, &vertexSource, &fragmentSource);
		_shaderID = LoadShader(vertexSource, fragmentSource);
		delete vertexSource;
		delete fragmentSource;
	}

	Shader::~Shader()
	{
		delete _uniformLocation;
		GlCall(glDeleteProgram(_shaderID));
	}

	GLint Shader::GetLocation(const std::string& name)
	{
		std::map<std::string, GLint>::iterator mapIterator = _uniformLocation->find(name);
		if (mapIterator == _uniformLocation->end())
		{
			GlCall(GLint location = glGetUniformLocation(_shaderID, name.c_str()));
			_uniformLocation->insert(std::pair<std::string, GLint>(name, location));
			return location;
		}
		else
		{
			return mapIterator->second;
		}
	}

	void Shader::SetUniform(const GLchar* name, const Math::Matrix4x4& matrix)
	{
		GlCall(glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, matrix.GetElements()));
	}

	void Shader::SetUniform(const GLchar* name, const Math::Vector4& vector4)
	{
		GlCall(glUniform4f(GetLocation(name), vector4.x, vector4.y, vector4.z, vector4.w));
	}

	void Shader::SetUniform(const GLchar* name, const Color& color)
	{
		GlCall(glUniform4f(GetLocation(name), color[0], color[1], color[2], color[3]));
	}

	void Shader::SetUniform(const GLchar* name, const Math::Vector3& vector3)
	{
		GlCall(glUniform3f(GetLocation(name), vector3.x, vector3.y, vector3.z));
	}

	void Shader::SetUniform(const GLchar* name, const Math::Vector2& vector2)
	{
		GlCall(glUniform2f(GetLocation(name), vector2.x, vector2.y));
	}

	void Shader::SetUniform(const GLchar* name, float value)
	{
		GlCall(glUniform1f(GetLocation(name), value));
	}

	void Shader::SetUniform(const GLchar* name, int value)
	{
		GlCall(glUniform1i(GetLocation(name), value));
	}

	void Shader::SetUniform(const GLchar* name, int values[], int size)
	{
		GlCall(glUniform1iv(GetLocation(name), size, values));
	}

	void Shader::ParseShaderFile(std::string& shaderFile, char** vertexSourceOut, char** fragmentSourceOut)
	{
		std::size_t globalPos = 0, temp;
		std::string version;
		globalPos = shaderFile.find(VERSION_MACRO, globalPos);
		if (globalPos != shaderFile.npos)
		{
			temp = globalPos;
			globalPos = shaderFile.find(END_MACRO, globalPos + 1);
			if (globalPos != shaderFile.npos)
			{
				version = shaderFile.substr(temp, globalPos - temp);
			}
		}
		version.replace(0, 1, "#");
		version += '\n';

		std::string vertex, fragment;

		globalPos = shaderFile.find(VERTEX_MACRO, globalPos); //move command recognision to a seperate function
		if (globalPos != shaderFile.npos)
		{
			temp = globalPos;
			globalPos = shaderFile.find(END_MACRO, globalPos + 1);
			if (globalPos != shaderFile.npos)
			{
				vertex = shaderFile.substr(temp + strlen(VERTEX_MACRO), globalPos - strlen(VERTEX_MACRO) - temp);
			}
		}

		globalPos = shaderFile.find(FRAGMENT_MACRO, globalPos);
		if (globalPos != shaderFile.npos)
		{
			temp = globalPos;
			globalPos = shaderFile.find(END_MACRO, globalPos + 1);
			if (globalPos != shaderFile.npos)
			{
				fragment = shaderFile.substr(temp + strlen(FRAGMENT_MACRO), globalPos - strlen(FRAGMENT_MACRO) - temp);
			}
		}

		vertex.insert(0, version);
		fragment.insert(0, version);

		*vertexSourceOut = new char[vertex.length() + 1];
		*fragmentSourceOut = new char[fragment.length() + 1];

		#ifdef _WIN32
			strcpy_s(*vertexSourceOut, vertex.length() + 1,vertex.c_str());
			strcpy_s(*fragmentSourceOut, fragment.length() + 1, fragment.c_str());
		#else
			strcpy(*vertexSourceOut, vertex.c_str());
			strcpy(*fragmentSourceOut, fragment.c_str());
		#endif
	}

	GLuint Shader::LoadShader(char* vertexSource, char* fragmentSource)
	{
		GlCall(GLuint program = glCreateProgram());
		GlCall(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
		GlCall(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

		GlCall(glShaderSource(vertexShader, 1, &vertexSource, NULL));
		GlCall(glCompileShader(vertexShader));

		GLint compileResult;
		GlCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult));
		if (compileResult == GL_FALSE)
		{
			GLint lenght;
			GlCall(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &lenght));
			//TODO memory leak change to alloca
			char* error = new char[lenght + 1];
			GlCall(glGetShaderInfoLog(vertexShader, lenght, &lenght, error));
			GlCall(glDeleteShader(vertexShader));
			PRIME_ERROR("Failed to compile vertex shader:\n", error,"\n");
			//char* errorMsg = new char[sizeof(error) + 100];
			//sprintf_s(errorMsg, sizeof(error) + 100, "Failed to compile vertex shader:\n%s \n", error);
			//PrimeException errorCompiling(errorMsg, -1);
			//throw errorCompiling;
		}

		GlCall(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));
		GlCall(glCompileShader(fragmentShader));

		GlCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult));
		if (compileResult == GL_FALSE)
		{
			GLint lenght;
			GlCall(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &lenght));
			char* error = new char[lenght + 1];
			GlCall(glGetShaderInfoLog(fragmentShader, lenght, &lenght, error));
			GlCall(glDeleteShader(fragmentShader));
			PRIME_ERROR("Failed to compile fragment shader:\n", error, "\n"); //const char type not supported
			//char* errorMsg = new char[sizeof(error) + 100];
			//sprintf_s(errorMsg, sizeof(error) + 100, "Failed to compile fragment shader:\n%s \n", error);
			//PrimeException errorCompiling(errorMsg, -1);
			//throw errorCompiling;
		}

		GlCall(glAttachShader(program, vertexShader));
		GlCall(glAttachShader(program, fragmentShader));

		GlCall(glLinkProgram(program));
		GlCall(glValidateProgram(program));

		GlCall(glDeleteShader(vertexShader));
		GlCall(glDeleteShader(fragmentShader));

		return program;
	}

	void Shader::Enable() const
	{
		GlCall(glUseProgram(_shaderID));
	}
	void Shader::Disable() const
	{
		GlCall(glUseProgram(0));
	}

}}