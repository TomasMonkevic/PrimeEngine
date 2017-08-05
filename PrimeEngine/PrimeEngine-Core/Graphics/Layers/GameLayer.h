#pragma once

#include "Layer.h"
#include <DllExport.h>
#include <GameObject.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI GameLayer : public Layer 
	{
	public:
		explicit GameLayer(Camera* camera);
		inline void Submit(GameObject* gameObject) { Layer::Submit(gameObject); }
		inline void Remove(GameObject* gameObject) { Layer::Remove(gameObject); }
	};
}}
