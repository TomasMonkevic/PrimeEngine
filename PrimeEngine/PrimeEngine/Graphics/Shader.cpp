#include "Shader.h"

namespace PrimeEngine { namespace Graphics {

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) :
		_vertexShaderPath(vertexShaderPath), _fragmentShaderPath(fragmentShaderPath)
	{
		_shaderID = LoadShader();
	}

	Shader::~Shader()
	{
		glDeleteProgram(_shaderID);
	}

	GLuint Shader::LoadShader()
	{
		GLuint program = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexSourceString = PrimeEngine::File::ReadFile(_vertexShaderPath);
		std::string fragmentSourceString = PrimeEngine::File::ReadFile(_fragmentShaderPath);

		const char* vertexSource = vertexSourceString.c_str();
		const char* fragmentSource = fragmentSourceString.c_str();

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
			char* errorMsg = new char[sizeof(error) + 50];
			sprintf(errorMsg, "Failed to compile vertex shader:\n%s \n", error);
			throw errorMsg; //a loging system would be nice
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
			char* errorMsg = new char[sizeof(error) + 50];
			sprintf(errorMsg, "Failed to compile fragment shader:\n%s \n", error);
			throw errorMsg; //a loging system would be nice
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