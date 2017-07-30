#pragma once

#include "Layer.h"
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class UILayer : public Layer 
	{
	public:
		UILayer(Shader* shader);
	};
}}
