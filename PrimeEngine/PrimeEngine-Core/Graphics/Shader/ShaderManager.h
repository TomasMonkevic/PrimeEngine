#pragma once

#include "Shader.h"
#include <unordered_map>
#include <DllExport.h>

#define ShaderManagerI ShaderManager::Instance()

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI ShaderManager
	{
	private:
		std::unordered_map<const char*,Shader*>* _shaders;
		static ShaderManager* _instance;
	private:
		ShaderManager();
	public:
		~ShaderManager();
		static ShaderManager& Instance()
		{
			static ShaderManager instance;
			return instance;
		}

		Shader* CreateShader(const char* shaderName, const char* shaderFile, bool isSource = true);
		Shader* GetShader(const char* shaderName);
		void DeleteShader(const char* shaderName);
	};
}}