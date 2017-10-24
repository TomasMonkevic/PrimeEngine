#include "ShaderManager.h"

namespace PrimeEngine { namespace Graphics {

	ShaderManager* ShaderManager::_instance = NULL;

	ShaderManager::ShaderManager()
	{
		_shaders = new std::unordered_map<const char*, Shader*>();
	}

	ShaderManager::~ShaderManager()
	{
		//TODO memory leak delete actual shaders
		//delete all shaders
		delete _shaders;
	}

	Shader* ShaderManager::CreateShader(const char* shaderName, const char* shaderFile, bool isSource)
	{
		//shader object is copied - not good
		//TODO: need to create a move constructor in shader class
		_shaders->insert(std::pair<const char*, Shader*>(shaderName, new Shader(shaderFile, isSource)));
		return (*_shaders)[shaderName];
	}

	Shader* ShaderManager::GetShader(const char* shaderName)
	{
		std::unordered_map<const char*, Shader*>::iterator iter = _shaders->find(shaderName);
		if (iter == _shaders->end())
		{
			return NULL;
		}
		else
		{
			return iter->second;
		}
	}

	void ShaderManager::DeleteShader(const char* shaderName)
	{

	}
}}