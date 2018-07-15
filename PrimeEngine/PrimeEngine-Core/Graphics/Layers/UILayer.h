#pragma once

#include "Layer.h"
#include <DllExport.h>
#include <UI\UIObject.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI UILayer : public Layer
	{
	public:
		UILayer();
		inline void Submit(UI::UIObject* UIobject) { Layer::Submit(UIobject); }
		inline void Remove(UI::UIObject* UIobject) { Layer::Remove(UIobject); }
	};
}}
