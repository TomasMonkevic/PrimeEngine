#pragma once

#include <DllExport.h>
#include "Mesh.h"
#include <vector>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI ModelImporter
	{
	public:
		ModelImporter();

		Mesh* ImportModel(const char* path, bool isCalcTangents) const;
	};
}}
