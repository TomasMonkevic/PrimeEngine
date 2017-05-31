#include "Shader.h"
#include "../PrimeException.h"

namespace PrimeEngine { namespace Graphics {

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) :
		_vertexShaderPath(vertexShaderPath), _fragmentShaderPath(fragmentShaderPath)
	{
		_uniformLocation = new std::map<const GLchar*, GLint>;
		_shaderID = LoadShader();
	}

	Shader::Shader(const char* shaderFilePath) :
		_shaderFilePath(shaderFilePath)
	{
		_uniformLocation = new std::map<const GLchar*, GLint>;
		_shaderID = LoadShader();
	}

	Shader::~Shader()
	{
		delete _uniformLocation;
		glDeleteProgram(_shaderID);
	}

	GLint Shader::GetLocation(const GLchar* name)
	{
		std::map<const GLchar*, GLint>::iterator mapIterator = _uniformLocation->find(name);
		if (mapIterator == _uniformLocation->end())
		{
			GLint location = glGetUniformLocation(_shaderID, name);
			_uniformLocation->insert(std::pair<const GLchar*, GLint>(name, location));
			return location;
		}
		else
		{
			return mapIterator->second;
		}
	}

	void Shader::SetUniform(const GLchar* name, const Math::Matrix4x4& matrix)
	{
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, matrix.GetElements());
	}

	void Shader::SetUniform(const GLchar* name, const Math::Vector4& vector4) 
	{
		glUniform4f(GetLocation(name), vector4.x, vector4.y, vector4.z, vector4.w);
	}

	void Shader::SetUniform(const GLchar* name, const Math::Vector3& vector3)
	{
		glUniform3f(GetLocation(name), vector3.x, vector3.y, vector3.z);
	}

	void Shader::SetUniform(const GLchar* name, const Math::Vector2& vector2)
	{
		glUniform2f(GetLocation(name), vector2.x, vector2.y);
	}

	void Shader::SetUniform(const GLchar* name, float value)
	{
		glUniform1f(GetLocation(name), value);
	}

	void Shader::SetUniform(const GLchar* name, int value)
	{
		glUniform1i(GetLocation(name), value);
	}

	void Shader::SetUniform(const GLchar* name, int values[], int size)
	{
		glUniform1iv(GetLocation(name), size, values);
	}

	void Shader::ParseShaderFile(std::string& shaderFile, char* vertexShader, char* fragmentShader)
	{

	}

	GLuint Shader::LoadShader()
	{
		GLuint program = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexSourceString = PrimeEngine::File::ReadFile(_vertexShaderPath);
		std::string fragmentSourceString = PrimeEngine::File::ReadFile(_fragmentShaderPath);
		//std::string shaderFileString = PrimeEngine::File::ReadFile(_shaderFilePath);

		const char* vertexSource = vertexSourceString.c_str();
		const char* fragmentSource = fragmentSourceString.c_str();

		//ParseShaderFile(shaderFileString, vertexSource, fragmentSource);

		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		GLint compileResult;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == GL_FALSE)
		{
			GLint lenght;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &lenght);
			char* error = new char[lenght + 1];
			glGetShaderInfoLog(vertexShader, lenght, &lenght, error);
			glDeleteShader(vertexShader);
			char* errorMsg = new char[sizeof(error) + 100];
			sprintf_s(errorMsg, sizeof(error) + 100, "Failed to compile vertex shader:\n%s \n", error);
			PrimeException errorCompiling(errorMsg, -1);
			throw errorCompiling;
		}

		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == GL_FALSE)
		{
			GLint lenght;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &lenght);
			char* error = new char[lenght + 1];
			glGetShaderInfoLog(fragmentShader, lenght, &lenght, error);
			glDeleteShader(fragmentShader);
			char* errorMsg = new char[sizeof(error) + 100];
			sprintf_s(errorMsg, sizeof(error) + 100, "Failed to compile fragment shader:\n%s \n", error);
			PrimeException errorCompiling(errorMsg, -1);
			throw errorCompiling;
		}

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}

	void Shader::Enable() const
	{
		glUseProgram(_shaderID);
	}
	void Shader::Disable() const
	{
		glUseProgram(0);
	}

}}